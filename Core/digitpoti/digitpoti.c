/*
 * digitpoti.c
 *
 *  Created on: Feb 2, 2024
 *      Author: nemet
 */
#include "digitpoti.h"
#include "nvs.h"

#include <string.h>

uint8_t data[8] = {0x0,0x0,  0x10,0x0,  0x60,0x0,  0x70,0x0};
uint32_t potivals_toSave[4];
//uint16_t digipotiAttValues[39] =
//{
//		256,//0
//		228,//-1
//		203,//-2
//		181,
//		162,
//		144,
//		128,
//		114,
//		102,
//		91,
//		81,
//		72,
//		64,
//		57,
//		51,
//		46,
//		41,
//		36,
//		32,
//		29,
//		26,
//		23,
//		20,
//		18,
//		16,
//		14,
//		13,
//		11,
//		10,
//		9,
//		8,
//		7,
//		6,
//		5,
//		4,
//		3,//-39
//		2,//-42
//		1,//-48
//		0//- inf
//};
uint16_t digipotiAttValues[41] =
{
    0,1,2,3,4,5,
	6,7,8,9,10,11,
	13,14,16,18,20,23,
	26,29,32,36,41,46,
	51,57,64,72,81,91,
	102,114,128,144,162,181,
    203,228,256
};
static void writePoti0(uint8_t *outbuff, uint16_t val)
{
	outbuff[0] |=  (val>>8)&0x01;
	outbuff[1] = val&0xff;
};
static void writePoti1(uint8_t *outbuff, uint16_t val)
{
	outbuff[2] = 0x10;
	outbuff[2] |=  (val>>8)&0x01;
	outbuff[3] = val&0xff;
};
static void writePoti2(uint8_t *outbuff, uint16_t val)
{
	outbuff[4] = 0x60;
	outbuff[4] |=  (val>>8)&0x01;
	outbuff[5] = val&0xff;
};
static void writePoti3(uint8_t *outbuff, uint16_t val)
{
	if(val == 0)
	{

	}
	outbuff[6] = 0x70;
	outbuff[6] |=  (val>>8)&0x01;
	outbuff[7] = val&0xff;
};
void write_poti_settings( I2C_HandleTypeDef *i2chandle,uint8_t poti,bool TermAConnected,bool TermBConnected,
								bool TermWConnected)
{
	uint8_t data[2];//reg address,ctrl byte
	data[1] = 0xff;//default state
	switch (poti) {
		case 0:
			data[0] = 0x41;//TCON0
			if(TermAConnected)
				{
					data[1] &= ~(1<<2);
				}
			if(TermBConnected)
				{
					data[1] &= ~(1<<0);
				}
			if(TermWConnected)
				{
					data[1] &= ~(1<<1);
				}
			break;
		case 1:
			data[0] = 0x41;//TCON0
			if(TermAConnected)
				{
					data[1] &= ~(1<<6);
				}
			if(TermBConnected)
				{
					data[1] &= ~(1<<4);
				}
			if(TermWConnected)
				{
					data[1] &= ~(1<<5);
				}
			break;
		case 2:
			data[0] = 0xa1;//TCON1
			if(TermAConnected)
				{
					data[1] &= ~(1<<2);
				}
			if(TermBConnected)
				{
					data[1] &= ~(1<<0);
				}
			if(TermWConnected)
				{
					data[1] &= ~(1<<1);
				}
			break;
		case 3:
			data[0] = 0xa1;//TCON1
			if(!TermAConnected)
				{
					data[1] &= ~(1<<6);
				}
			if(!TermBConnected)
				{
					data[1] &= ~(1<<4);
				}
			if(!TermWConnected)
				{
					data[1] &= ~(1<<5);
				}
			break;
		default:
			break;
	}
	HAL_I2C_Master_Transmit(i2chandle, 0x58, data, 2,200);
}
static HAL_StatusTypeDef checkPotirange(void* vals)
{
	uint32_t* array = (uint32_t*)vals; // Cast void pointer to uint32_t pointer
	for(uint8_t i = 0;i<4;i++)
	{
		if(array[i] > 100)
		{
			return HAL_ERROR;
		}
	}
	return HAL_OK;
}
//this loads the poti struct with the appropiate values from flash,does not write it to the pots themselves
HAL_StatusTypeDef writePotiFromNvs( DigitPot *poti)
{
	static uint32_t potivals[4];
	HAL_StatusTypeDef err = HAL_OK;

	read_from_flash(potivals, 4);
	err = checkPotirange((uint32_t*)potivals);
	if(err == HAL_OK)
		{
			poti->micVal = (uint8_t)potivals[0];
			poti->refVal = (uint8_t)potivals[1];
			poti->outVal = (uint8_t)potivals[2];
			poti->bypVal = (uint8_t)potivals[3];
		}
	else
	{
		poti->micVal = 0;
		poti->refVal = 0;
		poti->outVal = 0;
		poti->bypVal = 100;
	}
	return err;
}
//saves the poti values to the nvs
HAL_StatusTypeDef writePotiToNvs( DigitPot *poti)
{
	HAL_StatusTypeDef err = HAL_OK;
	potivals_toSave[0] = poti->micVal;
	potivals_toSave[1] = poti->refVal;
	potivals_toSave[2] = poti->outVal;
	potivals_toSave[3] = poti->bypVal;
	write_to_flash(potivals_toSave, 4);
	return err;
}

void sendValToPoti ( DigitPot *poti, I2C_HandleTypeDef *i2chandle)
{
	memset(data,0,sizeof(data));
	writePoti0(data, digipotiAttValues[ ( uint8_t )( ( float ) (poti->refVal) * ( 39.0/101.0 ) ) ]);
	writePoti1(data, digipotiAttValues[ ( uint8_t )( ( float ) (poti->micVal) * ( 39.0/101.0 ) ) ]);
	writePoti2(data, digipotiAttValues[ ( uint8_t )( ( float ) (poti->outVal) * ( 39.0/101.0 ) ) ]);
	writePoti3(data, digipotiAttValues[ ( uint8_t )( ( float ) (poti->bypVal) * ( 39.0/101.0 ) ) ]);


	HAL_I2C_Master_Transmit(i2chandle, 0x58, data, 8,200);

}
