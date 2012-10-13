// Header:
// File Name: 
// Author:
// Date:


#include "stm32f10x.h"
#include "UART.h"

volatile char rx_command[50];

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
  //This is the word length including the stop bit
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


void uart_parser(uint8_t rx_byte)
{
	//static char rx_command[50];
	static byte_count = 0;

	TIM3_Update(0,rx_byte*8);

//	rx_command[byte_count] = rx_byte;
//	byte_count++;
//	if(byte_count >= 50 || rx_byte == '\0')
//		byte_count = 0;


}


