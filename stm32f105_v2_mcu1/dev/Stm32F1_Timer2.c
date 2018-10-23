#include "Stm32F1_Timer2.h"
#include "InputDrive.h"
#include "Motor_Diver.h"
#include "OutputDrive.h"
#include "STM32F1_UART1.h"

extern unsigned char g_cCleanCurrentSence;
int jaopan=0;

void Stm32F1_Timer2Init(void)
{
	NVIC_InitTypeDef MyTimerIrConfig;
	TIM_TimeBaseInitTypeDef MyTimerConfig;
	MyTimerConfig.TIM_Prescaler = 720*3+10;
	MyTimerConfig.TIM_ClockDivision = TIM_CKD_DIV1;
	MyTimerConfig.TIM_CounterMode = TIM_CounterMode_Up;
	MyTimerConfig.TIM_Period = 10;
	MyTimerConfig.TIM_RepetitionCounter = 0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseInit(TIM2,&MyTimerConfig);
	TIM_Cmd(TIM2,ENABLE);
	/*ÖÐ¶Ï*/
	MyTimerIrConfig.NVIC_IRQChannel = TIM2_IRQn;
	MyTimerIrConfig.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&MyTimerIrConfig);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
}

//
//-------------------------------------------------*/
int deji_A=0;
int bsmamama=0;
void TIM2_IRQHandler(void)
{

	 //电机
	deji_A=!deji_A;
	MOTOR1_A_STATE(deji_A);
	
	if(jaopan || ezhCleanSence2==(g_cCleanCurrentSence&0xf0))
	{		
		//变速马达
		if(bsmamama>100)
		{
			bsmamama=0;
			BS_MADAMADA_STATE(deji_A);
		}
		bsmamama++;
	}
	else
	{
		BS_MADAMADA_STATE(0);
	}
	
	//
	sceMotor1_do();
	sceMotor2_do();
	sceMotorDemo_do();
	//---------------------------
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

