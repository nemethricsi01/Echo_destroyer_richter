/*
 * digitpoti.h
 *
 *  Created on: Feb 2, 2024
 *      Author: nemet
 */

#ifndef DIGITPOTI_H
#define DIGITPOTI_H
#include <stdint.h>
#include "main.h"


typedef struct  {
	uint8_t micVal;
	uint8_t refVal;
	uint8_t outVal;
	uint8_t bypVal;
}DigitPot;



void sendValToPoti(DigitPot *poti, I2C_HandleTypeDef *i2chandle);


#endif /* DIGITPOTI_DIGITPOTI_H_ */
