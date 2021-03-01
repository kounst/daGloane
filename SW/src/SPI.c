/*
 * SPI.c
 *
 *  Created on: Sep 23, 2012
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "SPI.h"
#include "TIM.h"
#include "main.h"

SPI_HandleTypeDef hspi1;


void SPI1_Configuration()
{
	hspi1.Instance = SPI1;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	//hspi1.Init.SPI_CRCPolynomial = 7;
	HAL_SPI_Init(&hspi1);

	/* Enable SPI1 */
	//SPI_Cmd(SPI1, ENABLE);
	__HAL_SPI_ENABLE(&hspi1);

	HAL_Delay(100);		// wait for MPU-6000 to be ready to perform read/write operations


	SPI1_writebyte(PWR_MGMT_1, DEVICE_RESET);

	HAL_Delay(100);

	SPI1_writebyte(USER_CTRL, I2C_IF_DIS);	//disable the MPU's I2C interface
	SPI1_writebyte(PWR_MGMT_1, 0x03);		//use Z axis resonator as a clock source
	SPI1_writebyte(ACCEL_CONFIG, FS_SEL_0);
	SPI1_writebyte(GYRO_CONFIG, FS_SEL_3);

	HAL_Delay(100);

}


uint8_t SPI1_readbyte(uint8_t address)
{
	uint8_t temp = 0;

	CS_LOW;

	SPI1->DR = 0x80 | address;

	while( __HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE) == RESET );

	SPI1->DR = 0x00;

	while( __HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE) == RESET );

	temp = SPI1->DR;

	while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE) == RESET);
	while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY) == SET);

	temp = SPI1->DR;

	CS_HIGH;

	return temp;
}


/**
 * @brief  Reads the specified number of bytes starting form a specified address
 * @param  uint8_t start_address: address to start reading form slave device
 * @param  uint8_t *bytearray: startaddress of an array to hold the read data
 * @param  uint8_t NofBytes: Number of bytes to read

 * @retval none
 */
void SPI1_read(uint8_t start_address, uint8_t *bytearray, uint8_t NofBytes)
{
	CS_LOW;

	SPI1->DR = 0x80 | start_address;

	while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE) == RESET);

	SPI1->DR = 0x00;

	while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE) == RESET);

	*bytearray = SPI1->DR;

	while(NofBytes - 1)
	{
		while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE) == RESET);
		SPI1->DR = 0x00;
		while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE) == RESET);
		*bytearray = SPI1->DR;
		bytearray++;

		NofBytes--;
	}

	while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE) == RESET);
	while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY) == SET);

	*bytearray = SPI1->DR;

	CS_HIGH;
}

void MPU_read(mpudata *mpu)
{
	uint8_t bytes[14];
	SPI1_read(ACCEL_XOUT_H, bytes, 14);

	mpu->acc_x = (bytes[0] << 8) | bytes[1];
	mpu->acc_y = (bytes[2] << 8) | bytes[3];
	mpu->acc_z = (bytes[4] << 8) | bytes[5];
	mpu->temp =  (bytes[6] << 8) | bytes[7];
	mpu->temp /= 340;
	mpu->temp += 36.53;
	mpu->gyro_x = (bytes[8] << 8) | bytes[9];
	mpu->gyro_y = (bytes[10] << 8) | bytes[11];
	mpu->gyro_z = (bytes[12] << 8) | bytes[13];
}


/**
 * @brief  Writes a byte to the specified data register
 * @param  uint8_t address: register address to write to
 * @param  uint8_t byte: data byte to write to specified data register
 * @retval none
 */
void SPI1_writebyte(uint8_t address, uint8_t byte)
{
	CS_LOW;

	/* Wait for SPI1 Tx buffer empty */
	while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE) == RESET);

	SPI1->DR = address;

	while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE) == RESET);

	SPI1->DR = byte;

	while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY) == SET);

	CS_HIGH;
}
