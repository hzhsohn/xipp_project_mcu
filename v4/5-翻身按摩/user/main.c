#include "system_init.h"
#include "Stm32f1_uart1.h"
#include "Stm32f1_uart2.h"
#include "Stm32f1_uart3.h"
#include "InputDrive.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1.h"
#include "ds18b20_1.h"
#include "watchdog.h"
#include "flash_rw.h"
#include "Stm32F1_Timer2.h"
#include "Stm32F1_Timer3.h"
#include "key.h"
#include "OutputDrive.h"
#include "STM32F1_ADC0.h"

//提交的数据
TagTimeRun g_run;

//气压
int ntmp=0;
int g_qiya=0;
typedef u16 AVERAGE(u8 times);
u16_t rPressure[14]={0},rPressureTmp[14]={0};
u16_t rTruePressure1[14]={0};
int isCheckDZCQSensorErr[14]={0};

AVERAGE *g_average[14]={Get_Adc1_Average,Get_Adc2_Average,Get_Adc3_Average,Get_Adc4_Average,Get_Adc5_Average,
						Get_Adc6_Average,Get_Adc7_Average,Get_Adc8_Average,Get_Adc9_Average,Get_Adc10_Average,
						Get_Adc11_Average,Get_Adc12_Average,Get_Adc13_Average,Get_Adc14_Average};
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
	STM32_Delay_init();
	STM32F1_UART3_Init(19200);
	
	DS18B20_Init();
	Adc1_Init();
	Adc2_Init();
	Adc3_Init();
	Adc4_Init();
	Adc5_Init();
	Adc6_Init();
	Adc7_Init();
	Adc8_Init();
	Adc9_Init();
	Adc10_Init();
	Adc11_Init();
	Adc12_Init();
	Adc13_Init();
	Adc14_Init();
	
	//Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	//InputDriveInit();
	OutputDriveInit();
	//zhSCM_GPIOConfig();
	
	//-------继电器测试------------------------
	//RelayTest();
	//OutputDriveInit();
	
	//-----------------------------------------
	//获取FALSH数据
	setFlashData();
  //-----------------------------------------
	//看门狗 
	//watchdog_init();
	
	while(1)
	{
				//------------------------------------------------------------------
				//气压1
				for(g_qiya=0;g_qiya<14;g_qiya++)
				{
					rPressureTmp[g_qiya] = g_average[g_qiya](10);
					ntmp=rPressureTmp[g_qiya]-rPressure[g_qiya];
					if(ntmp<60 && ntmp>-60) //限制突变幅度
					{
						g_run.guan_qiya_percent[g_qiya]=(float)rPressureTmp[g_qiya]/4096.0f*100;
						rTruePressure1[g_qiya]=rPressureTmp[g_qiya];
						isCheckDZCQSensorErr[g_qiya]=0;
					}
					else
					{
						isCheckDZCQSensorErr[g_qiya]++;						
						if(isCheckDZCQSensorErr[g_qiya]>10) //传感数据有毛病关掉继电器
						{
						}
					}
					rPressure[g_qiya]=rPressureTmp[g_qiya];
				}
				//-----------------------------------------------------------------
	}
}
