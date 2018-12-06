#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "system_init.h"
#include "Stm32f1_uart1.h"
#include "Stm32f1_uart2.h"
#include "Stm32f1_uart3.h"
#include "InputDrive.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1.h"
#include "Stm32f1_ADC2.h"
#include "ds18b20_1.h"
#include "watchdog.h"
#include "flash_rw.h"
#include "Stm32F1_Timer2.h"
#include "Stm32F1_Timer3.h"
#include "key.h"
#include "OutputDrive.h"
#include "global.h"

//
static void delay_s(int n)
{
		int i=0;
		for(i=0;i<n*10;i++)
		{ STM32_Delay_ms(100); }
}

#define _unit1(x) 							RELAY1_STATE(x)			//��������  ���η���
#define _unit2(x) 							RELAY2_STATE(x)			//��������  ���η���
#define _unit3(x) 							RELAY3_STATE(x)			//��й����  ���η���
#define _unit4(x) 		 					RELAY4_STATE(x)			//��й����  ���η���
#define _unit5(x) 							RELAY5_STATE(x)			//��ˮ��1  ���շ�����
#define _unit6(x) 							RELAY6_STATE(x)			//��ˮ��2  ���շ��ų嶷
#define _unit7(x) 							RELAY7_STATE(x)			//��ˮ��3  ���շ��ų�PP
#define _unit8(x) 				 			RELAY8_STATE(x) 		//ɱ����
#define _unit9(x) 							RELAY9_STATE(x)			//������ˮ
#define _unit10(x) 				 			RELAY10_STATE(x)		//������
#define _unit11(x)							RELAY11_STATE(x) 		//����ˮ��
#define _unit12(x) 	 						RELAY12_STATE(x)		//��������
#define _unit13(x) 							RELAY13_STATE(x)		//ˮ������  16A
#define _unit14(x) 	 						RELAY14_STATE(x)		//Ԥ��  220V
#define _unit15(x) 							RELAY15_STATE(x)		//������  220V



#endif
