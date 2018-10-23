#ifndef __STM32_Delay_H__
#define __STM32_Delay_H__

#include "system_init.h"
void STM32_Delay_init(void);
void STM32_Delay_us(u32_t nus);
void STM32_Delay_ms(u16_t nms);
#endif

