#include "system_init.h"
#include "Stm32f1_uart1.h"
#include "Stm32f1_uart2.h"
#include "Stm32f1_uart3.h"
#include "InputDrive.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1.h"
#include "ds18b20_1.h"
#include "watchdog.h"
#include "flash_rw.h"
#include "Stm32F1_Timer2.h"
#include "Stm32F1_Timer3.h"
#include "key.h"
#include "OutputDrive.h"
#include "STM32F1_ADC0.h"
#include "a.h"

extern TagTimeRun g_run;

//循环时间间隔
#define DELAY_S  100

//中断运行chart
int isCleanRuning=0;
int ppxxStep=0;

//当前工作场景
EzhCleanSence g_cCurrentSence;

////////////////////////////////////////////////////////////////
void senceBegin(EzhCleanSence n)
{
		g_cCurrentSence=n;
		ppxxStep=0;
		isCleanRuning=1;
}

//场景延时
void senceDelayToValue(int*nCalca,int*ppxxStep,int jmpValue,int delay_ms)
{
	if((*nCalca) > delay_ms) 
	{
			*nCalca=0;
			(*ppxxStep)++;
	}
	else
	{
			if(0==isCleanRuning)//中断
			{g_cCurrentSence=ezhCleanSenceNone;(*nCalca)=0;}
			(*nCalca)=jmpValue;
	}
}

void senceDelayToNext(int*nCalca,int*ppxxStep,int delay_ms)
{
	if((*nCalca) > delay_ms) 
	{
			*nCalca=0;
			(*ppxxStep)++; 
	}
	else
	{
			if(0==isCleanRuning)//中断
			{g_cCurrentSence=ezhCleanSenceNone;(*nCalca)=0;}
			(*nCalca)++;
	}
}

void senceNext(int*nCalca,int*ppxxStep)
{
			*nCalca=0;
			(*ppxxStep)++;
}

void senceDone(void)
{
			g_cCurrentSence=ezhCleanSenceNone;  		//场景复位
			ppxxStep=0;
			isCleanRuning=0;
}

//
void LitteSenceRun(void)
{
	 switch((int)g_cCurrentSence)
	 {
		 case ezhCleanSence1:
					litteGiaoGiaoZhu();
			 break;
		 case ezhCleanSence2:
					litteLaSi();
			 break;
		 case ezhCleanSence3:
					litteQuengQueng();
			 break;
	 }
}

/*********************************************************

----运行场景----

***********************************************************/
void litteGiaoGiaoZhu(void)
{
	int n=0;
	static int nCalca=0;	
	switch(ppxxStep)
	{
		case 0:				
			//充气
			REL_1_STATE(1);for(n=0;n<200000;n++);
			REL_2_STATE(1);for(n=0;n<200000;n++);
		  //真空泵开	
			RELAY11_STATE(1);for(n=0;n<200000;n++);
			//气阀方向,抽
			RELAY3_STATE(1);for(n=0;n<200000;n++);
			RELAY5_STATE(1);for(n=0;n<200000;n++);
			RELAY7_STATE(0);for(n=0;n<200000;n++);
			senceNext(&nCalca,&ppxxStep);
			break;
		case 1:
			REL_L5_STATE((g_run.guan_qiya_percent[5]>40));
			REL_R5_STATE((g_run.guan_qiya_percent[6]>40));
			REL_L7_STATE((g_run.guan_qiya_percent[7]>40));
			REL_R7_STATE((g_run.guan_qiya_percent[8]>40));
			senceNext(&nCalca,&ppxxStep);
			break;							
		default: //完毕
			//真空泵
			RELAY11_STATE(0);
		  //充气
			REL_1_STATE(0);
			REL_2_STATE(0);
			//气阀方向,全关
			RELAY3_STATE(0); 
			RELAY5_STATE(0);
			RELAY7_STATE(0);
			//
			senceDone();
			break;
	}
}
void litteLaSi(void)
{
	int n=0;
	static int nCalca=0;	
	switch(ppxxStep)
	{
		case 0:				
			//充气
			REL_1_STATE(1);for(n=0;n<200000;n++);
			REL_2_STATE(1);for(n=0;n<200000;n++);
		  //真空泵开	
			RELAY11_STATE(1);for(n=0;n<200000;n++);
			//气阀方向,抽
			RELAY3_STATE(1);for(n=0;n<200000;n++);
			RELAY5_STATE(0);for(n=0;n<200000;n++);
			RELAY7_STATE(1);for(n=0;n<200000;n++);
			senceNext(&nCalca,&ppxxStep);
			break;
		case 1:
			REL_L5_STATE((g_run.guan_qiya_percent[5]<60));
			REL_R5_STATE((g_run.guan_qiya_percent[6]<60));
			REL_L7_STATE((g_run.guan_qiya_percent[7]<60));
			REL_R7_STATE((g_run.guan_qiya_percent[8]<60));
			senceNext(&nCalca,&ppxxStep);
			break;							
		default: //完毕
			//真空泵
			RELAY11_STATE(0);
		  //充气
			REL_1_STATE(0);
			REL_2_STATE(0);
			//气阀方向,全关
			RELAY3_STATE(0); 
			RELAY5_STATE(0);
			RELAY7_STATE(0);
			//
			senceDone();
			break;
	}
}

void litteQuengQueng(void)
{
	static int nCalca=0;	
	switch(ppxxStep)
	{
		case 0:	
			RELAY3_STATE(1); //电源
			RELAY5_STATE(1);
			RELAY7_STATE(0);

			senceNext(&nCalca,&ppxxStep);
			break;
		case 1:
			senceDelayToNext(&nCalca,&ppxxStep,1*DELAY_S);
			break;
		case 2:
			senceNext(&nCalca,&ppxxStep);
			break;
		case 3:
			senceDelayToNext(&nCalca,&ppxxStep,1*DELAY_S);
			break;									
		default: //完毕
			senceDone();
			break;
	}
}

