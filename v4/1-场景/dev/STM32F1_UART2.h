#ifndef __STM32F1_UART2_DIVER_H_
#define __STM32F1_UART2_DIVER_H_

#include "system_init.h"

typedef enum _EzhUart2Sence{
		//1//继电器抽吸启用
		//2//继电器烘干启用
		//3//继电器除菌启用
		//4//继电器大便启用
		//5//继电器大便冲洗启用
		//6//继电器小便启用
		//7//继电器小便冲洗启用

		ezhUart2Sence1=1,
		ezhUart2Sence2,
		ezhUart2Sence3,
		ezhUart2Sence4,
		ezhUart2Sence5,
		ezhUart2Sence6,
		ezhUart2Sence7
	
}EzhUart2Sence;


void STM32F1_UART2SendData(u8_t nData);
void STM32F1_UART2SendDataS(u8_t* nData,u8_t nNum);
void STM32F1_UART2_Init(u32_t lBaudRate);

void uart2EventBtn(int i);
void uart2EventUnitSence(EzhUart2Sence i,int isEnable);

#endif
