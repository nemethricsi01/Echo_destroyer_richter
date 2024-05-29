/*
 * debug_led.h
 *
 *  Created on: Feb 13, 2024
 *      Author: nemet
 */

#ifndef DEBUG_LED_DEBUG_LED_H_
#define DEBUG_LED_DEBUG_LED_H_

#include "stm32f4xx.h"

typedef enum {
    PROG_INITIALIZATION,
    PROG_NORMAL_OPERATION,
    PROG_ERROR,
    PROG_DEBUG
} ProgramState;
extern volatile ProgramState current_state;



#endif /* DEBUG_LED_DEBUG_LED_H_ */
