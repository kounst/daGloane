/*
 * com.h
 *
 *  Created on: Nov 17, 2012
 *      Author: konstantin
 */

#ifndef COM_H_
#define COM_H_

uint16_t crc_xmodem_update(uint16_t crc, uint8_t data);
void send_data(uint8_t type, uint8_t *bytearray, uint8_t length);
void send_to_buffer(uint8_t *sendarray, uint8_t send_length);
uint8_t is_send_buffer_empty (void);
uint8_t get_buffer_byte(void);


typedef struct _msg1{
	int16_t roll;
	int16_t nick;
	int16_t yaw;
	int16_t throttle;
	int16_t control;	//tbd
}msg1;




#endif /* COM_H_ */
