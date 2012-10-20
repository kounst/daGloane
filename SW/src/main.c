/**
 *****************************************************************************
 **
 **  File        : main.c
 **
 **  Abstract    : main function.
 **
 **  Functions   : main
 **
 **  Environment : Atollic TrueSTUDIO/STM32
 **                STMicroelectronics STM32F10x Standard Peripherals Library
 **
 **  Distribution: The file is distributed “as is,” without any warranty
 **                of any kind.
 **
 **  (c)Copyright Atollic AB.
 **  You may use this file as-is or modify it according to the needs of your
 **  project. Distribution of this file (unmodified or modified) is not
 **  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
 **  rights to distribute the assembled, compiled & linked contents of this
 **  file as part of an application binary file, provided that it is built
 **  using the Atollic TrueSTUDIO(R) toolchain.
 **
 **
 *****************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include <math.h>
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


/* Global variables */
extern uint16_t lipo_voltage;
float acc_pitch, acc_roll;

mpudata mpu;
mpudata mpu_offset;

kalman_data pitch_data;
kalman_data roll_data;




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

	/* keep DCDC form turning off again (set Power_ON_µC)*/
	GPIOB->BSRR = GPIO_Pin_2;

	/* ADC Configuration */
	ADC1_Configuration();

	/* UART1 Configuration */
	UART1_Configuration();

	/* Init the uAC */
	uac_init();

	/* TIM3 Configuration */
	TIM3_Configuration();

	/* Systick Configuration */
	SysTick_Configuration();

	/* SPI1 Configuration */
	SPI1_Configuration();


	//Attach uac commands
	uac_attach("Hello",Hello_CMD);
	uac_attach("getMPU",get_MPU6000_data);
	uac_attach("getLiPo",get_LiPoVoltage);
	uac_attach("getSwitch", get_Switch);
	uac_attach("PwrOff", PwrOff);
	uac_attach("accangle", ACC_angle);
	uac_attach("getangle", get_angle);


	uac_printf("\nHello, my name is daGloane\n");

	//measure ACC channels while copter is stationary to obtain offsets.
	CalibrateACC();

	kalman_init(&pitch_data);
	kalman_init(&roll_data);

	/* Infinite loop */
	while (1)
	{
		//read data from MPU-6000 starting at address ACCEL_XOUT_H
		SPI1_read(ACCEL_XOUT_H ,mpu.bytes,14);

		//remove offsets from ACC data
		mpu.acc_x -= mpu_offset.acc_x;
		mpu.acc_y -= mpu_offset.acc_y;
		mpu.acc_z -= mpu_offset.acc_z;

		//calculate roll and pitch angle form ACC data
		acc_roll  = atan2(mpu.acc_x, mpu.acc_z);
		acc_pitch = atan2(mpu.acc_y, mpu.acc_z);
		//acc_angle *= (180/3.1415);

		//Estimate now state with updated sensor data
		kalman_innovate(&pitch_data, acc_pitch, mpu.gyro_x);
		kalman_innovate(&roll_data, acc_roll, mpu.gyro_y);

		/* The new kalman estimate is now stored in pitch_data.x1, pitch_data.x2, pitch_data.x3
		  	   								    roll_data.x1,  roll_data.x2,  roll_data.x3
		*/


		//!The uAC_Task() must be called periodically
		uac_task();
		//!If there are outgoing chars, send them
		if (uac_txavailable() && (USART_GetFlagStatus(USART1, USART_FLAG_TXE)))
		{
			//The ISR disables itself after the last char from the TX buffer is sent
			USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		}
	}
}



void CalibrateACC()
{
	int i;
	int neutralX = 0;
	int neutralY = 0;
	int neutralZ = 0;

	for(i = 0; i < 128; i++)
	{
		SPI1_read(ACCEL_XOUT_H ,mpu.bytes,14);
		neutralX += mpu.acc_x;
		neutralY += mpu.acc_y;
		neutralZ += mpu.acc_z;
		Delay(10);
	}

	mpu_offset.acc_x = neutralX / 128;
	mpu_offset.acc_y = neutralY / 128;
	mpu_offset.acc_z = neutralZ / 128;
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

	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

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
	//
	//  /* Enable the USART2 Interrupt */
	//  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//  NVIC_Init(&NVIC_InitStructure);


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

