#include "mini-data.h"
#include "Stm32f1_uart3.h"
#include "stdio.h"
#include "stdlib.h"
#include "logic.h"

//循环时间间隔
#define DELAY_S  100

//中断运行chart
int isCleanRuning=0;
int ppxxStep=0;

//当前工作场景
EzhCleanSence g_cCurrentSence;

//发送中断指令
void urgentSenceInterrupt(void)
{
	int i=0,n=0;
	senceDone();
	for(i=0;i<5;i++)
	{
			uart3Send(0xFF,0xFF,0,NULL,0);
			for(n=0;n<10000;n++);
	}
}

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
		if(ezhCleanSence1==g_cCurrentSence) 
		{			
				litteSenceRunXuXu();
		}
		else if(ezhCleanSence2==g_cCurrentSence) 
		{			
				litteSenceRunPooPoo();
		}
		else if(ezhCleanSence3==g_cCurrentSence)
		{
				litteSenceRunHuWai();
		}
		else if(ezhCleanSence4==g_cCurrentSence)
		{
				litteSenceRunChongXi();
		}
		else if(ezhCleanSence5==g_cCurrentSence)
		{
				litteSenceRunHongGan();
		}
		else if(ezhCleanSence6==g_cCurrentSence)
		{
				litteSenceRunChuQun();
		}
		else if(ezhCleanSence7==g_cCurrentSence)
		{
				litteSenceRunAnMo();
		}
		else if(ezhCleanSence8==g_cCurrentSence)
		{
				litteSenceRunBaoNang();
				
		}
}



/*********************************************************

----运行场景----

***********************************************************/
void litteSenceRunXuXu()
{					
				static int nCalca=0;	
				switch(ppxxStep)
				{
					case 0:	
						uart3Send(1,11,60,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 2:
						uart3Send(1,12,60,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 3:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;									
					default: //完毕
						uart3Send(1,13,60,NULL,0);
						senceDone();
						break;
				}
}

void litteSenceRunPooPoo()
{				
				static int nCalca=0;	
				switch(ppxxStep)
				{
					case 0:	
						uart3Send(1,21,60,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 2:
						uart3Send(1,22,60,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 3:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;									
					default: //完毕
						uart3Send(1,23,60,NULL,0);
						senceDone();
						break;
				}
}

void litteSenceRunHuWai(void)
{		
				static int nCalca=0;	
				switch(ppxxStep)
				{
					case 0:	
						uart3Send(1,31,60,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 2:
						uart3Send(1,32,60,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 3:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;									
					default: //完毕
						uart3Send(1,33,60,NULL,0);
						senceDone();
						break;
				}
}
void litteSenceRunChongXi(void)
{
				static int nCalca=0;	
				switch(ppxxStep)
				{
					case 0:	
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 2:
						senceNext(&nCalca,&ppxxStep);
						break;
					case 3:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;									
					default: //完毕
						senceDone();
						break;
				}
}

/********************************
//烘干
*********************************/
void litteSenceRunHongGan(void)
{
				static int nCalca=0;	
				switch(ppxxStep)
				{
					case 0:	
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 2:
						senceNext(&nCalca,&ppxxStep);
						break;
					case 3:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;									
					default: //完毕
						senceDone();
						break;
				}
}

/********************************
//除菌
*********************************/
void litteSenceRunChuQun(void)
{
				static int nCalca=0;	
				switch(ppxxStep)
				{
					case 0:	
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 2:
						senceNext(&nCalca,&ppxxStep);
						break;
					case 3:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;									
					default: //完毕
						senceDone();
						break;
				}
}

/********************************
//按摩
*********************************/
void litteSenceRunAnMo(void)
{
				static int nCalca=0;	
				switch(ppxxStep)
				{
					case 0:	
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 2:
						senceNext(&nCalca,&ppxxStep);
						break;
					case 3:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;									
					default: //完毕
						senceDone();
						break;
				}
}

/********************************
//保暖
*********************************/
void litteSenceRunBaoNang(void)
{
				static int nCalca=0;	
				switch(ppxxStep)
				{
					case 0:	
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 2:
						senceNext(&nCalca,&ppxxStep);
						break;
					case 3:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;									
					default: //完毕
						senceDone();
						break;
				}
}
