#ifndef __STM32F1_UART3_DIVER_H_
#define __STM32F1_UART3_DIVER_H_
#include "system_init.h"
void STM32F1_UART3SendData(u8_t nData);
void STM32F1_UART3SendDataS(u8_t* nData,u8_t nNum);
void STM32F1_UART3_Init(u32_t lBaudRate);
#endif
