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
	
	GPIO_MyStruct.GPIO_Pin = SENSOR4_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR4_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = SENSOR5_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR5_GPIO, &GPIO_MyStruct);
		
	GPIO_MyStruct.GPIO_Pin = SENSOR6_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR6_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = SENSOR7_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR7_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = SENSOR8_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR8_GPIO, &GPIO_MyStruct);
	
}
