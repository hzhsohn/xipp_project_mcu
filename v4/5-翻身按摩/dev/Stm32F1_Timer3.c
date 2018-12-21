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
	//发热垫
	if(g_run.JiaReTime1>0 )
	{
		 g_run.JiaReTime1--;
		 if(g_run.curJiaReWenDu <= g_run.JiaReWenDu1)
		 {
			 //开加热
			 _unit1(1);
			 _unit2(1);
		 }
		 else
		 {
			 _unit1(0);
			 _unit2(0);
		 }
	}
	else
	{
		_unit1(0);
		_unit2(0);
	}
	//---------------------------
	//按摩
	if(g_run.AnmoTime>0 )
	{
		 g_run.AnmoTime--;		 
		_unit3(1);
		_unit4(1);
		_unit5(1);
		_unit6(1);
		_unit7(1);
	}
	else
	{
		_unit3(0);
		_unit4(0);
		_unit5(0);
		_unit6(0);
		_unit7(0);
	}
	
	//-----------------------------
	//自动充气
	if(g_run.guan_qiya_percent<60)
	{
		_unit8(1);
	}
	else
	{
		_unit8(0);
	}
	
	//-----------------------------
	//排污开
	if(g_run.piai_wu_kai>0 )
	{
		 g_run.piai_wu_kai--;

		 _unit10(1);
	}
	else
	{
		_unit10(0);
	}
	
	//-----------------------------
	//排污关
	if(g_run.piai_wu_guan>0 )
	{
		 g_run.piai_wu_guan--;
		 _unit9(1);
	}
	else
	{
		_unit9(0);
	}
	
	//-----------------------------
	//小便阀门
	if(g_run.xiaobian_famen>0 )
	{
		 g_run.xiaobian_famen--;
		 _unit11(1);
	}
	else
	{
		_unit11(0);
	}
	
	//---------------------------
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

