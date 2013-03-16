/*
 * com.c
 *
 *  Created on: Nov 17, 2012
 *      Author: konstantin
 */


#include "stm32f10x.h"
#include "com.h"
#include "cobs.h"
#include "alloca.h"
#include "uac.h"
#include "TIM.h";


uint8_t send_buffer[256];
uint8_t receive_buffer[256];
uint8_t cobs_decoded_msg[255];
uint8_t rx_write_index = 0;
uint8_t read_pointer = 0;
uint8_t write_pointer = 0;



msg1 control_msg;




// private function prototypes
uint16_t crc_xmodem_update(uint16_t crc, uint8_t data);
void process_rx_msg(uint8_t rx_msg_length);




void send_data(uint8_t type, uint8_t *bytearray, uint8_t length)
{
	uint8_t i;
	uint16_t crc = 0;

	uint8_t sendarray[255];
	//uint8_t *sendarray = alloca(length + 5);

	sendarray[0] = type;
	sendarray[1] = length + 4;				//send along the total length including msg type, length byte, and check sum

	crc = crc_xmodem_update(crc, type);		//crc checksum
	crc = crc_xmodem_update(crc, length + 4);

	for(i = 0; i < length; i++)
	{
		crc = crc_xmodem_update(crc, bytearray[i]);
		sendarray[i + 2] = bytearray[i];
	}
	sendarray[length + 2] = (crc >> 8);
	sendarray[length + 3] = crc;

	cobs_encode_(sendarray, length + 4);	//COBS

	send_to_buffer(sendarray, length + 5, 1);
}



void send_to_buffer(uint8_t *sendarray, uint8_t send_length, uint8_t add_zero)
{
	uint8_t i;
	for(i = 0; i < send_length; i++)
	{
		send_buffer[write_pointer] = sendarray[i];
		write_pointer++;
	}
	if(add_zero)
	{
		send_buffer[write_pointer] = 0;		//write 0 byte to indicate end of frame
		write_pointer++;
	}

	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);	//enable TXE interrupt to initiate UART transmission
}

uint8_t is_send_buffer_empty (void)
{
	return (write_pointer == read_pointer);
}

uint8_t get_buffer_byte(void)
{
	uint8_t byte;
	byte = send_buffer[read_pointer];
	read_pointer++;
	return byte;
}


void store_received_byte(uint8_t byte)
{
	if(byte != 0)
	{
		receive_buffer[rx_write_index] = byte;
		rx_write_index++;
	}
	else
	{
		process_rx_msg(rx_write_index);
		rx_write_index = 0;
	}
}

void process_rx_msg(uint8_t rx_msg_length)
{
	//TODO make sure the receive_buffer is not written while we are still reading/decoding the previous message

	uint8_t decoded_length;
	uint16_t crc = 0;
	uint8_t i;

	decoded_length = cobs_decode(receive_buffer, rx_msg_length, cobs_decoded_msg);

	if(decoded_length)	//if cobs_decoding successful
	{
		for(i = 0; i < decoded_length; i++)
		{
			crc = crc_xmodem_update(crc, cobs_decoded_msg[i]);
		}

		if(!crc)		//if crc == 0
		{
			switch(cobs_decoded_msg[0])	//which message type?
			{
			case 1:
				if(decoded_length >= 13)
				{
					control_msg.roll = (cobs_decoded_msg[2] << 8) | cobs_decoded_msg[3];
					control_msg.nick = (cobs_decoded_msg[4] << 8) | cobs_decoded_msg[5];
					control_msg.yaw = (cobs_decoded_msg[6] << 8) | cobs_decoded_msg[7];
					control_msg.throttle = (cobs_decoded_msg[8] << 8) | cobs_decoded_msg[9];
					control_msg.control = cobs_decoded_msg[10];

					//uac_printf("testmsg: %i , %i , %i, %i , %i",control_msg.control, control_msg.nick, control_msg.roll, control_msg.throttle, control_msg.yaw);
					PWM_update(3,(control_msg.throttle+4000)/4);
				}
				else
				{
					uac_printf("incorrect message length");
				}
				break;

			case 2:
				break;

			default:
				break;
			}
		}
		else
		{
			//TODO error handling if crc check fails
			uac_printf("CRC check failed");
		}
	}
	else
	{
		//TODO error handling if cobs_decoding is unsuccessful
		uac_printf("COBS decoding failed");
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
