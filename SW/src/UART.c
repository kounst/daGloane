/*
 * UART.c
 *
 *  Created on: Sep 23, 2012
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "UART.h"



char uart_tx_buffer[255] = "Hello, my name is daGloane\n\n";



/*******************************************************************************
 * Function Name  : USART1_Configuration
 * Description    : Configures the USART1 peripheral.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void UART1_Configuration()
{
	/* USART1 configuration ------------------------------------------------------*/
	/* USART1 configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - Odd parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
	 */
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;	//115200Baud/s
	//This is the word length including the parity bit
	//So its actually only 7 bits of data!
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Odd;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure the USART1 */
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//receive interrupt enabled

	/* Enable USART1 */
	USART_Cmd(USART1, ENABLE);
}


/*******************************************************************************
 * Function Name  : USART1_Configuration
 * Description    : Configures the USART1 peripheral.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void UART1_Configuration2()
{
	/* USART1 configuration ------------------------------------------------------*/
	/* USART1 configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - Odd parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
	 */
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 2000000;	//2000000Baud/s
	//This is the word length including the parity bit
	//So its actually only 7 bits of data!
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Odd;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure the USART1 */
	USART_Init(USART1, &USART_InitStructure);
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//receive interrupt enabled

	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

	/* Enable USART1 */
	USART_Cmd(USART1, ENABLE);
}





/*******************************************************************************
 * Function Name  : USART2_Configuration
 * Description    : Configures the USART2 peripheral.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void UART2_Configuration()
{
	/* USART2 configuration ------------------------------------------------------*/
	/* USART2 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - Odd parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
	 */
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;	//115200Baud/s
	//This is the word length including the parity bit
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure the USART2 */
	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	//receive interrupt enabled

	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);
}



void UART2_Configuration_AT(uint32_t baudrate)
{
	/* USART2 configuration ------------------------------------------------------*/
	/* USART2 configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - Odd parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
	 */
	USART_DeInit(USART2);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudrate;
	//This is the word length including the parity bit
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure the USART2 */
	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	//receive interrupt enabled

	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);
}


void UART1_DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  /* USART1 TX DMA1 Channel (triggered by USART1 Tx event) Config */
  DMA_DeInit(DMA1_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)uart_tx_buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = TxBufferSize;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);

/*   USART1 RX DMA1 Channel (triggered by USART1 Rx event) Config
  DMA_DeInit(USARTy_Rx_DMA_Channel);
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = TxBufferSize2;
  DMA_Init(USART1_Rx_DMA_Channel, &DMA_InitStructure);*/

    /* Enable USART1 TX DMA1 Channel */
  DMA_Cmd(DMA1_Channel4, ENABLE);

  /* Enable USART1 RX DMA1 Channel */
  //DMA_Cmd(USART1_Rx_DMA_Channel, ENABLE);
}


