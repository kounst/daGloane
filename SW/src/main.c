/*
 * main.c
 *
 *  Created on: Oct 20, 2012
 *      Author: konstantin
 *
 */

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "main.h"
#include "GPIO.h"
#include "UART.h"
#include "ADC.h"
#include "TIM.h"
#include "SPI.h"
#include "uAC.h"
#include "uAC_CMD.h"
#include "kalman.h"
#include "com.h"

#include "Complementary_Filter.h"
#include "PID_Controller.h"
#include "GAS_for_Engines.h"

/* External inputs (root inport signals with auto storage) */
extern ExtU_Complementary_Filter_T Complementary_Filter_U;
extern ExtU_PID_Controller_T  PID_Controller_U;
extern ExtU_GAS_for_Engines_T GAS_for_Engines_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_Complementary_Filter_T Complementary_Filter_Y;
extern ExtY_PID_Controller_T  PID_Controller_Y;
extern ExtY_GAS_for_Engines_T GAS_for_Engines_Y;


/* Global variables */
extern uint16_t lipo_voltage;
float acc_pitch, acc_roll;

uint8_t msg2_bytearray[12];

mpudata mpu;
mpudata mpu_45;
mpudata mpu_offset;

kalman_data pitch_data;
kalman_data roll_data;

extern msg1 control_msg;
volatile uint8_t tick = 0;



DMA_InitTypeDef DMA_InitStructure;




extern char uart_tx_buffer[255];

/* Private functions */

/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */
int main(void)
{

	/* System Clocks Configuration */
	RCC_Configuration();

	/* NVIC Configuration */
	NVIC_Configuration();

	/* GPIO Configuration */
	GPIO_Configuration();

	/* keep DC/DC form turning off again (set Power_ON_µC) */
	GPIOB->BSRR = GPIO_Pin_2;

	/* ADC Configuration */
	ADC1_Configuration();

	UART1_DMA_Configuration();

	/* UART1 Configuration */
	//UART1_Configuration();
	UART1_Configuration2();

	/* UART2 Configuration for bluetooth AT command mode */
	UART2_Configuration_AT(115200);

	/* Init the uAC */
	//uac_init();

	/* Attach uac commands */
	//uAC_CMD_attach();

	/* TIM3 Configuration */
	TIM3_Configuration();

	/* TIM2 Configuration */
	LED_Timer_Configuration();

	/* Systick Configuration */
	SysTick_Configuration();

	/* SPI1 Configuration */
	SPI1_Configuration();

	//uac_printf("\nHello, my name is daGloane\n");

	/* measure ACC channels while copter is stationary to obtain offsets. */
	GetCalibrationData();

	kalman_init(&pitch_data);
	kalman_init(&roll_data);

	control_msg.throttle = 0;
	control_msg.nick = 0;
	control_msg.roll = 0;
	control_msg.yaw = 0;

	Complementary_Filter_initialize();
	PID_Controller_initialize();
	GAS_for_Engines_initialize();

	/* Infinite loop */
	while (1)
	{
		if (tick == 1)
		{
			LEDOn(LED1);

			tick = 0 ;
			//read data from MPU-6000
			MPU_read(&mpu);

			//remove offsets from ACC data
			mpu.acc_x -= mpu_offset.acc_x;
			mpu.acc_y -= mpu_offset.acc_y;
			mpu.gyro_x -= mpu_offset.gyro_x;
			mpu.gyro_y -= mpu_offset.gyro_y;
			mpu.gyro_z -= mpu_offset.gyro_z;


			//rotate gyro coordinate system to rotor coordinate system
			mpu_45.acc_x = sin_45deg * mpu.acc_x + sin_45deg * mpu.acc_y;
			mpu_45.acc_y = sin_45deg * mpu.acc_y - sin_45deg * mpu.acc_x;
			mpu_45.acc_z = mpu.acc_z;
			mpu_45.gyro_x = sin_45deg * mpu.gyro_x + sin_45deg * mpu.gyro_y;
			mpu_45.gyro_y = sin_45deg * mpu.gyro_y - sin_45deg * mpu.gyro_x;
			mpu_45.gyro_z = mpu.gyro_z;

			Complementary_Filter_U.acc_pitch = atan2(mpu_45.acc_y, mpu_45.acc_z);
			Complementary_Filter_U.acc_roll = atan2(mpu_45.acc_x, mpu_45.acc_z);
			Complementary_Filter_U.mpu_45gyro_x = (double)mpu_45.gyro_x / 7506;	// 131 LSB/°/s; 1rad/s = 0.017°/s --> 131/0.017 = 7506
			Complementary_Filter_U.mpu_45gyro_y = (double)mpu_45.gyro_y / 7506;
			Complementary_Filter_U.mpu_45gyro_z = (double)mpu_45.gyro_z / 7506;

			Complementary_Filter_step();
			PID_Controller_step();
			GAS_for_Engines_step();

			LEDOff(LED1);
			LEDToggle(LED2);

			/*f2b._float = Complementary_Filter_U.acc_pitch;
			uart_tx_buffer[0] = f2b.bytes[0];
			uart_tx_buffer[1] = f2b.bytes[1];
			uart_tx_buffer[2] = f2b.bytes[2];
			uart_tx_buffer[3] = f2b.bytes[3];
			uart_tx_buffer[4] = '\0';*/

			//sprintf(uart_tx_buffer, "accx:%d, accy:%d, accz:%d\n", mpu_45.acc_x, mpu_45.acc_y, mpu_45.acc_z);
			sprintf(uart_tx_buffer, "accR:%f, accP:%f,gyroR:%f, gyroP:%f, gyroY:%f, cfroll:%f, cfpitch:%f\n", Complementary_Filter_U.acc_roll, Complementary_Filter_U.acc_pitch, Complementary_Filter_U.mpu_45gyro_x, Complementary_Filter_U.mpu_45gyro_y, Complementary_Filter_U.mpu_45gyro_z, Complementary_Filter_Y.ist_roll, Complementary_Filter_Y.ist_pitch);



			/* Disable and re-enable DMA to start new transfer */
			DMA1_Channel4->CCR &= ~DMA_CCR4_EN;				//disable DMA
			DMA1_Channel4->CMAR = (unsigned)uart_tx_buffer;	//memory base address for DMA transfer
			DMA1_Channel4->CNDTR = strlen(uart_tx_buffer);	//number of bytes to transfer
			DMA1_Channel4->CCR |= DMA_CCR4_EN;				//enable DMA


			/*
			 The new kalman estimate is now stored in pitch_data.x1, pitch_data.x2, pitch_data.x3
			 * 	   									    roll_data.x1,  roll_data.x2,  roll_data.x3

			msg2_bytearray[0] = ((uint32_t)pitch_data.x1 >> 24);
			msg2_bytearray[1] = ((uint32_t)pitch_data.x1 >> 16);
			msg2_bytearray[2] = ((uint32_t)pitch_data.x1 >> 8);
			msg2_bytearray[3] = ((uint32_t)pitch_data.x1);
			msg2_bytearray[4] = ((uint32_t)pitch_data.x2 >> 24);
			msg2_bytearray[5] = ((uint32_t)pitch_data.x2 >> 16);
			msg2_bytearray[6] = ((uint32_t)pitch_data.x2 >> 8);
			msg2_bytearray[7] = ((uint32_t)pitch_data.x2);
			msg2_bytearray[8] = ((uint32_t)pitch_data.x3 >> 24);
			msg2_bytearray[9] = ((uint32_t)pitch_data.x3 >> 16);
			msg2_bytearray[10] = ((uint32_t)pitch_data.x3 >> 8);
			msg2_bytearray[11] = ((uint32_t)pitch_data.x3);
			 */


			//		uac_printf("Pitch,Roll,GyroX,GyroY,AccPitch,AccRoll = ( %f , %f , %f , %f , %f , %f)\n",Complementary_Filter_Y.ist_pitch,Complementary_Filter_Y.ist_roll,Complementary_Filter_U.mpu_45gyro_x,Complementary_Filter_U.mpu_45gyro_y),Complementary_Filter_U.acc_pitch,Complementary_Filter_U.acc_roll;
			//uac_printf("test123");
			//LEDToggle(LED1);
			//LEDToggle(LED2);
			/* The uAC_Task() must be called periodically
			 * It checks whether a command has been received and
			 * calls the corresponding uAC_CMD function
			 */
			//Delay(25);		//100ms

			//uac_task();

			//If there are outgoing chars, send them
			//uac_tx_task();
		}
	}
}



void GetCalibrationData()
{
	int i;
	int neutralX = 0;
	int neutralY = 0;
	//int neutralZ = 0;
	int neutralPi = 0;
	int neutralRo = 0;
	int neutralYa = 0;

	for(i = 0; i < 128; i++)
	{
		//SPI1_read(ACCEL_XOUT_H ,mpu.bytes,14);
		MPU_read(&mpu);
		neutralX += mpu.acc_x;
		neutralY += mpu.acc_y;
		//neutralZ += mpu.acc_z;
		neutralPi += mpu.gyro_x;
		neutralRo += mpu.gyro_y;
		neutralYa += mpu.gyro_z;
		Delay(3);
	}

	mpu_offset.acc_x = neutralX / 128;
	mpu_offset.acc_y = neutralY / 128;
	//mpu_offset.acc_z = neutralZ / 128;
	mpu_offset.gyro_x = neutralPi / 128;
	mpu_offset.gyro_y = neutralRo / 128;
	mpu_offset.gyro_z = neutralYa / 128;
}





void RCC_Configuration(void)
{
	/* Setup the microcontroller system. Initialize the Embedded Flash Interface,
     initialize the PLL and update the SystemFrequency variable. */
	SystemInit();

	/* PCLK1 = HCLK/2 */
	RCC_PCLK1Config(RCC_HCLK_Div2);

	RCC_ADCCLKConfig(RCC_PCLK2_Div4);

	/* GPIOA, GPIOB and AFIO clocks enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |  RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	/* USART1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* USART2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* DMA1 clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* ADC1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/* SPI1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
}

/**
 * @brief  Configures the nested vectored interrupt controller.
 * @param  None
 * @retval None
 */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//  /* Enable the TIM3 gloabal interrupt */
	//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//  NVIC_Init(&NVIC_InitStructure);
	//
	//
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* SysTick Priority */
	NVIC_SetPriority(SysTick_IRQn, 2);
}


/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
	while(1)
	{}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
	__assert_func (file, line, NULL, failedexpr);
}

