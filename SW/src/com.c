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


uint8_t send_buffer[256];
uint8_t read_pointer = 0;
uint8_t write_pointer = 0;





void send_data(uint8_t type, uint8_t *bytearray, uint8_t length)
{
	uint8_t i;
	uint8_t *presendarray = alloca(length + 4);	// clear data array
	uint8_t *sendarray = alloca(length + 5);
	uint16_t crc = 0;

	crc = crc_xmodem_update(crc, type);		//crc checksum
	crc = crc_xmodem_update(crc, length);

	presendarray[0] = type;
	presendarray[1] = length;

	for(i = 0; i < length; i++)
	{
		crc = crc_xmodem_update(crc, bytearray[i]);
		presendarray[i + 2] = bytearray[i];
	}

	presendarray[length + 2] = (crc >> 8);
	presendarray[length + 3] = crc;

	cobs_encode(presendarray, length + 4, sendarray);	//COBS

	send_to_buffer(sendarray, length + 5);
}



void send_to_buffer(uint8_t *sendarray, uint8_t send_length)
{
	uint8_t i;
	for(i = 0; i < send_length; i++)
	{
		send_buffer[write_pointer] = sendarray[i];
		write_pointer++;
	}

	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);	//enable TXE interrupt to initiate uart transmission
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
