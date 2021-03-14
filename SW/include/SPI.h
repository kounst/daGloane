/*
 * SPI.h
 *
 *  Created on: Sep 23, 2012
 *      Author: konstantin
 */

#ifndef SPI_H_
#define SPI_H_


struct _mpudata
{
	int16_t acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z, temp;
};

typedef struct _mpudata mpudata;


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
#define GYRO_CONFIG			0x1B	//GYRO_CONFIG Register
#define ACCEL_CONFIG		0x1C	//ACCEL_CONFIG Register
	#define FS_SEL_0		0x0
	#define FS_SEL_1		(0x1<<3)
	#define FS_SEL_2		(0x2<<3)
	#define FS_SEL_3		(0x3<<3)

#define CS_LOW				GPIOA->BRR = GPIO_PIN_4;
#define CS_HIGH				GPIOA->BSRR = GPIO_PIN_4;


void SPI1_Configuration(void);
void SPI1_read(uint8_t, uint8_t *, uint8_t);
uint8_t SPI1_readbyte(uint8_t);
void SPI1_read(uint8_t, uint8_t *, uint8_t);
void SPI1_writebyte(uint8_t, uint8_t);
void MPU_read(mpudata *mpu);
void MPU_read_IT();
void MX_SPI1_Init(void);





#endif /* SPI_H_ */
