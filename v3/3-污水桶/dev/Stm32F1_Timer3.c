#include "Stm32F1_Timer3.h"
#include "InputDrive.h"
#include "OutputDrive.h"

extern int g_timeoverUart1;
extern int g_uart1len;

extern int g_timeoverUart2;
extern int g_uart2len;

extern int g_timeoverUart3;
extern int g_uart3len;

extern TagUpData485 ud485;
extern TagTimeRun g_run;

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

/*--------------------------------------------------
//
//-------------------------------------------------*/
void TIM3_IRQHandler(void)
{

	g_timeoverUart1++;
	g_timeoverUart2++;
	g_timeoverUart3++;
	
	//周期计数复位
	if(g_timeoverUart1>500)
	{
			g_uart1len=0;
			g_timeoverUart1=0;
	}
	if(g_timeoverUart2>500)
	{
			g_uart2len=0;
			g_timeoverUart2=0;
	}
	if(g_timeoverUart3>500)
	{
			g_uart3len=0;
			g_timeoverUart3=0;
	}

	//---------------------------
	//继电器操作
	if(g_run.juint1Time>0)
	{
			g_run.juint1Time--;
			_junit1(1);
	}
	else
	{
			_junit1(0);
	}
	
	if(g_run.juint2Time>0)
	{
			g_run.juint2Time--;
			_junit2(1);
	}
	else
	{
			_junit2(0);
	}
	
	if(g_run.juint3Time>0)
	{
			g_run.juint3Time--;
			_junit3(1);
	}
	else
	{
			_junit3(0);
	}
	
	if(g_run.juint4Time>0)
	{
			g_run.juint4Time--;
			_junit4(1);
	}
	else
	{
			_junit4(0);
	}
	
	if(g_run.juint5Time>0)
	{
			g_run.juint5Time--;
			_junit5(1);
	}
	else
	{
			_junit5(0);
	}
	
	if(g_run.juint6Time>0)
	{
			g_run.juint6Time--;
			_junit6(1);
	}
	else
	{
			_junit6(0);
	}
	//---------------------------
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

