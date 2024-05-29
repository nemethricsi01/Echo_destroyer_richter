/*
 * debug_led.c
 *
 *  Created on: Feb 13, 2024
 *      Author: nemet
 */
#include "debug_led.h"

#include "stm32f4xx.h"
#include "main.h"
#include "digitpoti.h"


volatile ProgramState current_state = PROG_INITIALIZATION;
volatile uint16_t potiSaveTimer = 0;
extern uint8_t savepotiflag;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {

	if(potiSaveTimer > 0)
	{
		potiSaveTimer--;
		if(potiSaveTimer == 0)
		{
			savepotiflag = 1;
		}
	}
	 static int counter = 0;
	        counter++;
	        switch (current_state) {
	                    case PROG_INITIALIZATION:
	                        // Blink LED slowly
	                        if (counter % 4 == 0) {
	                            HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_SET); // LED on
	                        } else {
	                            HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_RESET); // LED off
	                        }
	                        break;
	                    case PROG_NORMAL_OPERATION:
	                        // Blink LED quickly
	                        if (counter % 2 == 0) {
	                            HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_SET); // LED on
	                        } else  {
	                            HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_RESET); // LED off
	                        }
	                        break;
	                    case PROG_ERROR:
	                        // Blink LED twice quickly, then pause
	                        if ( (counter >= 1 && counter <= 3) || (counter >= 6 && counter <= 8)) {
	                            HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_SET); // LED on
	                        } else {
	                            HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_RESET); // LED off
	                        }
	                        break;
	                    case PROG_DEBUG:
	                        // Blink LED three times quickly, then pause
	                        if ( ((counter == 3)||(counter == 4))||((counter == 7)||(counter == 8))||((counter == 11)||(counter == 12)) ) {
	                            HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_SET); // LED on
	                        } else {
	                            HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_RESET); // LED off
	                        }
	                        break;
	                }

        if (counter >= 20) {
            counter = 0;
        }
}

