/*
 * i2c_slave.c
 *
 *  Created on: Jan 31, 2024
 *      Author: nemet
 */


#include "main.h"
#include "digitpoti.h"

extern I2C_HandleTypeDef hi2c3;
extern I2C_HandleTypeDef hi2c1;

#define RxSIZE  10 //1 for mic, 1 for ref, 1 for output, 1 bypass, 6 reserved
uint8_t RxData[RxSIZE];
#define DIGIPOT_ADD 0x58




DigitPot digitpoti;


int count = 0;

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	HAL_I2C_EnableListen_IT(hi2c);
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	if (TransferDirection == I2C_DIRECTION_TRANSMIT)  // if the master wants to transmit the data
	{
		// receive using sequential function.
		// The I2C_FIRST_AND_LAST_FRAME implies that the slave will send a NACK after receiving "entered" num of bytes
		HAL_I2C_Slave_Sequential_Receive_IT(hi2c, RxData, RxSIZE, I2C_FIRST_AND_LAST_FRAME);
		for(int i = 0;i<10;i++);
	}
	else  // if the master requests the data from the slave
	{
		Error_Handler();  // call error handler
	}
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	digitpoti.micVal = RxData[0];
	digitpoti.refVal = RxData[1];
	digitpoti.outVal = RxData[2];
	digitpoti.bypVal = RxData[3];

	sendValToPoti(&digitpoti, &hi2c1);
	count++;
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
	HAL_I2C_EnableListen_IT(hi2c);
}
