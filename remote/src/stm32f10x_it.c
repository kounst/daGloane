/**
 ******************************************************************************
 * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
 * @author  MCD Application Team
 * @version V3.5.0
 * @date    08-April-2011
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "GPIO.h"
#include "main.h"
#include "TIM.h"
#include "UART.h"


extern struct pwm pulswidth;
uint8_t tick = 0;
uint8_t ppm_decode = 0;
uint8_t rx_byte = 0;

/** @addtogroup STM32F10x_StdPeriph_Template
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
	tick = 1;

	TimingDelay_Decrement();  			//Decrement ms counter of Delay() function
	//LEDToggle(LED1);
}


/**
 * @brief  This function handles USART2 interrupt request.
 * @param  None
 * @retval None
 */
void USART3_IRQHandler(void)
{
	//uint8_t rx_byte;
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)	// if this is a transmit interrupt..
	{
		if(tx_available())
			USART_SendData(USART3, tx_char());
		else
			USART_ITConfig(USART3, USART_IT_TXE, DISABLE);

	}

	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)	// if this is a receive interrupt..
	{
		rx_byte = USART_ReceiveData(USART3);
		store_received_byte(rx_byte);
	}
}


/**
 * @brief  This function handles TIM4 interrupt request.
 * @param  None
 * @retval None
 */
void TIM4_IRQHandler(void)
{
	static uint16_t IC4Value, lastIC4Value;
	static uint8_t channel = 0;

	if(TIM_GetITStatus(TIM4, TIM_IT_CC4) == SET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
		LEDToggle(LED2);




		IC4Value = TIM_GetCapture4(TIM4);
		uint16_t length = IC4Value - lastIC4Value;
		if(length > 20000)
		{
			channel = 0;

			if(pulswidth.sync < 10)
				pulswidth.sync++;
			lastIC4Value = IC4Value;
			channel++;
		}
		else
		{
			if((length < 8500) && (length > 3500))
			{
				switch(channel)
				{
				case 1:
					pulswidth.pw1 = length;

					break;
				case 2:
					pulswidth.pw2 = length;

					break;
				case 3:
					pulswidth.pw3 = length;
					break;
				case 4:
					pulswidth.pw4 = length;

					break;
				case 5:
					pulswidth.pw5 = length;

					break;
				case 6:
					pulswidth.pw6 = length;

					break;
				case 7:
					pulswidth.pw7 = length;
					ppm_decode = 1;
					break;
				default:
					channel = 0;
					if(pulswidth.sync > 0)
						pulswidth.sync--;
					break;
				}
				lastIC4Value = IC4Value;
				channel++;
			}
			else
			{
				pulswidth.sync = 0;
			}
		}

	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
{
}*/

/**
 * @}
 */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
