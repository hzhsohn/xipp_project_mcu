#include "Motor_Diver.h"
u8_t nMotor1Cnt;
u8_t nMotor2Cnt;
u8_t nMotor1State;
u8_t nMotor2State;
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/*Ê±ÖÓÊ¹ÄÜ*/
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
void Motor_State(void)
{
	switch(nMotor1State)
	{
		case 0x00:
			MOTOR1_A_STATE(0);
			MOTOR1_B_STATE(0);
			break;
		case 0x01:
			MOTOR1_A_STATE(1);
			MOTOR1_B_STATE(0);
			break;
		case 0x02:
			MOTOR1_A_STATE(0);
			MOTOR1_B_STATE(1);
			break;
	}
	
	switch(nMotor2State)
	{
		case 0x00:
			MOTOR2_A_STATE(0);
			MOTOR2_B_STATE(0);
			break;
		case 0x01:
			MOTOR2_A_STATE(1);
			MOTOR2_B_STATE(0);
			break;
		case 0x02:
			MOTOR2_A_STATE(0);
			MOTOR2_B_STATE(1);
			break;
	}
}
void MOTOR_TIMER_ISR(void)
{
		if (nMotor1State!=0x00)
	{
		nMotor1Cnt++;
		if (nMotor1Cnt>=MOTORTIME)
		{
			nMotor1State = 0x00;
			nMotor1Cnt = 0;
		}
	}
	else
	{
		nMotor1Cnt = 0;
	}
	
	if (nMotor2State!=0x00)
	{
		nMotor2Cnt++;
		if (nMotor2Cnt>=MOTORTIME)
		{
			nMotor2State = 0x00;
			nMotor2Cnt = 0;
		}
	}
	else
	{
		nMotor2Cnt = 0;
	}
	
}
