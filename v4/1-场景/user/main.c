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
#include "logic.h"

//当前工作场景
extern int g_cCleanCurrentSence;
//
void delay_s(int n)
{
		int i=0;
		for(i=0;i<n*10;i++)
		{ STM32_Delay_ms(100); }
}

////////////////////////////////////////////////////////////////
void setFlashData()
{
	char binFlag[4]={0};
	FLASH_ReadByte(STARTADDRFLAG ,(uint8_t*)binFlag,4);
	
	if(!(binFlag[0]=='a' && binFlag[1]=='b' && binFlag[2]=='c' && binFlag[3]=='d'))
	{
			binFlag[0]='a';
			binFlag[1]='b';
			binFlag[2]='c';
			binFlag[3]='d';

			FLASH_WriteByte(STARTADDRFLAG,(uint8_t*)binFlag,4);
	}
}
int main(void)
{
	EzhKeyEvent ev;
  EzhKeyState btn1;
	EzhKeyState btn2;
	EzhKeyState btn3;
	EzhKeyState btn4;
	EzhKeyState btn5;
	EzhKeyState btn6;
	EzhKeyState btn7;
	EzhKeyState btn8;
  zhSCM_initKeyState(&btn1);
	zhSCM_initKeyState(&btn2);
	zhSCM_initKeyState(&btn3);
	zhSCM_initKeyState(&btn4);
	zhSCM_initKeyState(&btn5);
	zhSCM_initKeyState(&btn6);
	zhSCM_initKeyState(&btn7);
	zhSCM_initKeyState(&btn8);
		
	STM32_Delay_init();
	STM32F1_UART1_Init(19200);
	//STM32F1_UART2_Init(19200);
	STM32F1_UART3_Init(19200);

	Stm32F1_Timer2Init(); 
	Stm32F1_Timer3Init();
	InputDriveInit();
	OutputDriveInit();
	zhSCM_GPIOConfig();
	
	//-----------------------------------------
	//获取FALSH数据
	setFlashData();
  //-----------------------------------------
  
  //STM32F1_UART3SendDataS("12345",5);
  uart3Send(100,0,0,NULL,0);
  
  

	//看门狗
	//watchdog_init();
	
	while(1)
	{
				//看门狗
				//watchdog_action();
				//
				//---------------------
				//按键1		大便键
				ev=zhSCM_keyState(&btn1,TOUCHKEY_1_GPIO,TOUCHKEY_1_PIN);
				switch(ev)
				{
					case ZH_KEY_EVENT_NONE:
						break;
					case ZH_KEY_EVENT_DOWN:
						break;
					case ZH_KEY_EVENT_PRESS:
						break;
					case ZH_KEY_EVENT_UP:
					{
						senceBegin(ezhCleanSence10);
					}
					 break;
				}
				//按键2		小便键
				ev=zhSCM_keyState(&btn2,TOUCHKEY_2_GPIO,TOUCHKEY_2_PIN);
				switch(ev)
				{
					case ZH_KEY_EVENT_NONE:
						break;
					case ZH_KEY_EVENT_DOWN:
						break;
					case ZH_KEY_EVENT_PRESS:
						break;
					case ZH_KEY_EVENT_UP:
					{
						senceBegin(ezhCleanSence9);
					}
						break;
				}
				//按键3		烘干键
				ev=zhSCM_keyState(&btn3,TOUCHKEY_3_GPIO,TOUCHKEY_3_PIN);
				switch(ev)
				{
					case ZH_KEY_EVENT_NONE:
						break;
					case ZH_KEY_EVENT_DOWN:
						break;
					case ZH_KEY_EVENT_PRESS:
						break;
					case ZH_KEY_EVENT_UP:
					{
						senceBegin(ezhCleanSence5);
					}
						break;
				}
				//按键4		除菌键
				ev=zhSCM_keyState(&btn4,TOUCHKEY_4_GPIO,TOUCHKEY_4_PIN);
				switch(ev)
				{
					case ZH_KEY_EVENT_NONE:
						break;
					case ZH_KEY_EVENT_DOWN:
						break;
					case ZH_KEY_EVENT_PRESS:
						break;
					case ZH_KEY_EVENT_UP:
					{
						senceBegin(ezhCleanSence6);
					}
						break;
				}
				
				//按键5		按摩键
				ev=zhSCM_keyState(&btn5,TOUCHKEY_5_GPIO,TOUCHKEY_5_PIN);
				switch(ev)
				{
					case ZH_KEY_EVENT_NONE:
						break;
					case ZH_KEY_EVENT_DOWN:
						break;
					case ZH_KEY_EVENT_PRESS:
						break;
					case ZH_KEY_EVENT_UP:
					{
						senceBegin(ezhCleanSence7);
					}
						break;
				}
				//按键6		保暖键
				ev=zhSCM_keyState(&btn6,TOUCHKEY_6_GPIO,TOUCHKEY_6_PIN);
				switch(ev)
				{
					case ZH_KEY_EVENT_NONE:
						break;
					case ZH_KEY_EVENT_DOWN:
						break;
					case ZH_KEY_EVENT_PRESS:
						break;
					case ZH_KEY_EVENT_UP:
					{
						//保暖开与关
						uart3Send(4,1,0,NULL,0);
					}
						break;
				}

				//按键7		翻身
				ev=zhSCM_keyState(&btn7,TOUCHKEY_7_GPIO,TOUCHKEY_7_PIN);
				switch(ev)
				{
					case ZH_KEY_EVENT_NONE:
						break;
					case ZH_KEY_EVENT_DOWN:
						break;
					case ZH_KEY_EVENT_PRESS:
						break;
					case ZH_KEY_EVENT_UP:
					{
						uart3Send(5,3,1,NULL,0);
					}
						break;
				}
				//按键8		待机开关
				ev=zhSCM_keyState(&btn8,TOUCHKEY_8_GPIO,TOUCHKEY_8_PIN);
				switch(ev)
				{
					case ZH_KEY_EVENT_NONE:
						break;
					case ZH_KEY_EVENT_DOWN:
						break;
					case ZH_KEY_EVENT_PRESS:
						break;
					case ZH_KEY_EVENT_UP:
					{
						senceBegin(ezhCleanSence8);
					}
						break;
				}

	}
}
