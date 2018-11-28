#include "Stm32F1_Timer3.h"
#include "InputDrive.h"
#include "logic.h"

extern int g_timeoverUart1;
extern int g_uart1len;

extern int g_timeoverUart2;
extern int g_uart2len;

extern int g_timeoverUart3;
extern int g_uart3len;

int g_intervalSend=0;
//最后执行时间
int g_interValLastExc=0;
//
extern 


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

	MyTimerIrConfig.NVIC_IRQChannel = TIM3_IRQn;
	MyTimerIrConfig.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&MyTimerIrConfig);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
}

void TIM3_IRQHandler(void)
{
	g_timeoverUart1++;
	g_timeoverUart2++;
	g_timeoverUart3++;
	g_intervalSend++;
	g_interValLastExc++;
	
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
	
	//搜索硬件状态指令
	if(g_intervalSend>50)
	{
			if(0==getCmdCount())
			{
				dev_status();
			}
			//加入搜索
			g_intervalSend=0;
	}
	
	//执行间隔
	if(g_interValLastExc>50)
	{
			sendLogic();
			g_interValLastExc=0;
	}
	
	
	//---------------------------
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

