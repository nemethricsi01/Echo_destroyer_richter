/*
 * digitpoti.c
 *
 *  Created on: Feb 2, 2024
 *      Author: nemet
 */
#include "digitpoti.h"

uint16_t digipotiAttValues[39] =
{
		256,//0
		228,//-1
		203,//-2
		181,
		162,
		144,
		128,
		114,
		102,
		91,
		81,
		72,
		64,
		57,
		51,
		46,
		41,
		36,
		32,
		29,
		26,
		23,
		20,
		18,
		16,
		14,
		13,
		11,
		10,
		9,
		8,
		7,
		6,
		5,
		4,
		3,//-39
		2,//-42
		1,//-48
		0//- inf
};
static void writePoti0(uint8_t *outbuff, uint16_t val)
{
	outbuff[0] |=  (val>>8)&0x01;
	outbuff[1] = val&0xff;
};
static void writePoti1(uint8_t *outbuff, uint16_t val)
{
	outbuff[2] |=  (val>>8)&0x01;
	outbuff[3] = val&0xff;
};
static void writePoti2(uint8_t *outbuff, uint16_t val)
{
	outbuff[4] |=  (val>>8)&0x01;
	outbuff[5] = val&0xff;
};
static void writePoti3(uint8_t *outbuff, uint16_t val)
{
	outbuff[6] |=  (val>>8)&0x01;
	outbuff[7] = val&0xff;
};

void sendValToPoti ( DigitPot *poti, I2C_HandleTypeDef *i2chandle)
{
	uint8_t data[8] = {0x0,0x0,  0x10,0x0,  0x60,0x0,  0x70,0x0};

	writePoti0(data, digipotiAttValues[ ( uint8_t )( ( float ) (poti->refVal) * ( 38.0/100.0 ) ) ]);
	writePoti1(data, digipotiAttValues[ ( uint8_t )( ( float ) (poti->micVal) * ( 38.0/100.0 ) ) ]);
	writePoti2(data, digipotiAttValues[ ( uint8_t )( ( float ) (poti->outVal) * ( 38.0/100.0 ) ) ]);
	writePoti3(data, digipotiAttValues[ ( uint8_t )( ( float ) (poti->bypVal) * ( 38.0/100.0 ) ) ]);


	HAL_I2C_Master_Transmit(i2chandle, 0x58, data, 16,200);

}
