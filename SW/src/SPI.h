/*
 * SPI.h
 *
 *  Created on: Sep 23, 2012
 *      Author: konstantin
 */

#ifndef SPI_H_
#define SPI_H_



#endif /* SPI_H_ */



#define READ				0x80	//MSB to select read or write operation
#define WHO_AM_I			0x75	//WHO_AM_I register
#define ACCEL_XOUT_H		0x3B	//ACC  X-Axis high byte register
#define ACCEL_XOUT_L		0x3C	//ACC  X-Axis low byte register
#define ACCEL_YOUT_H		0x3D	//ACC  Y-Axis high byte register
#define ACCEL_YOUT_L		0x3E	//ACC  Y-Axis low byte register
#define ACCEL_ZOUT_H		0x3F	//ACC  Z-Axis high byte register
#define ACCEL_ZOUT_L		0x40	//ACC  Z-Axis low byte register
#define	TEMP_OUT_H			0x41	//Temp high byte register
#define TEMP_OUT_L			0x42	//Temp low byte register
#define GYRO_XOUT_H			0x43	//Gyro X-Axis high byte register
#define GYRO_XOUT_L			0x44	//Gyro X-Axis low byte register
#define GYRO_YOUT_H			0x45	//Gyro Y-Axis high byte register
#define GYRO_YOUT_L			0x46	//Gyro Y-Axis low byte register
#define GYRO_ZOUT_H			0x47	//Gyro Z-Axis high byte register
#define GYRO_ZOUT_L			0x48	//Gyro Z-Axis low byte register
#define USER_CTRL			0x6A	//user control register
	#define I2C_IF_DIS		0x10		//user control register I2C interface disable bit
#define PWR_MGMT_1			0x6B	//Pwr_Mgmt Register 1
	#define DEVICE_RESET	0x80		//Pwr_Mgmt DEVICE_RESET bit
#define	PWR_MGMT_2			0x6C	//Pwr_Mgmt Register 2

#define CS_LOW				GPIOA->BRR = GPIO_Pin_4;
#define CS_HIGH				GPIOA->BSRR = GPIO_Pin_4;


void SPI1_Configuration(void);
uint8_t MPU_ReadByte(void);
uint8_t MPU_SendByte(uint8_t);
void SPI1_read(uint8_t, uint8_t *, uint8_t);
uint8_t SPI1_readbyte(uint8_t);
