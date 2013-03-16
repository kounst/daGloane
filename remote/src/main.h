/*
 * main.h
 *
 *  Created on: Oct 20, 2012
 *      Author: konstantin
 */

#ifndef MAIN_H_
#define MAIN_H_

union pulsw
{
  struct pwm
  {
    vu16 pw1;
    vu16 pw2;
    vu16 pw3;
    vu16 pw4;
    vu16 pw5;
    vu16 pw6;
    vu16 pw7;
    vu16 pw8;
    vu16 pw9;
    vu16 sync;
  }puls;
  vu16 pw[10];
};

typedef union pulsw _pwm;


/* Function prototypes */
void RCC_Configuration(void);
void NVIC_Configuration(void);
uint16_t crc_xmodem_update(uint16_t, uint8_t);
void send_msg(uint8_t, uint8_t *, uint8_t);
void Calibrate(void);
void tobytearray(_pwm *, _pwm *, uint8_t *, uint8_t);

#endif /* MAIN_H_ */
