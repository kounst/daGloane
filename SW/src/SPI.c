/*
 * SPI.c
 *
 *  Created on: Sep 23, 2012
 *      Author: konstantin
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "SPI.h"
#include "TIM.h"	//function Delay defined in TIM.c




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

	Delay(500);		// wait for MPU-6000 to be ready to perform read/write operations


	CS_LOW;
	//Delay(1);
	/* Wait for SPI1 Tx buffer empty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	/* Send SPI1 data */
	SPI_I2S_SendData(SPI1, PWR_MGMT_1);		//address USER_CTRL register
	/* Wait for SPI1 Tx buffer empty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	/* Send SPI1 data */
	SPI_I2S_SendData(SPI1, DEVICE_RESET);			//write USER_CTRL register
	// wait for RXNE = 1
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
	Delay(1);
	CS_HIGH;

	Delay(500);

	CS_LOW;
	//Delay(1);
	/* Wait for SPI1 Tx buffer empty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	/* Send SPI1 data */
	SPI_I2S_SendData(SPI1, PWR_MGMT_1);		//address PowerManagement1 register
	/* Wait for SPI1 Tx buffer empty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	/* Send SPI1 data */
	SPI_I2S_SendData(SPI1, 0x03);			//write PowerManagement1 register
											//set clocksource to Z-axis gyroscope reference
	// wait for RXNE = 1
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
	Delay(1);
	CS_HIGH;

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

	//We want to write to the array last element first.
	//This changes the order of high byte and low byte and allows us to access a whole word at once later on.
	bytearray += (NofBytes - 1);

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
		bytearray--;

		NofBytes--;
	}

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

	*bytearray = SPI_I2S_ReceiveData(SPI1);

	CS_HIGH;
}
