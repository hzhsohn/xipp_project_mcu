#include "watchdog.h"
#include "Motor_Diver.h"

void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/*时钟使能*/
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
	
		GPIO_MyStruct.GPIO_Pin = MOTOR1_C_PIN;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(MOTOR1_C_GPIO, &GPIO_MyStruct);
		MOTOR1_C_STATE(0);
		GPIO_MyStruct.GPIO_Pin = MOTOR1_D_PIN;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(MOTOR1_D_GPIO, &GPIO_MyStruct);
		MOTOR1_D_STATE(0);
		
	
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

		GPIO_MyStruct.GPIO_Pin = MOTOR2_C_PIN;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(MOTOR2_C_GPIO, &GPIO_MyStruct);
		MOTOR2_C_STATE(0);
		GPIO_MyStruct.GPIO_Pin = MOTOR2_D_PIN;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(MOTOR2_B_GPIO, &GPIO_MyStruct);
		MOTOR2_D_STATE(0);

	//输入
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_MyStruct.GPIO_Pin = MOTOR1_LIMIT_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(MOTOR1_LIMIT_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = MOTOR2_LIMIT_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(MOTOR2_LIMIT_GPIO, &GPIO_MyStruct);
}
