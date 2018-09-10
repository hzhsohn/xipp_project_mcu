#include "Stm32F1_Timer3.h"
#include "TouchKey_Diver.h"
#include "Sensor.h"
#include "Motor_Diver.h"

int kk=0;
int kk2=0;
int kk_1ms=0;
u16_t sCount1ms;
int kkUart1count=0;
extern int g_uart1len;

void aurtEventStatus();

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
Func_Staus CountToOneSecond(void)
{
	if (sCount1ms<100)
	{
		sCount1ms++;
	}
	else
	{
		sCount1ms=0;
		return _Enable;
	}
	return _Disable;
}
/*--------------------------------------------------
//
//-------------------------------------------------*/


void TIM3_IRQHandler(void)
{

	TOUCHKEY_TIMER_ISR();//按钮中断处理函数
	kk++;
	kk2++;	
	kk_1ms++;
	kkUart1count++;
	
	//周期计数复位
	 if(kkUart1count>500)
	 {
		 g_uart1len=0;
		 kkUart1count=0;
	 }
	 
	 //------------------------------------------------------------------
	 //上传数据
		if(kk2>200)
		{
					aurtEventStatus();
					kk2=0;
		}
	//---------------------------
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

