#ifndef __FLASH_H
#define __FLASH_H

#include "user_common.h"

#define FLASH_BASEADDR 		0x08000000

void FLASH_Erase(uint16_t page);

void Flash_write32Buff(uint16_t page, uint16_t Address_offset, uint32_t *data, uint32_t len);
void Flash_read32Buff(uint16_t page, uint16_t Address_offset, uint32_t* data, uint32_t len);

#endif /* __FLASH_H */
