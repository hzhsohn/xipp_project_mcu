#ifndef __STM32F1_UART1_DIVER_H_
#define __STM32F1_UART1_DIVER_H_
#include "system_init.h"

void STM32F1_UART1SendData(u8_t nData);
void STM32F1_UART1SendDataS(u8_t* nData,u8_t nNum);
void STM32F1_UART1_Init(u32_t lBaudRate);
#endif
