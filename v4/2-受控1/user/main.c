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
#include "InputDrive.h"
#include "OutputDrive.h"
#include "a.h"


//关闭所有输出
void allClose()
{
		//
	 _unit1(0); 								
	 _unit2(0); 					
	 _unit3(0); 					
	 _unit4(0); 		 					
	 _junit1(0); 						
	 _junit2(0); 							
	 _junit3(0); 							
	 _junit4(0); 				 	
	 _junit5(0); 								
	 _junit6(0); 				 		
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
	//STM32F1_UART1_Init(115200);
	//STM32F1_UART2_Init(19200);
	STM32F1_UART3_Init(19200);

	//DS18B20_Init();
	//DS18B20_Init1();
	//Adc_Init();
	//Adc2_Init();
	//Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	//InputDriveInit();
	OutputDriveInit();
	//-----------------------------------------
	//获取FALSH数据
	setFlashData();
  //-----------------------------------------
//RelayTest();
	//看门狗
	//watchdog_init();	
	//
 	allClose();
	while(1)
	{
					//看门狗
					//watchdog_action();					
	}

}
