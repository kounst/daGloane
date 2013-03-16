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
#include <stdlib.h>
#include "stm32f10x.h"
#include "main.h"
#include "GPIO.h"
#include "UART.h"
#include "cobs.h"
#include "TIM.h"


/* Private typedef */
/* Private define  */



/* Private macro */
/* Private variables */

_pwm pulswidth;
_pwm neutral;

//union pwm pulswidth, neutral;
extern uint8_t tick;
extern uint8_t ppm_decode;

extern uint8_t AT_cmd_OK;
extern uint8_t AT_cmd_ERROR_17;

/* Private function prototypes */
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

	UART3_Configuration(38400);

	TIM4_Configuration();

	/* Systick Configuration */
	SysTick_Configuration();


	while(pulswidth.puls.sync < 10);

	Calibrate();

	/* Try to connect to copter */
	BT_send_AT_command("AT+init");
	while(AT_cmd_OK != 1 && AT_cmd_ERROR_17 != 1);
	AT_cmd_OK = 0;
	AT_cmd_ERROR_17 = 0;
	BT_send_AT_command("AT+pair=0015,E9,006DD9,5");
	while(AT_cmd_OK != 1);
	AT_cmd_OK = 0;
	BT_send_AT_command("AT+link=0015,E9,006DD9");
	while(AT_cmd_OK != 1);
	AT_cmd_OK = 0;


	/* Infinite loop */
	while (1)
	{
		if(ppm_decode == 1)
		{
			ppm_decode = 0;
			uint8_t puls[14];

			tobytearray(&pulswidth, &neutral, puls, 7);


			if(pulswidth.puls.sync == 10)
			{
				send_msg(1, puls, 14);

				//The ISR disables itself after the last char from the TX buffer is sent
				USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
				LEDToggle(LED1);
			}

		}
		/*//If there are outgoing chars, send them
		if (tx_available() && (USART_GetFlagStatus(USART3, USART_FLAG_TXE)))
		{
			//The ISR disables itself after the last char from the TX buffer is sent
			USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
		}*/
	}
}


void tobytearray(_pwm *upuls, _pwm *uneutral, uint8_t *spuls, uint8_t length)
{
	int i;
	for(i = 0; i< length; i++)
	{
		spuls[2*i] = ((int16_t)upuls->pw[i] - (int16_t)uneutral->pw[i])>>8;
		spuls[2*i + 1] = (int16_t)upuls->pw[i] - (int16_t)uneutral->pw[i];
	}


}


void Calibrate()
{
  int i;
  long int neutral1 = 0;
  long int neutral2 = 0;
  long int neutral3 = 0;
  long int neutral4 = 0;
  long int neutral5 = 0;
  long int neutral6 = 0;
  long int neutral7 = 0;

  for(i = 0; i < 128; i++)
  {
    neutral1 += pulswidth.pw[0];
    neutral2 += pulswidth.pw[1];
    neutral3 += pulswidth.pw[2];
    neutral4 += pulswidth.pw[3];
    neutral5 += pulswidth.pw[4];
    neutral6 += pulswidth.pw[5];
    neutral7 += pulswidth.pw[6];
    Delay(20);
  }
  neutral.pw[0] = neutral1 / 128;
  neutral.pw[1] = neutral2 / 128;
  neutral.pw[2] = neutral3 / 128;
  neutral.pw[3] = neutral4 / 128;
  neutral.pw[4] = neutral5 / 128;
  neutral.pw[5] = neutral6 / 128;
  neutral.pw[6] = neutral7 / 128;
}


void send_msg(uint8_t msg_type, uint8_t *msg, uint8_t length)
{
	uint8_t i;
	uint16_t crc = 0;
	uint8_t *headermsg = alloca((length + 5) * sizeof(uint8_t));
	//uint8_t *fullmsg = alloca((length + 5) * sizeof(uint8_t));


	if((headermsg == NULL))// || (fullmsg == NULL))
	{

	}
	else
	{
		headermsg[0] = msg_type;
		headermsg[1] = length + 4;
		for(i = 0; i < length; i++)
		{
			headermsg[i + 2] = msg[i];
		}
		for(i = 0; i < (length + 2); i++)
		{
			crc = crc_xmodem_update(crc, headermsg[i]);
		}
		headermsg[i+1] = crc;
		headermsg[i] = (crc>>8);
		cobs_encode_(headermsg, length + 4);//, fullmsg);

		//txsendbuffer(fullmsg, length + 5);
		txsendbuffer(headermsg, length + 5);
	}
}


/**
 * @brief  CRC-XMODEM calculation
 * @param  CRC, DATA
 * @retval updated CRC
 */
uint16_t crc_xmodem_update(uint16_t crc, uint8_t data)
{
	int i;

	crc = crc ^ ((uint16_t)data << 8);
	for (i=0; i<8; i++)
	{
		if (crc & 0x8000)
			crc = (crc << 1) ^ 0x1021;
		else
			crc <<= 1;
	}
	return crc;
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |  RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

	/* USART3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* TIM4 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	/* ADC1 clock enable */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/* SPI1 clock enable */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
}

/**
 * @brief  Configures the nested vectored interrupt controller.
 * @param  None
 * @retval None
 */
void NVIC_Configuration()
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the TIM4 gloabal interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//	NVIC_Init(&NVIC_InitStructure);
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

