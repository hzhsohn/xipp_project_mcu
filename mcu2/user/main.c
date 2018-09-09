#include "system_init.h"
#include "BeeSpeaker_Diver.h"
#include "Stm32f1_uart1_diver.h"
#include "Stm32f1_uart2_diver.h"
#include "Stm32f1_uart3_diver.h"
#include "Relay_Diver.h"
#include "mini-data.h"
#include "watchdog.h"
#include "flash_rw.h"


void sence1();
void sence2();
void sence3();
void sence4();
void sence5();

#define DELAY_S			10
#define DELAY_S2		5

int main(void)
{
	Code_Init();
	
	//RelayTest();
	/*sence1();
	sence2();
	sence3();
	sence4();
	sence5();*/
	
	while(1)
	{
	}
}

//1号充气
void sence1()
{
		int i=0;
		RELAY1_STATE(1);
		RELAY5_STATE(1);
		RELAY8_STATE(1);
		for(i=0;i<1000;i++)
		{
			STM32_Delay_ms(DELAY_S);
		}
		RELAY9_STATE(1);
		RELAY5_STATE(0);
		RELAY2_STATE(1);
		
		for(i=0;i<1000;i++)
		{
			STM32_Delay_ms(DELAY_S2);
		}
		allClose();
}

//1号放气
void sence2()
{
		int i=0;
		RELAY3_STATE(1);
		RELAY5_STATE(1);
		RELAY12_STATE(1);
		for(i=0;i<1000;i++)
		{
			STM32_Delay_ms(DELAY_S);
		}
		RELAY13_STATE(1);
		RELAY5_STATE(0);
		RELAY4_STATE(1);
		
		for(i=0;i<1000;i++)
		{
			STM32_Delay_ms(DELAY_S2);
		}
		
		allClose();
}

//2号冲气
void sence3()
{
		int i=0;
		RELAY1_STATE(1);
		RELAY5_STATE(1);
		RELAY6_STATE(1);
		for(i=0;i<1000;i++)
		{
			STM32_Delay_ms(DELAY_S);
		}
		RELAY7_STATE(1);
		RELAY5_STATE(0);
		RELAY2_STATE(1);
		
		for(i=0;i<1000;i++)
		{
			STM32_Delay_ms(DELAY_S2);
		}
		
		allClose();
}

//3号放气
void sence4()
{
		int i=0;
		RELAY3_STATE(1);
		RELAY5_STATE(1);
		RELAY10_STATE(1);
		for(i=0;i<1000;i++)
		{
			STM32_Delay_ms(DELAY_S);
		}
		RELAY11_STATE(1);
		RELAY5_STATE(0);
		RELAY4_STATE(1);
		
		for(i=0;i<1000;i++)
		{
			STM32_Delay_ms(DELAY_S2);
		}
		
		allClose();
}

//都平了
void sence5()
{
		sence2();
		sence4();
}

