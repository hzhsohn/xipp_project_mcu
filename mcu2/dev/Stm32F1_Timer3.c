#include "Stm32F1_Timer3.h"

int kkUart1count=0;
extern int g_uart1len;

void Stm32F1_Timer3Init(void)
{
	NVIC_InitTypeDef MyTimerIrConfig;
	TIM_TimeBaseInitTypeDef MyTimerConfig;
	MyTimerConfig.TIM_Prescaler = 7200;
	MyTimerConfig.TIM_ClockDivision = TIM_CKD_DIV1;
	MyTimerConfig.TIM_CounterMode = TIM_CounterMode_Up;
	MyTimerConfig.TIM_Period = 99;
	MyTimerConfig.TIM_RepetitionCounter = 0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseInit(TIM3,&MyTimerConfig);
	TIM_Cmd(TIM3,ENABLE);
	/*ÖÐ¶Ï*/
	MyTimerIrConfig.NVIC_IRQChannel = TIM3_IRQn;
	MyTimerIrConfig.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&MyTimerIrConfig);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
}

void TIM3_IRQHandler(void)
{
	kkUart1count++;
	
	//周期计数复位
	 if(kkUart1count>500)
	 {
		 g_uart1len=0;
		 kkUart1count=0;
	 }
	//---------------------------
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

