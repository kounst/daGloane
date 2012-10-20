/*
 * main.h
 *
 *  Created on: Oct 20, 2012
 *      Author: konstantin
 */

#ifndef MAIN_H_
#define MAIN_H_

//We have to consider the endianness of the plattform here.
//bytes[0] is the low  byte of gyro_z
//bytes[1] is the high byte of gyro_z
union _mpudata
{
	uint8_t bytes[14];
	//struct { int16_t gyro_z, gyro_y, gyro_x, temp, acc_z, acc_y, acc_x; } words;
	int16_t gyro_z, gyro_y, gyro_x, temp, acc_z, acc_y, acc_x;
};

typedef union _mpudata mpudata;


/* Function prototypes */
void RCC_Configuration(void);
void NVIC_Configuration(void);
void CalibrateACC(void);


#endif /* MAIN_H_ */
