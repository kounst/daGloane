/*
 * UART.h
 *
 *  Created on: Sep 23, 2012
 *      Author: konstantin
 */

void UART3_Configuration(uint16_t);
uint8_t tx_available();
char tx_char();
void txsendbuffer(uint8_t *, int);
void process_rx_msg(uint8_t);

enum _at_resp
{
	none,
	OK,
	ERROR_16,
	ERROR_17,
	FAIL,
	OTHER
};
