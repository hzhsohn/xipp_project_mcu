#include "system_init.h"
#include "BeeSpeaker_Diver.h"
#include "Stm32f1_uart1_diver.h"
#include "Stm32f1_uart2_diver.h"
#include "Stm32f1_uart3_diver.h"
#include "Relay_Diver.h"
#include "mini-data.h"
#include "watchdog.h"
#include "flash_rw.h"

void initDev(void);
void sence1(void);
void sence2(void);
void sence3(void);
void sence4(void);
void sence5(void);

void delay_s(int n)
{
		int i=0;
		for(i=0;i<n*10;i++)
		{ STM32_Delay_ms(100); }
}

int main(void)
{
	Code_Init();
	
  initDev();
	while(1)
	{ }
}


//初始化
void initDev()
{
		allClose();
	
		RELAY2_STATE(1);
		RELAY4_STATE(1);
		RELAY7_STATE(1);
		RELAY9_STATE(1);
		RELAY11_STATE(1);
		RELAY13_STATE(1);
		//
		delay_s(15);
		//
		allClose();
}

//1号充气
void sence1()
{
		RELAY5_STATE(1);
		delay_s(3);
		//
		RELAY1_STATE(1);
		RELAY8_STATE(1);
		delay_s(55);
		//
		RELAY1_STATE(0);
		RELAY8_STATE(0);
		//
		RELAY9_STATE(1);
		RELAY2_STATE(1);
		delay_s(15);
		//
		RELAY9_STATE(0);
		RELAY2_STATE(0);
		RELAY5_STATE(0);
		//
		allClose();
}

//1号放气
void sence2()
{
		RELAY5_STATE(1);
		delay_s(3);
		//
		RELAY3_STATE(1);
		RELAY12_STATE(1);
		delay_s(55);
		//
		RELAY3_STATE(0);
		RELAY12_STATE(0);
		//
		RELAY13_STATE(1);
		RELAY4_STATE(1);
		delay_s(15);
		//
		RELAY13_STATE(0);
		RELAY4_STATE(0);
		RELAY5_STATE(0);
		//
		allClose();
}

//2号冲气
void sence3()
{
		RELAY1_STATE(1);
		RELAY6_STATE(1);
		delay_s(3);
		//
		RELAY5_STATE(1);
		delay_s(55);
		//
		RELAY1_STATE(0);
		RELAY6_STATE(0);
		//
		RELAY7_STATE(1);
		RELAY2_STATE(1);
		delay_s(15);
		//
		RELAY7_STATE(0);
		RELAY2_STATE(0);
		RELAY5_STATE(0);
		//
		allClose();
}

//3号放气
void sence4()
{
		RELAY3_STATE(1);
		RELAY10_STATE(1);
		delay_s(3);
		//
		RELAY5_STATE(1);
		delay_s(55);
		//
		RELAY3_STATE(0);
		RELAY10_STATE(0);
		//
		RELAY11_STATE(1);
		RELAY4_STATE(1);
		delay_s(15);
		//
		RELAY11_STATE(0);
		RELAY4_STATE(0);
		RELAY5_STATE(0);
		//
		allClose();
}

//都平了
void sence5()
{
		sence2();
		sence4();
}

