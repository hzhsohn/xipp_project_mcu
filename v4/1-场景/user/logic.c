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
				litteSenceRunAutoXuXu();
		}
		else if(ezhCleanSence2==g_cCurrentSence) 
		{			
				litteSenceRunAutoPooPoo();
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
		else if(ezhCleanSence9==g_cCurrentSence)
		{
				litteSenceRunXuXu();
		}
		else if(ezhCleanSence10==g_cCurrentSence)
		{
				litteSenceRunPooPoo();
		}
}



/*********************************************************

----运行场景----

***********************************************************/
void litteSenceRunAutoXuXu(void)
{
			static int nCalca=0;	
			switch(ppxxStep)
			{
				case 0:	
					senceDelayToNext(&nCalca,&ppxxStep,15*DELAY_S);
					break;
				default:
					senceDone();
					senceBegin(ezhCleanSence9);
					break;
			}
}
void litteSenceRunAutoPooPoo(void)
{
			static int nCalca=0;	
			switch(ppxxStep)
			{
				case 0:	
					senceDelayToNext(&nCalca,&ppxxStep,60*DELAY_S);
					break;
				default:
					senceDone();
					senceBegin(ezhCleanSence10);
					break;
			}
}
void litteSenceRunXuXu()
{					
				static int nCalca=0;	
				switch(ppxxStep)
				{
					//---------------
					//抽走尿尿
					case 0:	
						uart3Send(2,17,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;
					case 2:
						uart3Send(2,17,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//-----------------
					//洗鸡鸡
					case 3:	
						uart3Send(2,2,10,NULL,0);
						uart3Send(2,12,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 4:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 5:
						uart3Send(2,2,0,NULL,0);
						uart3Send(2,12,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//-----------------
					//让鸡鸡休息2秒
					case 6:
						senceDelayToNext(&nCalca,&ppxxStep,2*DELAY_S);
						break;
					//-----------------
					//吹干鸡鸡
					case 7:	
						uart3Send(2,10,10,NULL,0);
						uart3Send(2,13,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 8:
						senceDelayToNext(&nCalca,&ppxxStep,10*DELAY_S);
						break;
					case 9:
						uart3Send(2,10,0,NULL,0);
						uart3Send(2,13,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 10:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 11:
						uart3Send(2,10,10,NULL,0);
						uart3Send(2,13,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 12:
						uart3Send(2,10,0,NULL,0);
						uart3Send(2,13,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//---------------					
					//抽走洗鸡鸡水
					case 13:	
						uart3Send(2,17,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 14:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;
					case 15:
						uart3Send(2,17,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//
					default: //完毕
						senceDone();
						break;
				}
}

void litteSenceRunPooPoo()
{				
				static int nCalca=0;	
				switch(ppxxStep)
				{
					//------------------------
					//淋水
					case 0:	
						uart3Send(2,2,10,NULL,0);
						uart3Send(2,15,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,2*DELAY_S);
						break;
					case 2:
						uart3Send(2,2,0,NULL,0);
						uart3Send(2,15,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//-------------------------
					//让屁眼休息一下
					case 3:
						senceDelayToNext(&nCalca,&ppxxStep,10*DELAY_S);
						break;
					//-------------------------
					//淋水
					case 4:	
						uart3Send(2,2,10,NULL,0);
						uart3Send(2,15,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 5:
						senceDelayToNext(&nCalca,&ppxxStep,2*DELAY_S);
						break;
					case 6:
						uart3Send(2,2,0,NULL,0);
						uart3Send(2,15,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//-------------------------
					//让屁眼休息一下
					case 7:
						senceDelayToNext(&nCalca,&ppxxStep,10*DELAY_S);
						break;
					//-------------------------
					//淋水
					case 8:	
						uart3Send(2,2,10,NULL,0);
						uart3Send(2,15,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 9:
						senceDelayToNext(&nCalca,&ppxxStep,2*DELAY_S);
						break;
					case 10:
						uart3Send(2,2,0,NULL,0);
						uart3Send(2,15,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//-------------------------
					//让屁眼休息一下
					case 11:
						senceDelayToNext(&nCalca,&ppxxStep,2*DELAY_S);
						break;
					//--------------------------
					//抽屎
					case 12:	
						uart3Send(2,20,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 13:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;
					case 14:
						uart3Send(2,20,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//----------------------------
					//洗屁股
					case 15:	
						uart3Send(2,2,10,NULL,0);
						uart3Send(2,15,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 16:
						senceDelayToNext(&nCalca,&ppxxStep,5*DELAY_S);
						break;
					case 17:
						uart3Send(2,2,0,NULL,0);
						uart3Send(2,15,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//----------------------------
					//将屎抽走
					case 18:	
						uart3Send(2,20,10,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 19:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;
					case 20:
						uart3Send(2,20,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//----------------------------
					//吹干屁股
					case 21:	
						uart3Send(2,11,20,NULL,0);
						uart3Send(2,16,20,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 22:
						senceDelayToNext(&nCalca,&ppxxStep,10*DELAY_S);
						break;
					case 23:
						uart3Send(2,11,0,NULL,0);
						uart3Send(2,16,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//------------------------------
					//让屁股休息一下
					case 24:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;
					//----------------------------
					//吹干屁股
					case 25:	
						uart3Send(2,11,20,NULL,0);
						uart3Send(2,16,20,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 26:
						senceDelayToNext(&nCalca,&ppxxStep,10*DELAY_S);
						break;
					case 27:
						uart3Send(2,11,0,NULL,0);
						uart3Send(2,16,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					//------------------------------
					//让屁股休息一下
					case 28:
						senceDelayToNext(&nCalca,&ppxxStep,3*DELAY_S);
						break;
					//----------------------------
					//吹干屁股
					case 29:	
						uart3Send(2,11,20,NULL,0);
						uart3Send(2,16,20,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					case 30:
						senceDelayToNext(&nCalca,&ppxxStep,10*DELAY_S);
						break;
					case 31:
						uart3Send(2,11,0,NULL,0);
						uart3Send(2,16,0,NULL,0);
						senceNext(&nCalca,&ppxxStep);
						break;
					default: //完毕
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
