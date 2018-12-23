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
					litteAllFull();
			 break;
		 case ezhCleanSence3:
					litteQuengQueng();
			 break;
	 }
}

/*********************************************************

----运行场景----

***********************************************************/
#define QI_MIN    1400
#define QI_MAX    3900

void litteGiaoGiaoZhu(void)
{
	int n=0;
	static int nCalca=0;	
	switch(ppxxStep)
	{
		case 0:				
			//充气
			REL_1_STATE(1);for(n=0;n<100000;n++);
			REL_2_STATE(1);for(n=0;n<100000;n++);
			//真空泵开	
			RELAY11_STATE(1);for(n=0;n<100000;n++);
			//气阀方向,抽
			RELAY3_STATE(1);for(n=0;n<100000;n++);
			RELAY5_STATE(1);for(n=0;n<100000;n++);
			RELAY7_STATE(0);for(n=0;n<100000;n++);
			senceNext(&nCalca,&ppxxStep);
			break;
		case 1:
		{
			char isTrue[13]={0};
			int isAllOK=0;
			int i=0;
			isTrue[0]=(g_run.guan_qiya_percent[12]>QI_MIN);
			isTrue[1]=(g_run.guan_qiya_percent[0]>QI_MIN);
			isTrue[2]=(g_run.guan_qiya_percent[1]>QI_MIN);
			isTrue[3]=(g_run.guan_qiya_percent[2]>QI_MIN);
			isTrue[4]=(g_run.guan_qiya_percent[3]>QI_MIN);
			isTrue[5]=(g_run.guan_qiya_percent[4]>QI_MIN);
			isTrue[6]=(g_run.guan_qiya_percent[5]>QI_MIN);
			isTrue[7]=(g_run.guan_qiya_percent[6]>QI_MIN);
			isTrue[8]=(g_run.guan_qiya_percent[7]>QI_MIN);
			isTrue[9]=(g_run.guan_qiya_percent[8]>QI_MIN);
			isTrue[10]=(g_run.guan_qiya_percent[9]>QI_MIN);
			isTrue[11]=(g_run.guan_qiya_percent[10]>QI_MIN);
			isTrue[12]=(g_run.guan_qiya_percent[11]>QI_MIN);
			//
			REL_TOP_b_STATE(isTrue[0]);
			REL_L1_b_STATE(isTrue[1]);
			REL_L2_b_STATE(isTrue[2]);
			REL_L3_b_STATE(isTrue[3]);
			REL_L4_b_STATE(isTrue[4]);
			REL_L5_b_STATE(isTrue[5]);
			REL_L6_b_STATE(isTrue[6]);
			REL_R1_b_STATE(isTrue[7]);
			REL_R2_b_STATE(isTrue[8]);
			REL_R3_b_STATE(isTrue[9]);
			REL_R4_b_STATE(isTrue[10]);
			REL_R5_b_STATE(isTrue[11]);
			REL_R6_b_STATE(isTrue[12]);
			//
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }			
			if(isAllOK)
			{
				senceNext(&nCalca,&ppxxStep);
			}
		}
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
void litteAllFull(void)
{
	int n=0;
	static int nCalca=0;	
	switch(ppxxStep)
	{
		case 0:				
			//充气
			REL_1_STATE(1);for(n=0;n<100000;n++);
			REL_2_STATE(1);for(n=0;n<100000;n++);
			//真空泵开	
			RELAY11_STATE(1);for(n=0;n<100000;n++);
			//气阀方向,抽
			RELAY3_STATE(1);for(n=0;n<100000;n++);
			RELAY5_STATE(0);for(n=0;n<100000;n++);
			RELAY7_STATE(1);for(n=0;n<100000;n++);
			senceNext(&nCalca,&ppxxStep);
			break;
		case 1:
		{
			char isTrue[13]={0};
			int isAllOK=0;
			int i=0;
			isTrue[0]=(g_run.guan_qiya_percent[12]<QI_MAX);
			isTrue[1]=(g_run.guan_qiya_percent[0]<QI_MAX);
			isTrue[2]=(g_run.guan_qiya_percent[1]<QI_MAX);
			isTrue[3]=(g_run.guan_qiya_percent[2]<QI_MAX);
			isTrue[4]=(g_run.guan_qiya_percent[3]<QI_MAX);
			isTrue[5]=(g_run.guan_qiya_percent[4]<QI_MAX);
			isTrue[6]=(g_run.guan_qiya_percent[5]<QI_MAX);
			isTrue[7]=(g_run.guan_qiya_percent[6]<QI_MAX);
			isTrue[8]=(g_run.guan_qiya_percent[7]<QI_MAX);
			isTrue[9]=(g_run.guan_qiya_percent[8]<QI_MAX);
			isTrue[10]=(g_run.guan_qiya_percent[9]<QI_MAX);
			isTrue[11]=(g_run.guan_qiya_percent[10]<QI_MAX);
			isTrue[12]=(g_run.guan_qiya_percent[11]<QI_MAX);
			
			REL_TOP_a_STATE(isTrue[0]);
			REL_L1_a_STATE(isTrue[1]);
			REL_L2_a_STATE(isTrue[2]);
			REL_L3_a_STATE(isTrue[3]);
			REL_L4_a_STATE(isTrue[4]);
			REL_L5_a_STATE(isTrue[5]);
			REL_L6_a_STATE(isTrue[6]);
			REL_R1_a_STATE(isTrue[7]);
			REL_R2_a_STATE(isTrue[8]);
			REL_R3_a_STATE(isTrue[9]);
			REL_R4_a_STATE(isTrue[10]);
			REL_R5_a_STATE(isTrue[11]);
			REL_R6_a_STATE(isTrue[12]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }			
			if(isAllOK)
			{
				senceNext(&nCalca,&ppxxStep);
			}
		}
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

#define _IS_NO_ADC_DEBUG		1
void litteQuengQueng(void)
{
	static int nCalca=0;	
	int n=0;
	switch(ppxxStep)
	{
		//-------------------------------
		//充气模式
		case 0:				
			//充气
			REL_1_STATE(1);for(n=0;n<100000;n++);
			REL_2_STATE(1);for(n=0;n<100000;n++);
			//真空泵开	
			RELAY11_STATE(1);for(n=0;n<100000;n++);
			//气阀方向,抽
			RELAY3_STATE(1);for(n=0;n<100000;n++);
			RELAY5_STATE(0);for(n=0;n<100000;n++);
			RELAY7_STATE(1);for(n=0;n<100000;n++);
		
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			#endif
			senceNext(&nCalca,&ppxxStep);
			break;
		//-------------------------------
		//头涨起
		case 1:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[12]<QI_MAX);
			REL_TOP_a_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_TOP_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		//-------------------------------
		//左边涨起
		case 2:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[0]<QI_MAX);
			REL_L1_a_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L1_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 3:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[1]<QI_MAX);
			REL_L2_a_STATE(isTrue[0]);

			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L2_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 4:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[2]<QI_MAX);
			REL_L3_a_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L3_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 5:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;

			isTrue[0]=(g_run.guan_qiya_percent[3]<QI_MAX);
			REL_L4_a_STATE(isTrue[0]);

			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L4_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 6:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;

			isTrue[0]=(g_run.guan_qiya_percent[4]<QI_MAX);
			REL_L5_a_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L5_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 7:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[5]<QI_MAX);
			REL_L6_a_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L6_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		//-------------------------------
		//右边涨起
		case 8:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;

			isTrue[0]=(g_run.guan_qiya_percent[6]<QI_MAX);
			REL_R1_a_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R1_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 9:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;

			isTrue[0]=(g_run.guan_qiya_percent[7]<QI_MAX);
			REL_R2_a_STATE(isTrue[0]);

			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R2_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 10:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[8]<QI_MAX);
			REL_R3_a_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R3_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 11:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[9]<QI_MAX);
			REL_R4_a_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R4_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 12:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;

			isTrue[0]=(g_run.guan_qiya_percent[10]<QI_MAX);
			REL_R5_a_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R5_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 13:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[11]<QI_MAX);
			REL_R6_a_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R6_a_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		//---------------------------------------------------
		//抽气
		case 14:
		{
			REL_1_STATE(1);for(n=0;n<100000;n++);
			REL_2_STATE(1);for(n=0;n<100000;n++);
			//真空泵开	
			RELAY11_STATE(1);for(n=0;n<100000;n++);
			//气阀方向,抽
			RELAY3_STATE(1);for(n=0;n<100000;n++);
			RELAY5_STATE(0);for(n=0;n<100000;n++);
			RELAY7_STATE(1);for(n=0;n<100000;n++);
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			#endif
			senceNext(&nCalca,&ppxxStep);
		}
		//---------------------------------------------------
		//左边下去
		case 15:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[0]>QI_MIN);
			REL_L1_b_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L1_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 16:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[1]>QI_MIN);
			REL_L2_b_STATE(isTrue[0]);

			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L2_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 17:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[2]>QI_MIN);
			REL_L3_b_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L3_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 18:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[3]>QI_MIN);
			REL_L4_b_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L4_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 19:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[4]>QI_MIN);
			REL_L5_b_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L5_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 20:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[5]>QI_MIN);
			REL_L6_b_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_L6_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		//---------------------------------------------------
		//右边下去
		case 21:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[6]>QI_MIN);
			REL_R1_b_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R1_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 22:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[7]>QI_MIN);
			REL_R2_b_STATE(isTrue[0]);

			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R2_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 23:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[8]>QI_MIN);
			REL_R3_b_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R3_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 24:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[9]>QI_MIN);
			REL_R4_b_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R4_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 25:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[10]>QI_MIN);
			REL_R5_b_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R5_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		case 26:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[11]>QI_MIN);
			REL_R6_b_STATE(isTrue[0]);
			
			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }
			
			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_R6_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
			break;
		//---------------------------------------------------
		//头下去
		case 27:
		{
			char isTrue[1]={0};
			int isAllOK=0;
			int i=0;
			
			isTrue[0]=(g_run.guan_qiya_percent[12]>QI_MIN);
			REL_TOP_b_STATE(isTrue[0]);

			for(i=0;i<sizeof(isTrue);i++)
			{ isAllOK&=(!isTrue[i]); }

			#if _IS_NO_ADC_DEBUG 
			for(n=0;n<20000000;n++);
			isAllOK=1;
			#endif
			if(isAllOK)
			{
				REL_TOP_b_STATE(0);
				senceNext(&nCalca,&ppxxStep);
			}
		}
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

