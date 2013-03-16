/*
 * UART.c
 *
 *  Created on: Sep 23, 2012
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "UART.h"

uint8_t tx_buffer[256];
uint8_t read_index = 0;
uint8_t write_index = 0;

uint8_t receive_buffer[256];
uint8_t rx_write_index = 0;
uint8_t rx_read_index = 0;
uint8_t cr = 0;
uint8_t lf = 0;

uint8_t AT_cmd_OK = 0;
uint8_t AT_cmd_ERROR_0 = 0;
uint8_t AT_cmd_ERROR_16 = 0;
uint8_t AT_cmd_ERROR_17 = 0;
uint8_t AT_cmd_FAIL = 0;

char at_cmdlib[10][20] = {"OK","ERROR(0)","ERROR(16)","ERROR(17)","FAIL","ERROR(0)","ERROR(0)","ERROR(0)","ERROR(0)","ERROR(0)"};
#define AT_CmdLibLength 2


/*******************************************************************************
 * Function Name  : USART3_Configuration
 * Description    : Configures the USART3 peripheral.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void UART3_Configuration(uint16_t baudrate)
{
	/* USART3 configuration ------------------------------------------------------*/
	/* USART3 configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
	 */
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudrate;
	//This is the word length including the parity bit
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure the USART3 */
	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	//receive interrupt enabled

	/* Enable USART3 */
	USART_Cmd(USART3, ENABLE);
}

uint8_t tx_available()
{
	if(read_index != write_index)
		return 1;
	else
		return 0;
}

char tx_char()
{
	uint8_t tx_char = tx_buffer[read_index];
	read_index++;
	return tx_char;
}

void txsendbuffer(uint8_t *msg, int length)
{
	int i;
	//while(*msg != '\0')
	for(i = 0 ; i < length; i++)
	{
		tx_buffer[write_index] = *msg;
		msg++;
		write_index++;
	}

	//add end message character
	tx_buffer[write_index] = 0;
	write_index++;
}

void store_received_byte(uint8_t byte)
{

	if(byte == 0x0D)
		cr = 1;
	else
	{
		if(cr == 1 && byte == 0x0A)
		{
			lf = 1;
		}
		else
		{
			cr = 0;
			lf = 0;
		}
	}
	if(lf == 0)
	{
		receive_buffer[rx_write_index] = byte;
		rx_write_index++;
	}
	else
	{
		process_rx_msg(rx_write_index);
		rx_write_index = 0;
		lf = 0;
	}
}


void process_rx_msg(uint8_t write_index)
{
	uint8_t i;
	char *at_receive;
	receive_buffer[rx_write_index - 1] = '\0';
	at_receive = &receive_buffer[rx_read_index];

	for (i=0;i<AT_CmdLibLength;i++)
	{
		if(at_strcmp(at_receive, at_cmdlib[i]))
			break;
	}
	if (i==AT_CmdLibLength)
	{
		//unknown response
	}
	switch(i)
	{
	case 0:
		AT_cmd_OK = 1;
		break;
	case 1:
		break;
	case 3:
		AT_cmd_ERROR_17 = 1;
		break;
	default:
		break;
	}
}


int at_strcmp (char *a, char *b)
{
	unsigned int i;
	int Ret=1;

	for (i=0;a[i]!='\0' && b[i]!='\0';i++)
	{
		if ((0x60 | a[i])!=(0x60 | b[i])) Ret=0;
	}
	if (a[i]!=b[i]) Ret=0;

	return Ret;
}


void BT_send_AT_command(char * AT_command)
{
	while(*AT_command != '\0')
	{
		tx_buffer[write_index] = *AT_command;
		AT_command++;
		write_index++;
	}
	tx_buffer[write_index] = 0x0D;
	write_index++;
	tx_buffer[write_index] = 0x0A;
	write_index++;

	//The ISR disables itself after the last char from the TX buffer is sent
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}



