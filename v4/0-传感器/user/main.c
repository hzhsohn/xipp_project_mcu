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

//大小便检测
#define dxbPooPoo  				SENSOR4_STATE()?0:1    //屎
#define dxbXuXu	  				SENSOR5_STATE()?0:1    //尿

//--
//温度
int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0,rGasTemperature=0,rGasTemp=0;
s16 rTrueWaterTemp=0,rTrueGasTemp=0;
int isWaterTooHot=0;
int isGasTooHot=0;
int isCheckWaterSensorErr=0; //水温防错误限制
int isCheckGasSensorErr=0;//水温防错误限制
int isCheckBedCQSensorErr=0;//气压防错误限制
int isCheckDZCQSensorErr=0;	//气压防错误限制

//气压
u16_t rPressure=0,rPressureTmp=0,rPressure2=0,rPressure2Tmp=0,rPressure3=0,rPressure3Tmp=0;
u16_t rTruePressure1=0,rTruePressure2=0,rTruePressure3=0;

//屎屎尿尿的防抖动
int rPoopoDD=0;
int rXuxuDD=0;
int pdxbPooPoo;
int pdxbXuXu;
//
int isTextPOPO=0;
int isTextXUXU=0;

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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);	
	STM32_Delay_init();
	//STM32F1_UART1_Init(115200);
	//STM32F1_UART2_Init(19200);
	STM32F1_UART3_Init(19200);
	
	//DS18B20_Init();
	//DS18B20_Init1();
	//Adc_Init();
	//Adc2_Init();
	//Stm32F1_Timer2Init();
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
				//看门狗
				//watchdog_action();
				//
				pdxbPooPoo=dxbPooPoo;
				pdxbXuXu=dxbXuXu;
			
				//------------------------------------------------------------------
				//检测有无尿拉下来		
				if(pdxbXuXu)
				{
					rXuxuDD++;
					if(rXuxuDD>3)
					{
							rXuxuDD=0;
							uart3Send(0,1,NULL,0);
					}
				}
				else
				{
						rXuxuDD=0;
				}
				//------------------------------------------------------------------
				//检测有没有屎掉下来
				if(pdxbPooPoo)
				{
					rPoopoDD++;
					if(rPoopoDD>3)
					{
							rPoopoDD=0;
							uart3Send(0,2,NULL,0);
					}
				}
				else
				{
					rPoopoDD=0;
				}

				/*//------------------------------------------------------------------
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
*/
				//-------------------------------------------------------------------
				/*//空气加热,实时条件限制
				rGasTemp=DS18B20_Get_Temp1(); 
				if(rGasTemp<2000 && rGasTemp> -200) //限制位
				{
					ntmp=rGasTemp-rGasTemperature;
					if(ntmp<20 && ntmp>-20) //限制突变幅度
					{
							isGasTooHot=0;							
							if(rGasTemp > 60*10) //加热器有问题了吧,太高了就是加热器有问题了.
							{
								//气温太热了.发到串口告诉上位机端,通知护士小妹妹,机器故障了
								isGasTooHot=1;
							}
							rTrueGasTemp=rGasTemp;
							isCheckGasSensorErr=0;
							g_run.curJiaReWenDu=rTrueGasTemp;
					}
					rGasTemperature=rGasTemp;
				}
				else
				{
					isCheckGasSensorErr++;						
					if(isCheckGasSensorErr>10) //传感数据有毛病关掉加热继电器
					{
							//传感器有毛病了.关掉继电器
							g_run.curJiaReWenDu=-1;
					}
				}*/
		}		
}
