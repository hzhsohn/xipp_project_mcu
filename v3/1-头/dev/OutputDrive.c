#include "OutputDrive.h"

void VOLUME_Configuration(void);

void OutputDriveInit(void)
{
	 VOLUME_Configuration();
	
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

void VOLUME_Configuration(void)
{
		GPIO_InitTypeDef GPIO_MyStruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_4;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_MyStruct);
		GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	
		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_5;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_MyStruct);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
}
