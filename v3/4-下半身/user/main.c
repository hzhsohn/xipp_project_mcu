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

/**************/
//�������߼��ض���
#define cgqWaterHeight  					SENSOR1_STATE()?1:0 //
#define cgqWaterLow  				SENSOR2_STATE()?0:1 //��ˮ��

//--
//ˮ�¶�
int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0;
s16 rTrueWaterTemp=0;
int isWaterTooHot=0;
int isCheckWaterSensorErr=0; //ˮ�·���������

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
	STM32F1_UART1_Init(115200);
	STM32F1_UART2_Init(19200);
	STM32F1_UART3_Init(9600);
	
	DS18B20_Init();
	//DS18B20_Init1();
	//Adc_Init();
	//Adc2_Init();
	Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	InputDriveInit();
	OutputDriveInit();
	zhSCM_GPIOConfig();
	
	//-----------------------------------------
	//��ȡFALSH����
	setFlashData();
  //-----------------------------------------

	//
	 _unit1(1); 								
	 _unit2(1); 					
	 _unit3(1); 					
	 _unit4(1); 		 					
	 _unit5(1); 						
	 _unit6(1); 							
	 _unit7(1); 							
	 _unit8(1); 				 	
	 _unit9(1); 								
	 _unit10(1); 				 		
	 _unit11(1);					
	 _unit12(1); 	 						
	 _unit13(1);
	 _unit14(1); 
	 _unit15(1); 
	
	//���Ź�
	//watchdog_init();
	
	while(1)
	{
				//���Ź�
				//watchdog_action();
				//
				//---------------------
				//����1		������
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
							
					}
					 break;
				}
				//����2		��ϴ��
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
							
					}
						break;
				}
				//����3		��ɼ�
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
							
					}
						break;
				}
				//����4		������
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
						break;
				}
				
				//����5		��Ħ��
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
						break;
				}
				//����6		��ů��
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
						break;
				}
				
				//����7		������
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
					}
						break;
				}
				//����8		��������
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
					}
						break;
				}

				//------------------------------------------------------------------
				//ˮ�¼���
				rWaterTemp=DS18B20_Get_Temp();
				if(rWaterTemp<2000 && rWaterTemp> -200) //����λ
				{
					int ntmp=0;
					ntmp=rWaterTemp-rWaterTemperature;
					if(ntmp<20 && ntmp>-20)	//����ͻ�����
					{
							isWaterTooHot=0;							
							if(rWaterTemp > 60*10) //�������������˰�,̫���˾��Ǽ�������������.
							{
									//ˮ̫����.�������ڸ�����λ����,֪ͨ��ʿС����,����������
									isWaterTooHot=1;
							}
							rTrueWaterTemp=rWaterTemp;
							isCheckWaterSensorErr=0;
					}
					rWaterTemperature=rWaterTemp;
				}
				else
				{
						isCheckWaterSensorErr++;						
						if(isCheckWaterSensorErr>10) //��������ë��̫��ص����ȼ̵���
						{
							//��������ë����.�ص��̵���
				
						}
				}
	}
}
