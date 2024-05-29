/*
 * i2c_slave.c
 *
 *  Created on: Jan 31, 2024
 *      Author: nemet
 */


#include "main.h"
#include "digitpoti.h"
#include "nvs.h"

extern I2C_HandleTypeDef hi2c3;
extern I2C_HandleTypeDef hi2c1;

#define RxSIZE  10 //1 for mic, 1 for ref, 1 for output, 1 bypass, 6 reserved
uint8_t RxData[RxSIZE];
#define DIGIPOT_ADD 0x58
#define POTI_SAVETIME 50


extern volatile uint16_t potiSaveTimer;


extern DigitPot digitpoti;
uint8_t TxData[16] = {	0x00,0x11,0x22,0x33,
						0x44,0x55,0x66,0x77,
						0x88,0x99,0xaa,0xbb,
						0,0,
						0,0
						};
extern volatile int16_t MicMaxVal;
extern volatile int16_t RefMaxVal;
extern volatile int16_t OutMaxVal;

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
	else if( TransferDirection == I2C_DIRECTION_RECEIVE )
	{
		TxData[0] = MicMaxVal>>8;
		TxData[1] = MicMaxVal & 0xff;
		TxData[2] = RefMaxVal>>8;
		TxData[3] = RefMaxVal & 0xff;
		TxData[4] = OutMaxVal>>8;
		TxData[5] = OutMaxVal & 0xff;
		TxData[15] = digitpoti.bypVal;
		TxData[14] = digitpoti.outVal;
		TxData[13] = digitpoti.refVal;
		TxData[12] = digitpoti.micVal;

		HAL_I2C_Slave_Seq_Transmit_IT(hi2c, TxData, 16, I2C_NEXT_FRAME);
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
	potiSaveTimer = POTI_SAVETIME;

	sendValToPoti(&digitpoti, &hi2c1);
	if(digitpoti.bypVal == 0)
	{
		write_poti_settings(&hi2c1, 3, false, true, true);
	}
	else
	{
		write_poti_settings(&hi2c1, 3, true, true, true);
	}
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
	uint32_t errorcode = HAL_I2C_GetError(hi2c);
	/* BERR Error commonly occurs during the Direction switch
	 * Here we the software reset bit is set by the HAL error handler
	 * Before resetting this bit, we make sure the I2C lines are released and the bus is free
	 * I am simply reinitializing the I2C to do so
	 */
	if (errorcode == 1)  // BERR Error
	{
		HAL_I2C_DeInit(hi2c);
		HAL_I2C_Init(hi2c);
	}
	HAL_I2C_EnableListen_IT(hi2c);
}
