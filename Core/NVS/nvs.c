/*
 * nvs.c
 *
 *  Created on: Feb 6, 2024
 *      Author: nemet
 */

#include "nvs.h"

#define FLASH_USER_START_ADDR    0x08060000UL   // Adjust based on your flash sector

HAL_StatusTypeDef write_to_flash(uint32_t* data, uint32_t size)
{
	volatile HAL_StatusTypeDef status;
    volatile FLASH_EraseInitTypeDef erase_init;
    volatile uint32_t page_error;

    // Initialize FLASH Erase structure
    erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;
    erase_init.Sector = FLASH_SECTOR_7;  // Adjust based on your flash sector
    erase_init.NbSectors = 1;
    erase_init.VoltageRange = FLASH_VOLTAGE_RANGE_3;  // Adjust based on your voltage range
    HAL_FLASH_Unlock();
    // Erase the flash sector
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_PGPERR);
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_PGSERR);
    status = HAL_FLASHEx_Erase(&erase_init, &page_error);
    volatile uint32_t error;
    error = HAL_FLASH_GetError();

    // Write data to flash

    uint32_t dummy[size] __attribute__((aligned(4)));
    for (int i = 0; i < size; i++) {
    	dummy[i] = data[i];
        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_USER_START_ADDR + i * sizeof(uint32_t), dummy[i]);
        if (status != HAL_OK) {
            // Error handling
        	return HAL_ERROR;
        }
    }
    HAL_FLASH_Lock();
}


// Function to read data from flash memory
HAL_StatusTypeDef read_from_flash(uint32_t* data, uint32_t size) {
    for (int i = 0; i < size; i++) {
        data[i] = *(uint32_t*)(FLASH_USER_START_ADDR + i * sizeof(uint32_t));
    }
}
