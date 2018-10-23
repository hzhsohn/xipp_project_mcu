#ifndef __STM32F1_UART2_DIVER_H_
#define __STM32F1_UART2_DIVER_H_
#include "system_init.h"
void STM32F1_UART2SendData(u8_t nData);
void STM32F1_UART2SendDataS(u8_t* nData,u8_t nNum);
void STM32F1_UART2_Init(u32_t lBaudRate);
#endif
