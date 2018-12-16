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
#include "STM32F1_ADC0.h"

//提交的数据
TagUpData485 ud485;
TagTimeRun g_run;

//--
//温度
int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0;
s16 rTrueWaterTemp=0;
int isWaterTooHot=0;
int isCheckWaterSensorErr=0; //水温防错误限制

//气压
u16_t rPressure[10]={0},rPressureTmp[10]={0};
u16_t rTruePressure1[10]={0};
int isCheckDZCQSensorErr[10]={0};


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
	STM32F1_UART1_Init(115200);
	STM32F1_UART2_Init(19200);
	STM32F1_UART3_Init(19200);
	
	DS18B20_Init();
	DS18B20_Init1();
	
	Adc_Init0();
	Adc_Init();
	Adc2_Init();
	
	Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	InputDriveInit();
	OutputDriveInit();
	//zhSCM_GPIOConfig(); 	
	
	//-----------------------------------------
	//获取FALSH数据
	setFlashData();
  //-----------------------------------------

	//看门狗
	//watchdog_init();
	
	while(1)
	{
				//------------------------------------------------------------------
				//当前温度
				rWaterTemp=DS18B20_Get_Temp();
				if(rWaterTemp<2000 && rWaterTemp> -200) //限制位
				{
					ntmp=rWaterTemp-rWaterTemperature;
					if(ntmp<20 && ntmp>-20)	//限制突变幅度
					{
							isWaterTooHot=0;							
							if(rWaterTemp > 60*10) //加热器有问题了吧,太高了就是加热器有问题了.
							{
									//水太热了.发到串口告诉上位机端,通知护士小妹妹,机器故障了
									isWaterTooHot=1;
							}								
							rTrueWaterTemp=rWaterTemp;
							isCheckWaterSensorErr=0;
							ud485.PiGuWenDu=rTrueWaterTemp;
							g_run.curJiaReWenDu=rTrueWaterTemp;
					}
					rWaterTemperature=rWaterTemp;
				}
				else
				{
						isCheckWaterSensorErr++;
						if(isCheckWaterSensorErr>10) //传感数据有毛病关掉加热继电器
						{
								//传感器有毛病了.关掉继电器
								ud485.PiGuWenDu=0;
						}
				}
			
				//------------------------------------------------------------------
				//气压1
				rPressureTmp[0] = Get_Adc_Average0(10);
				ntmp=rPressureTmp[0]-rPressure[0];
				if(ntmp<60 && ntmp>-60) //限制突变幅度
				{
					g_run.guan_qiya_percent=(float)rPressureTmp[0]/4096.0f*100;
					rTruePressure1[0]=rPressureTmp[0];
					isCheckDZCQSensorErr[0]=0;
				}
				else
				{
					isCheckDZCQSensorErr[0]++;						
					if(isCheckDZCQSensorErr[0]>10) //传感数据有毛病关掉继电器
					{
					}
				}
				rPressure[0]=rPressureTmp[0];
				
				//------------------------------------------------------------------
				//气压其它
				//Get_Adc_Average
		
		}
}
