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

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

extern volatile char uart_buffer[];
uint16_t lipo_voltage = 3810; 	//4V

extern volatile uint8_t SPI_MASTER_Buffer_Tx[20];
extern volatile uint8_t SPI_MASTER_Buffer_Rx[20];
extern uint8_t BytesToSend;

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
	static uint16_t TurnOff_count = 1000;

	//LEDToggle(LED2);

	if(debounce(GPIOA->IDR & 2))		//tactile switch input
	{
		//LEDOn(LED1);
		//GPIOB->BSRR = GPIO_Pin_0;		//set Mot1
		if(TurnOff_count)
		{
			TurnOff_count--;
			if(!(TurnOff_count % 100))
				uac_printf("TurnOff_count: %i\n", TurnOff_count/100);
			if(!TurnOff_count)
				uac_printf("\nBye-bye!\n");
		}
	}
	else
	{
		if(!TurnOff_count)
		{
			GPIOB->BRR = GPIO_Pin_2;	//turn off DCDC
		}
		else
		{
			TurnOff_count = 1000;		//reset TurnOff delay
		}
	}


	if(lipo_voltage > ADC_GetConversionValue(ADC1))
		lipo_voltage--;
	else
		lipo_voltage++;


	GPIOB->ODR ^= GPIO_Pin_3;
	GPIOA->ODR ^= GPIO_Pin_15;
	GPIOB->ODR ^= GPIO_Pin_4;

	TimingDelay_Decrement();  			//Decrement ms counter of Delay() function
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
	static uint16_t TxCounter = 0;


	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)	// if this is a transmit interrupt..
	{
//		/* Write one byte to the transmit data register */
//		USART_SendData(USART1, uart_buffer[TxCounter++]);
//
//		if(TxCounter == 499 || uart_buffer[TxCounter] == '\0')
//		{
//			/* Disable the USART1 Transmit interrupt */
//			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
//			TxCounter = 0;
//		}


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
//		uart_parser(USART_ReceiveData(USART1));

		//!Hand over the char to uAC
		//We are using only 7 data bits
		//So we only keep bit 0..6
		uac_rx(0x7F & USART_ReceiveData(USART1));


	}
	USART_ClearITPendingBit(USART1, USART_IT_TXE);
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}


/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
void SPI_IRQHandler(void)
{
	static uint8_t TxIdx = 0;
	static uint8_t RxIdx = 0;
	if(SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_TXE) != RESET)
	{
		/* Send SPI_MASTER data */
		SPI_I2S_SendData(SPI1, SPI_MASTER_Buffer_Tx[TxIdx++]);

		/* Disable SPI_MASTER TXE interrupt */
		if (TxIdx == BytesToSend)
		{
			TxIdx = 0;
			SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
		}
	}

	if(SPI_I2S_GetITStatus(SPI1,SPI_I2S_IT_RXNE) != RESET)
	{
		/* Store SPI received data */
		SPI_MASTER_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI1);

		if(RxIdx == BytesToSend)
		{
			RxIdx = 0;
			GPIOA->BSRR = GPIO_Pin_4;
		}
	}

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
