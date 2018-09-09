#ifndef __STM32F1_UART1_DIVER_H_
#define __STM32F1_UART1_DIVER_H_
#include "system_init.h"


/*
//-----------��ǰ��ϴС����
	ezhCleanSenceNoneûִ��,
	ezhCleanSence1�Զ���С��																					
	ezhCleanSence2�Զ������ 
	ezhCleanSence3����
	ezhCleanSence4��ϴ
	ezhCleanSence5���
	ezhCleanSence6����
	ezhCleanSence7��Ħ
	ezhCleanSence8��ů
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
