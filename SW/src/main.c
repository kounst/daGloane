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

/* Includes */
#include <stddef.h>
#include "stm32f10x.h"
#include "GPIO.h"
#include "UART.h"
#include "ADC.h"
#include "TIM.h"
#include "SPI.h"
#include "uAC.h"




/* Private typedef */
/* Private define  */


/* Private macro */
/* Private variables */
static __IO uint32_t TimingDelay;

/* Global variables */
volatile char uart_buffer[500];
extern uint16_t lipo_voltage;
extern char rx_command[50];



int16_t acc_x, acc_y, acc_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temp;

/* Private function prototypes */
void RCC_Configuration(void);
void NVIC_Configuration(void);
void SysTick_Configuration(void);
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

void Hello_CMD (int argc, char *argv[]);
void get_MPU6000_data(int argc, char *argv[]);
void get_LiPoVoltage(int argc, char *argv[]);
void get_Switch(int argc, char *argv[]);
void PwrOff(int argc, char *argv[]);

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
	uint16_t lipo_voltage_mv;


	union gyrodata
	{
		uint8_t bytes[14];
		uint16_t words[7];
	}gyro;

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


	uac_printf("Hello, my name is daGloane\n\r");

	/* Infinite loop */
	while (1)
	{
		//Delay(1);

		//!The uAC_Task() must be called periodically
		uac_task();

		SPI1_read(ACCEL_XOUT_H ,gyro.bytes,14);
		acc_x = (gyro.bytes[0] << 8) | gyro.bytes[1];
		acc_y = (gyro.bytes[2] << 8) | gyro.bytes[3];
		acc_z = (gyro.bytes[4] << 8) | gyro.bytes[5];
		temp = (gyro.bytes[6] << 8) | gyro.bytes[7];
		gyro_x = (gyro.bytes[8] << 8) | gyro.bytes[9];
		gyro_y = (gyro.bytes[10] << 8) | gyro.bytes[11];
		gyro_z = (gyro.bytes[12] << 8) | gyro.bytes[13];

		//!If there are outgoing chars, send them
		if (uac_txavailable() && (USART_GetFlagStatus(USART1, USART_FLAG_TXE)))
		{
			USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		}
	}
}




//A console test command.
void Hello_CMD (int argc, char *argv[])
{
	uac_printf("Hello World!\n");
	int i;
	for (i=0;i<argc;i++)
	{
		uac_printf("%i: %s\n",i,argv[i]);
	}

}


void PwrOff(int argc, char *argv[])
{
	uac_printf("\nBye-bye!\n");
	while(uac_txavailable());	//wait for uac string to be sent
	GPIOB->BRR = GPIO_Pin_2;	//turn off DCDC
}




void get_MPU6000_data(int argc, char *argv[])
{
	if(!argc)	//if they didn't give us a parameter
	{
				//give them everything!
		uac_printf("All data the MPU-6000 provides: \n");
		uac_printf("acc_x:  %i\ngyro_x: %i\n",acc_x, gyro_x);
		uac_printf("acc_y:  %i\ngyro_y: %i\n",acc_y, gyro_y);
		uac_printf("acc_z:  %i\ngyro_z: %i\n",acc_z, gyro_z);
		uac_printf("Temp: %i\n",temp);
	}
	else
	{
		//which axis do they want to know about?
		switch (*argv[0])
		{
			case 'x':
				uac_printf("acc_x:  %i\ngyro_x: %i\n",acc_x, gyro_x);

				break;
			case 'y':
				uac_printf("acc_y:  %i\ngyro_y: %i\n",acc_y, gyro_y);

				break;
			case 'z':
				uac_printf("acc_z:  %i\ngyro_z: %i\n",acc_z, gyro_z);

				break;
			case 't':
				uac_printf("Temp: %i\n",temp);

				break;
			default:
				break;
		}
	}
}


void get_Switch(int argc, char *argv[])
{
	char *state;
	switch (debounce(GPIOA->IDR & 2))
				{
	case 1:
		state = "ON";
		break;
	case 0:
		state = "OFF";
		break;
	default:
		break;
				}
	uac_printf("SwitchState: %s",state);
}


void get_LiPoVoltage(int argc, char *argv[])
{
	uac_printf("LiPo_Voltage: %2fV\n",(float)lipo_voltage/952.558);
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

/**
 * @brief  Configures the SysTick.
 * @param  None
 * @retval None
 */
void SysTick_Configuration(void)
{

	/* Setup SysTick Timer for 1 msec interrupts  */
	if (SysTick_Config(SystemCoreClock / 1000))
	{
		/* Capture error */
		while (1);
	}


}

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in milliseconds.
 * @retval None
 */
void Delay(__IO uint32_t nTime)
{
	TimingDelay = nTime;

	while(TimingDelay != 0);
}

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
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

