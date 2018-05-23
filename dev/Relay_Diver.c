#include "Relay_Diver.h"

void Relay_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/* ±÷” πƒ‹*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	/*RELAY1*/
	GPIO_MyStruct.GPIO_Pin = RELAY1_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY1_GPIO, &GPIO_MyStruct);
	RELAY1_STATE(LOW);
	/*RELAY2*/
	GPIO_MyStruct.GPIO_Pin = RELAY2_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY2_GPIO, &GPIO_MyStruct);
	RELAY2_STATE(LOW);
	/*RELAY3*/
	GPIO_MyStruct.GPIO_Pin = RELAY3_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY3_GPIO, &GPIO_MyStruct);
	RELAY3_STATE(LOW);
	/*RELAY4*/
	GPIO_MyStruct.GPIO_Pin = RELAY4_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY4_GPIO, &GPIO_MyStruct);
	RELAY4_STATE(LOW);
	/*RELAY5*/
	GPIO_MyStruct.GPIO_Pin = RELAY5_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY5_GPIO, &GPIO_MyStruct);
	RELAY5_STATE(LOW);
	/*RELAY6*/
	GPIO_MyStruct.GPIO_Pin = RELAY6_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY6_GPIO, &GPIO_MyStruct);
	RELAY6_STATE(LOW);
	/*RELAY7*/
	GPIO_MyStruct.GPIO_Pin = RELAY7_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY7_GPIO, &GPIO_MyStruct);
	RELAY7_STATE(LOW);
	/*RELAY8*/
	GPIO_MyStruct.GPIO_Pin = RELAY8_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY8_GPIO, &GPIO_MyStruct);
	RELAY8_STATE(LOW);
	/*RELAY9*/
	GPIO_MyStruct.GPIO_Pin = RELAY9_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY9_GPIO, &GPIO_MyStruct);
	RELAY9_STATE(LOW);


}
