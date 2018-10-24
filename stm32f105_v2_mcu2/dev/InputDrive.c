#include "InputDrive.h"

void InputDriveInit(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/*ʱ��ʹ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_MyStruct.GPIO_Pin = SENSOR1_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(SENSOR1_GPIO, &GPIO_MyStruct);
	
	
}
