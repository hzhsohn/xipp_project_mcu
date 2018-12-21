#include "InputDrive.h"

void InputDriveInit(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/* ±÷” πƒ‹*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_MyStruct.GPIO_Pin = SENSOR1_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR1_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = SENSOR2_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR2_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = SENSOR3_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR3_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = SENSOR4_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR4_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = SENSOR5_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR5_GPIO, &GPIO_MyStruct);
	
}
