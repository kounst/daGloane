/*
 * SPI.c
 *
 *  Created on: Sep 23, 2012
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "SPI.h"
#include "TIM.h"
#include "main.h"




void SPI1_Configuration()
{
	SPI_InitTypeDef   SPI_InitStructure;

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	//SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);

	/* Enable SPI1 */
	SPI_Cmd(SPI1, ENABLE);

	Delay(100);		// wait for MPU-6000 to be ready to perform read/write operations


	SPI1_writebyte(PWR_MGMT_1, DEVICE_RESET);

	Delay(100);

	SPI1_writebyte(USER_CTRL, I2C_IF_DIS);	//disable the MPU's I2C interface
	SPI1_writebyte(PWR_MGMT_1, 0x03);		//use Z axis resonator as a clock source

	Delay(100);

}


uint8_t SPI1_readbyte(uint8_t address)
{
	uint8_t temp = 0;

	CS_LOW;

	SPI_I2S_SendData(SPI1, 0x80 | address);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	SPI_I2S_SendData(SPI1, 0x00);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

	temp = SPI_I2S_ReceiveData(SPI1);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

	temp = SPI_I2S_ReceiveData(SPI1);

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

	SPI_I2S_SendData(SPI1, 0x80 | start_address);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	SPI_I2S_SendData(SPI1, 0x00);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

	*bytearray = SPI_I2S_ReceiveData(SPI1);

	while(NofBytes - 1)
	{
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI1, 0x00);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		*bytearray = SPI_I2S_ReceiveData(SPI1);
		bytearray++;

		NofBytes--;
	}

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

	*bytearray = SPI_I2S_ReceiveData(SPI1);

	CS_HIGH;
}

void MPU_read(mpudata *mpu)
{
	uint8_t bytes[14];
	SPI1_read(ACCEL_XOUT_H, bytes, 14);

	mpu->acc_x = (bytes[0] << 8) | bytes[1];
	mpu->acc_y = (bytes[2] << 8) | bytes[3];
	mpu->acc_z = (bytes[4] << 8) | bytes[5];
	mpu->temp = (bytes[6] << 8) | bytes[7];
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
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	SPI_I2S_SendData(SPI1, address);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	SPI_I2S_SendData(SPI1, byte);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

	CS_HIGH;
}
