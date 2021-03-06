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
#include "ADC.h"
#include "UART.h"
#include "uAC.h"
#include "TIM.h"
#include "com.h"

/** @addtogroup STM32F10x_StdPeriph_Template
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


uint16_t lipo_voltage = 2860; 	//3V
extern uint8_t tick;			// main loop trigger



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
		LED_update(0,1000);
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
	/*	Checks whether the push-bottom is being held down and turns of the power if
	 * 	it is released after more than 1 second
	 */
	PWR_Buttom_handler();

	HeartBeat();

	/*	This is sort of a low pass filter
	 *  Its characteristic is not great but OK for this application
	 */
	if(lipo_voltage > ADC_GetConversionValue(ADC1))
		lipo_voltage--;
	else
		lipo_voltage++;

	TimingDelay_Decrement();  			//Decrement ms counter of Delay() function

	tick=1;								// main loop trigger
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
 * @brief  This function handles USART1 interrupt request.
 * @param  None
 * @retval None
 */
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)	// if this is a transmit interrupt..
	{
		if(uac_txavailable())
		{
			USART_SendData(USART1, uac_tx());
		}
		else
		{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		}
	}

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	// if this is a receive interrupt..
	{
		/* Hand over the char to uAC
		 * We are using only 7 data bits
		 * So we only keep bit 0..6
		 */
		uac_rx(0x7F & USART_ReceiveData(USART1));
	}
}


/**
 * @brief  This function handles USART2 interrupt request.
 * @param  None
 * @retval None
 */
void USART2_IRQHandler(void)
{
	char byte;
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)	// if this is a transmit interrupt..
	{
		if(is_send_buffer_empty())
		{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
		}
		else
		{
			USART_SendData(USART2, get_buffer_byte());
		}
	}

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)	// if this is a receive interrupt..
	{
		//uac_printf("BT: ");
		byte = USART_ReceiveData(USART2);
		//uac_printf("%i",byte);
		//USART_SendData(USART1, byte);
		store_received_byte(byte);
	}
}


/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
void SPI_IRQHandler(void)
{

}



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
