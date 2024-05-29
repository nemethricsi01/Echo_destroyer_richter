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

#include <stdbool.h>


typedef struct  {
	volatile uint8_t micVal;
	volatile uint8_t refVal;
	volatile uint8_t outVal;
	volatile uint8_t bypVal;
}DigitPot;



void sendValToPoti(DigitPot *poti, I2C_HandleTypeDef *i2chandle);
void write_poti_settings( I2C_HandleTypeDef *i2chandle,uint8_t poti,bool TermAConnected,bool TermBConnected,
		bool TermWConnected);
HAL_StatusTypeDef writePotiFromNvs( DigitPot *poti);
HAL_StatusTypeDef writePotiToNvs( DigitPot *poti);

#endif /* DIGITPOTI_DIGITPOTI_H_ */
