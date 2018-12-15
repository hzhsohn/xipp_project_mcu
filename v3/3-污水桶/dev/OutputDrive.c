#include "OutputDrive.h"

void Relay_Init(void);

void OutputDriveInit(void)
{
	 Relay_Init();
	
	{
		GPIO_InitTypeDef GPIO_MyStruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_10;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOD, &GPIO_MyStruct);
			GPIO_ResetBits(GPIOD,GPIO_Pin_10);	 
			//GPIO_SetBits(GPIOD,GPIO_Pin_10);
	 }
}


void Relay_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/* ±÷” πƒ‹*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
	/*RELAY1*/
	GPIO_MyStruct.GPIO_Pin = RELAY1_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY1_GPIO, &GPIO_MyStruct);
	RELAY1_STATE(0);
	/*RELAY2*/
	GPIO_MyStruct.GPIO_Pin = RELAY2_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY2_GPIO, &GPIO_MyStruct);
	RELAY2_STATE(0);
	/*RELAY3*/
	GPIO_MyStruct.GPIO_Pin = RELAY3_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY3_GPIO, &GPIO_MyStruct);
	RELAY3_STATE(0);
	/*RELAY4*/
	GPIO_MyStruct.GPIO_Pin = RELAY4_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY4_GPIO, &GPIO_MyStruct);
	RELAY4_STATE(0);
	/*RELAY5*/
	GPIO_MyStruct.GPIO_Pin = RELAY5_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY5_GPIO, &GPIO_MyStruct);
	RELAY5_STATE(0);
	/*RELAY6*/
	GPIO_MyStruct.GPIO_Pin = RELAY6_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY6_GPIO, &GPIO_MyStruct);
	RELAY6_STATE(0);
	/*RELAY7*/
	GPIO_MyStruct.GPIO_Pin = RELAY7_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY7_GPIO, &GPIO_MyStruct);
	RELAY7_STATE(0);
	/*RELAY8*/
	GPIO_MyStruct.GPIO_Pin = RELAY8_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY8_GPIO, &GPIO_MyStruct);
	RELAY8_STATE(0);
	/*RELAY9*/
	GPIO_MyStruct.GPIO_Pin = RELAY9_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY9_GPIO, &GPIO_MyStruct);
	RELAY9_STATE(0);


	/*RELAY10*/
	GPIO_MyStruct.GPIO_Pin = RELAY10_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY10_GPIO, &GPIO_MyStruct);
	RELAY10_STATE(0);


	/*RELAY11*/
	GPIO_MyStruct.GPIO_Pin = RELAY11_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY11_GPIO, &GPIO_MyStruct);
	RELAY11_STATE(0);


	/*RELAY12*/
	GPIO_MyStruct.GPIO_Pin = RELAY12_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY12_GPIO, &GPIO_MyStruct);
	RELAY12_STATE(0);

	/*RELAY13*/
	GPIO_MyStruct.GPIO_Pin = RELAY13_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY13_GPIO, &GPIO_MyStruct);
	RELAY13_STATE(0);
		
	/*RELAY14*/
	GPIO_MyStruct.GPIO_Pin = RELAY14_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY14_GPIO, &GPIO_MyStruct);
	RELAY14_STATE(0);
		
	/*RELAY15*/
	GPIO_MyStruct.GPIO_Pin = RELAY15_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY15_GPIO, &GPIO_MyStruct);
	RELAY15_STATE(0);
}

void RelayTest()
{
	int tmeCal=0;
	
	RELAY1_STATE(0);
	RELAY2_STATE(0);
	RELAY3_STATE(0);
	RELAY4_STATE(0);
	RELAY5_STATE(0);
	RELAY6_STATE(0);
	RELAY7_STATE(0);
	RELAY8_STATE(0);
	RELAY9_STATE(0);
	RELAY10_STATE(0);
	RELAY11_STATE(0);
	RELAY12_STATE(0);
	RELAY13_STATE(0);
	RELAY14_STATE(0);
	RELAY15_STATE(0);
	//-------------------------------------------------
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY1_STATE(1); 
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY2_STATE(1); 	
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY3_STATE(1); 
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY4_STATE(1);
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY5_STATE(1); 	
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY6_STATE(1); 
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY7_STATE(1); 	
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY8_STATE(1); 
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY9_STATE(1); 		
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY10_STATE(1);	
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY11_STATE(1); 
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY12_STATE(1); 		
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
	RELAY13_STATE(1); 	
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	RELAY14_STATE(1); 		
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	RELAY15_STATE(1); 					
	tmeCal=0;
	while(tmeCal<3600000)
	{
		tmeCal++;
	}
	
}
