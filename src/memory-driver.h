#ifndef MEMORY_DRIVER_H
#define MEMORY_DRIVER_H

#include <asf.h>
#include "ble_utils.h"
#include "conf_at25dfx.h"

void flash_memory_init(void);

void flash_memory_read (uint16_t address, uint16_t* target_buffer, uint16_t size);

void flash_memory_write (uint16_t address, uint16_t* target_buffer, uint16_t size);

#endif