#include "system_init.h"
#include "BeeSpeaker_Diver.h"
#include "Stm32F1_Timer2.h"
#include "Stm32F1_Timer3.h"
#include "STM32_Delay.h"
#include "Relay_Diver.h"
#include "Stm32f1_uart1_diver.h"
#include "Stm32f1_uart2_diver.h"
#include "Stm32f1_uart3_diver.h"

void Code_Init(void)
{
	  ErrorStatus HSEStartUpStatus;
		SystemInit();	
		RCC_HSEConfig(RCC_HSE_ON);
		HSEStartUpStatus = RCC_WaitForHSEStartUp();
		if(HSEStartUpStatus == SUCCESS)
		{

		}		
		STM32_Delay_init();
		STM32F1_UART1_Init(9600);
		//STM32F1_UART2_Init(230400);
		//STM32F1_UART3_Init(115200);
		
		Stm32F1_Timer2Init();
		Stm32F1_Timer3Init();

		Relay_Init();
}
