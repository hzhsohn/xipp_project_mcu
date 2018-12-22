#ifndef __STM32F1_UART1_DIVER_H_
#define __STM32F1_UART1_DIVER_H_
#include "system_init.h"


/*
//-----------当前清洗小场景
	ezhCleanSenceNone没执行,
	ezhCleanSence1自动化小便																					
	ezhCleanSence2自动化大便 
	ezhCleanSence3护卫
	ezhCleanSence4冲洗
	ezhCleanSence5烘干
	ezhCleanSence6除菌
	ezhCleanSence7按摩
	ezhCleanSence8保暖
*/
typedef enum _EzhCleanSence{
	ezhCleanSenceNone=0x00,
	ezhCleanSence1=0x10,
	ezhCleanSence2=0x20,
	ezhCleanSence3=0x30,
	ezhCleanSence4=0x40,
	ezhCleanSence5=0x50,
	ezhCleanSence6=0x60,
	ezhCleanSence7=0x70,
	ezhCleanSence8=0x80,
	ezhCleanSenceA=0xA0,
	ezhCleanSenceB=0xB0,
	ezhCleanSenceC=0xC0,
}EzhCleanSence;



void STM32F1_UART1SendData(u8_t nData);
void STM32F1_UART1SendDataS(u8_t* nData,u8_t nNum);
void STM32F1_UART1_Init(u32_t lBaudRate);
#endif
