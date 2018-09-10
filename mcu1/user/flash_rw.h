#ifndef __flash_rw_H
#define __flash_rw_H

#include "stm32f10x_flash.h"
#include "STM32_Delay.h"


#define STARTADDRFLAG		 	0x08020000
#define STARTADDR 				0x0801F000

void FLASH_WriteByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num);
void FLASH_ReadByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num);

#endif
