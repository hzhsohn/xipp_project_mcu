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

//��С����
#define dxbPooPoo  				SENSOR4_STATE()?0:1    //ʺ
#define dxbXuXu	  				SENSOR5_STATE()?0:1    //��

//--
//�¶�
int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0,rGasTemperature=0,rGasTemp=0;
s16 rTrueWaterTemp=0,rTrueGasTemp=0;
int isWaterTooHot=0;
int isGasTooHot=0;
int isCheckWaterSensorErr=0; //ˮ�·���������
int isCheckGasSensorErr=0;//ˮ�·���������
int isCheckBedCQSensorErr=0;//��ѹ����������
int isCheckDZCQSensorErr=0;	//��ѹ����������

//��ѹ
u16_t rPressure=0,rPressureTmp=0,rPressure2=0,rPressure2Tmp=0,rPressure3=0,rPressure3Tmp=0;
u16_t rTruePressure1=0,rTruePressure2=0,rTruePressure3=0;

//ʺʺ����ķ�����
int rPoopoDD=0;
int rXuxuDD=0;
int pdxbPooPoo;
int pdxbXuXu;
//
int isTextPOPO=0;
int isTextXUXU=0;

//����
extern unsigned char cHeartJump;

//
void delay_s(int n)
{
		int i=0;
		for(i=0;i<n*10;i++)
		{ STM32_Delay_ms(100); }
}

//�ر��������
void allClose()
{
		//
	 _unit1(0); 								
	 _unit2(0); 					
	 _unit3(0); 					
	 _unit4(0); 		 					
	 _unit5(0); 						
	 _unit6(0); 							
	 _unit7(0); 							
	 _unit8(0); 				 	
	 _unit9(0); 								
	 _unit10(0); 				 		
	 _unit11(0);					
	 _unit12(0); 	 						
	 _unit13(0);
	 _unit14(0); 
	 _unit15(0); 	
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
	STM32_Delay_init();
	STM32F1_UART1_Init(115200);
	STM32F1_UART2_Init(19200);
	STM32F1_UART3_Init(9600);
	
	DS18B20_Init();
	DS18B20_Init1();
	Adc_Init();
	Adc2_Init();
	Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	InputDriveInit();
	OutputDriveInit();
	//zhSCM_GPIOConfig();
 	
	//-----------------------------------------
	//��ȡFALSH����
	setFlashData();
  //-----------------------------------------

	//���Ź�
	//watchdog_init();
	
	while(1)
	{
				//���Ź�
				//watchdog_action();
				//
				pdxbPooPoo=dxbPooPoo;
				pdxbXuXu=dxbXuXu;
				//		
				//------------------------------------------------------------------
				//���������������		
				//if(rTrueWaterTemp>=g_tmeSetting.waterTemperature*10) //�������ˮ�²���������
				{
							if(dxbXuXu)
							{
								rXuxuDD++;
								if(rXuxuDD>2000)
								{
										rXuxuDD=0;
								}
							}
							else
							{
									rXuxuDD=0;
							}
				}
				//------------------------------------------------------------------
				//�����û��ʺ������
				//if(rTrueWaterTemp>=g_tmeSetting.waterTemperature*10)  //�������ˮ�²���������
				{
							if(dxbPooPoo)
							{
								rPoopoDD++;
								if(rPoopoDD>2000)
								{
										rPoopoDD=0;
								}
							}
							else
							{
								rPoopoDD=0;
							}
				}

				//------------------------------------------------------------------
				//ˮ�¼���
				rWaterTemp=DS18B20_Get_Temp();
				if(rWaterTemp<2000 && rWaterTemp> -200) //����λ
				{
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
							//��������ë����.
						}
				}

				//-------------------------------------------------------------------
				//��������,ʵʱ��������
				rGasTemp=DS18B20_Get_Temp1(); 
				if(rGasTemp<2000 && rGasTemp> -200) //����λ
				{
					ntmp=rGasTemp-rGasTemperature;
					if(ntmp<20 && ntmp>-20) //����ͻ�����
					{
							isGasTooHot=0;							
							if(rGasTemp > 60*10) //�������������˰�,̫���˾��Ǽ�������������.
							{
								//����̫����.�������ڸ�����λ����,֪ͨ��ʿС����,����������
								isGasTooHot=1;
							}
							rTrueGasTemp=rGasTemp;
							isCheckGasSensorErr=0;
					}
					rGasTemperature=rGasTemp;
				}
				else
				{
					isCheckGasSensorErr++;						
					if(isCheckGasSensorErr>10) //����������ë���ص����ȼ̵���
					{
							//��������ë����.�ص��̵���
							_unit12(0); //�����ȵ�Ԫ
					}
				}
		}		
}
