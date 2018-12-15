#include "system_init.h"
#include "Stm32f1_uart1.h"
#include "Stm32f1_uart2.h"
#include "Stm32f1_uart3.h"
#include "InputDrive.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1.h"
#include "Stm32f1_ADC2.h"
#include "Motor_Diver.h"
#include "ds18b20_1.h"
#include "watchdog.h"
#include "flash_rw.h"
#include "Stm32F1_Timer2.h"
#include "Stm32F1_Timer3.h"
#include "key.h"
#include "OutputDrive.h"


//摄像头电机
int xiiiLimit=90000;
int xiii=1000000;
int xiii2=1000000;
int Motor1_do_step=0;
int Motor2_do_step=0;
int motor1_p_or_n=0;
int motor2_p_or_n=0;
int monLimitState1L;
int monLimitState1R;
int monLimitState2L;
int monLimitState2R;

//
void delay_s(int n)
{
		int i=0;
		for(i=0;i<n*10;i++)
		{ STM32_Delay_ms(100); }
}

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
			
			//DS18B20_Init();
			//DS18B20_Init1();
			//Adc_Init();
			//Adc2_Init();	
			//
			//Motor_Init();
			Stm32F1_Timer2Init();
			Stm32F1_Timer3Init();
			//InputDriveInit();
			//zhSCM_GPIOConfig();
			OutputDriveInit();
		 
			//-----------------------------------------
			//获取FALSH数据
			setFlashData();
			//-----------------------------------------

			//看门狗
			//watchdog_init();
			
			//音响
			GPIO_SetBits(GPIOB,GPIO_Pin_4);
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
			
			while(1)
			{
				//看门狗
				//watchdog_action();
				//
				
			}
}
