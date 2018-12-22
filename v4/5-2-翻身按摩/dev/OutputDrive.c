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
	/*时钟使能*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);
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

//---------------------------------------------------------
//气垫阀门

	/*REL_1*/
	GPIO_MyStruct.GPIO_Pin = REL_1_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_1_GPIO, &GPIO_MyStruct);
	REL_1_STATE(0);
	
	/*REL_2*/
	GPIO_MyStruct.GPIO_Pin = REL_2_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_2_GPIO, &GPIO_MyStruct);
	REL_2_STATE(0);
	
	/*REL_3*/
	GPIO_MyStruct.GPIO_Pin = REL_3_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_3_GPIO, &GPIO_MyStruct);
	REL_3_STATE(0);

	/*REL_4*/
	GPIO_MyStruct.GPIO_Pin = REL_4_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_4_GPIO, &GPIO_MyStruct);
	REL_4_STATE(0);

	/*REL_L1*/
	GPIO_MyStruct.GPIO_Pin = REL_L1_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L1_GPIO, &GPIO_MyStruct);
	REL_L1_STATE(0);

	/*REL_L2*/
	GPIO_MyStruct.GPIO_Pin = REL_L2_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L2_GPIO, &GPIO_MyStruct);
	REL_L2_STATE(0);

	/*REL_L3*/
	GPIO_MyStruct.GPIO_Pin = REL_L3_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L3_GPIO, &GPIO_MyStruct);
	REL_L3_STATE(0);

	/*REL_L4*/
	GPIO_MyStruct.GPIO_Pin = REL_L4_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L4_GPIO, &GPIO_MyStruct);
	REL_L4_STATE(0);

	/*REL_L5*/
	GPIO_MyStruct.GPIO_Pin = REL_L5_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L5_GPIO, &GPIO_MyStruct);
	REL_L5_STATE(0);

	/*REL_L6*/
	GPIO_MyStruct.GPIO_Pin = REL_L6_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L6_GPIO, &GPIO_MyStruct);
	REL_L6_STATE(0);

	/*REL_L7*/
	GPIO_MyStruct.GPIO_Pin = REL_L7_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L7_GPIO, &GPIO_MyStruct);
	REL_L7_STATE(0);

	/*REL_L8*/
	GPIO_MyStruct.GPIO_Pin = REL_L8_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L8_GPIO, &GPIO_MyStruct);
	REL_L8_STATE(0);

	/*REL_L9*/
	GPIO_MyStruct.GPIO_Pin = REL_L9_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L9_GPIO, &GPIO_MyStruct);
	REL_L9_STATE(0);

	/*REL_L10*/
	GPIO_MyStruct.GPIO_Pin = REL_L10_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L10_GPIO, &GPIO_MyStruct);
	REL_L10_STATE(0);

	/*REL_L11*/
	GPIO_MyStruct.GPIO_Pin = REL_L11_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L11_GPIO, &GPIO_MyStruct);
	REL_L11_STATE(0);

	/*REL_L12*/
	GPIO_MyStruct.GPIO_Pin = REL_L12_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_L12_GPIO, &GPIO_MyStruct);
	REL_L12_STATE(0);


	/*REL_R1*/
	GPIO_MyStruct.GPIO_Pin = REL_R1_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R1_GPIO, &GPIO_MyStruct);
	REL_R1_STATE(0);

	/*REL_R2*/
	GPIO_MyStruct.GPIO_Pin = REL_R2_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R2_GPIO, &GPIO_MyStruct);
	REL_R2_STATE(0);

	/*REL_R3*/
	GPIO_MyStruct.GPIO_Pin = REL_R3_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R3_GPIO, &GPIO_MyStruct);
	REL_R3_STATE(0);

	/*REL_R4*/
	GPIO_MyStruct.GPIO_Pin = REL_R4_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R4_GPIO, &GPIO_MyStruct);
	REL_R4_STATE(0);

	/*REL_R5*/
	GPIO_MyStruct.GPIO_Pin = REL_R5_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R5_GPIO, &GPIO_MyStruct);
	REL_R5_STATE(0);

	/*REL_R6*/
	GPIO_MyStruct.GPIO_Pin = REL_R6_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R6_GPIO, &GPIO_MyStruct);
	REL_R6_STATE(0);

	/*REL_R7*/
	GPIO_MyStruct.GPIO_Pin = REL_R7_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R7_GPIO, &GPIO_MyStruct);
	REL_R7_STATE(0);

	/*REL_R8*/
	GPIO_MyStruct.GPIO_Pin = REL_R8_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R8_GPIO, &GPIO_MyStruct);
	REL_R8_STATE(0);

	/*REL_R9*/
	GPIO_MyStruct.GPIO_Pin = REL_R9_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R9_GPIO, &GPIO_MyStruct);
	REL_R9_STATE(0);

	/*REL_R10*/
	GPIO_MyStruct.GPIO_Pin = REL_R10_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R10_GPIO, &GPIO_MyStruct);
	REL_R10_STATE(0);

	/*REL_R11*/
	GPIO_MyStruct.GPIO_Pin = REL_R11_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R11_GPIO, &GPIO_MyStruct);
	REL_R11_STATE(0);

	/*REL_R12*/
	GPIO_MyStruct.GPIO_Pin = REL_R12_PIN;
	GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(REL_R12_GPIO, &GPIO_MyStruct);
	REL_R12_STATE(0);
	
}

void RelayTest()
{
	int tmeCal=0;
	const int a = 360000;		//3600000
	
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
	
	REL_1_STATE(0);
	REL_2_STATE(0);
	REL_3_STATE(0); 
	REL_4_STATE(0);
	REL_L1_STATE(0);
	REL_L2_STATE(0);
	REL_L3_STATE(0);
	REL_L4_STATE(0);
	REL_L5_STATE(0);
	REL_L6_STATE(0);
	REL_L7_STATE(0);
	REL_L8_STATE(0);
	REL_L9_STATE(0);
	REL_L10_STATE(0);
	REL_L11_STATE(0);
	REL_L12_STATE(0);
	REL_R1_STATE(0);
	REL_R2_STATE(0);
	REL_R3_STATE(0);
	REL_R4_STATE(0);
	REL_R5_STATE(0);
	REL_R6_STATE(0);
	REL_R7_STATE(0);
	REL_R8_STATE(0);
	REL_R9_STATE(0);
	REL_R10_STATE(0);
	REL_R11_STATE(0);
	REL_R12_STATE(0);


	//-------------------------------------------------
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	RELAY1_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	RELAY2_STATE(1); 	
	tmeCal=0;
	while(tmeCal<a)
	{		tmeCal++;
	}
	
	RELAY3_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	RELAY4_STATE(1);
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	RELAY5_STATE(1); 	
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	RELAY6_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	RELAY7_STATE(1); 	
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	RELAY8_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	RELAY9_STATE(1); 		
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	RELAY10_STATE(1);	
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	RELAY11_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	//-------------------------------
	REL_1_STATE(1);
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_2_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_3_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_4_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L1_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L2_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L3_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L4_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L5_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L6_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L7_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L8_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L9_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L10_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L11_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_L12_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R1_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R2_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R3_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R4_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R5_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R6_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R7_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R8_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R9_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R10_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R11_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
	
	REL_R12_STATE(1); 
	tmeCal=0;
	while(tmeCal<a)
	{
		tmeCal++;
	}
		
}
