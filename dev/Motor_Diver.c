#include "watchdog.h"
#include "Motor_Diver.h"

void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/* ±÷” πƒ‹*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	/*MOTOR1*/
	GPIO_MyStruct.GPIO_Pin = MOTOR1_A_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR1_A_GPIO, &GPIO_MyStruct);
	MOTOR1_A_STATE(0);
	GPIO_MyStruct.GPIO_Pin = MOTOR1_B_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR1_B_GPIO, &GPIO_MyStruct);
	MOTOR1_B_STATE(0);
	/*MOTOR2*/
	GPIO_MyStruct.GPIO_Pin = MOTOR2_A_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR2_A_GPIO, &GPIO_MyStruct);
	MOTOR2_A_STATE(0);
	GPIO_MyStruct.GPIO_Pin = MOTOR2_B_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR2_B_GPIO, &GPIO_MyStruct);
	MOTOR2_B_STATE(0);

}
