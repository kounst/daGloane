/*
 * UART.h
 *
 *  Created on: Sep 23, 2012
 *      Author: konstantin
 */

#define USART1_DR_Base	(USART1_BASE | 0x04)

#define countof(a)   (sizeof(a) / sizeof(*(a)))
#define TxBufferSize   (countof(uart_tx_buffer) - 1)

void UART1_Configuration(void);
void UART2_Configuration(void);
void UART2_Configuration_AT(uint32_t);
