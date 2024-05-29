/*
 * nvs.h
 *
 *  Created on: Feb 6, 2024
 *      Author: nemet
 */

#ifndef NVS_NVS_H_
#define NVS_NVS_H_
#include "main.h"



HAL_StatusTypeDef write_to_flash(uint32_t* data, uint32_t size);
HAL_StatusTypeDef read_from_flash(uint32_t* data, uint32_t size);


#endif /* NVS_NVS_H_ */
