#include "system_init.h"
#include "Stm32f1_uart1.h"
#include "Stm32f1_uart2.h"
#include "Stm32f1_uart3.h"
#include "InputDrive.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1.h"
#include "Stm32f1_ADC2.h"
#include "Motor_Diver.h"
#include "ds18b20_1.h"
#include "watchdog.h"
#include "flash_rw.h"
#include "Stm32F1_Timer2.h"
#include "Stm32F1_Timer3.h"
#include "key.h"
#include "OutputDrive.h"

//
extern u8_t kk,kk2;
extern int kk_1ms;

unsigned char g_cCleanCurrentSence=0;  

//场景时间调度
#define DEF_TIME_MS_DELAY		100

#define _unit1(x) 							RELAY1_STATE(x)			//按摩保暖电源
#define _unit2(x) 							RELAY2_STATE(x)			//左充气  常闭阀门
#define _unit3(x) 							RELAY3_STATE(x)			//左放气  常闭阀门
#define _unit4(x) 		 					RELAY4_STATE(x)			//右充气  常闭阀门
#define _unit5(x) 							RELAY5_STATE(x)			//右放气  常闭阀门
#define _unit6(x) 							RELAY6_STATE(x)			//背囊充  常闭阀门
#define _unit7(x) 							RELAY7_STATE(x)			//背囊放  常闭阀门
#define _unit8(x) 				 			RELAY8_STATE(x) 		//床垫充气  常闭阀门
#define _unit9(x) 							RELAY9_STATE(x)			//放气  常闭阀门
#define _unit10(x) 				 			RELAY10_STATE(x)		//充气关  球形阀门
#define _unit11(x)							RELAY11_STATE(x) 		//充气开  球形阀门
#define _unit12(x) 	 						RELAY12_STATE(x)		//预留

/**************/
//传感器逻辑重定义
#define cgqWST1  					SENSOR1_STATE()?1:0 //污水桶满

//--
//温度
int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0,rGasTemperature=0,rGasTemp=0;
s16 rTrueWaterTemp=0,rTrueGasTemp=0;
int isWaterTooHot=0;
int isGasTooHot=0;
int isCheckWaterSensorErr=0; //水温防错误限制
int isCheckGasSensorErr=0;//水温防错误限制
int isCheckBedCQSensorErr=0;//气压防错误限制
int isCheckDZCQSensorErr=0;	//气压防错误限制

//气压
u16_t rPressure=0,rPressureTmp=0,rPressure2=0,rPressure2Tmp=0;
u16_t rTruePressure1=0,rTruePressure2=0;

//工作时间设置
TagTimeingSetting g_tmeSetting={0};

//中断运行chart
int isCleanRuning=0;
int ppxxStep=0;

//
void senceDelay(int*nCalca,int*ppxxStep,int jmpValue,int delay_ms,int ezhCleanSencePOS);

//
void LitteSenceRun(void);
/*
	ezhCleanSence1 1号																				
	ezhCleanSence2 2号 
*/
void litteSenceRun1(void);
void litteSenceRun2(void);

//关闭所有输出
void allSenceClose()
{
	 _unit1(0); 								
	 _unit2(0); 					
	 _unit3(0); 					
	 _unit4(0); 		 					
	 _unit5(0); 						
	 _unit6(0); 							
	 _unit7(0); 							
	 _unit8(0); 				 	
	 _unit9(0); 								
	 _unit10(0); 
	 _unit11(0);
	 _unit12(0);
}

//中断场景
void allOutClose()
{	
		isCleanRuning=0;
		allSenceClose();
}
////////////////////////////////////////////////////////////////
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
			{g_cCleanCurrentSence=0;(*nCalca)=0;allOutClose();}
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
			{g_cCleanCurrentSence=0;(*nCalca)=0;allOutClose();}
			(*nCalca)++;
	}
}

void senceNext(int*nCalca,int*ppxxStep)
{
			*nCalca=0;
			(*ppxxStep)++;

}
////////////////////////////////////////////////////////////////

//显示信息指令
void aurtEventUnitShow(int i)
{
		uchar dst_buf[50]={0};
		int myDataLen=0;
		unsigned char cbuf[5]={0};
		cbuf[0]=0x03;
		cbuf[1]=i&0xff;
		cbuf[2]=(i>>8)&0xff;
		cbuf[3]=(i>>16)&0xff;
		cbuf[4]=(i>>24)&0xff;
		myDataLen = miniDataCreate(5,cbuf,dst_buf);
		STM32F1_UART1SendDataS(dst_buf,myDataLen);
}

void setFlashData()
{
	char binFlag[4]={0};
	FLASH_ReadByte(STARTADDRFLAG ,(uint8_t*)binFlag,4);
	FLASH_ReadByte(STARTADDR ,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));
	
	if(!(binFlag[0]=='a' && binFlag[1]=='b' && binFlag[2]=='c' && binFlag[3]=='d'))
	{
			binFlag[0]='a';
			binFlag[1]='b';
			binFlag[2]='c';
			binFlag[3]='d';

			//初始化FLASH内容
			g_tmeSetting.a=1;					  //
			g_tmeSetting.b=1;					  //
				
			FLASH_WriteByte(STARTADDRFLAG,(uint8_t*)binFlag,4);
			FLASH_WriteByte(STARTADDR,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));

	}
}

int main(void)
{
	EzhKeyEvent ev;
  EzhKeyState btn1;
	EzhKeyState btn2;
	EzhKeyState btn3;
	EzhKeyState btn4;
  zhSCM_initKeyState(&btn1);
	zhSCM_initKeyState(&btn2);
	zhSCM_initKeyState(&btn3);
	zhSCM_initKeyState(&btn4);
		
	STM32_Delay_init();
	STM32F1_UART1_Init(19200);  //对接MCU1
	//STM32F1_UART2_Init(230400);
	//STM32F1_UART3_Init(9600);
	
	Adc_Init();
	Adc2_Init();	
	Motor_Init();
	Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	InputDriveInit();
	OutputDriveInit();

	//-----------------------------------------
	//获取FALSH数据
	setFlashData();
  //-----------------------------------------

	//测试继电子器逻辑	
	#if 0
			allOutClose();
			RelayTest();
			allOutClose();
	#endif 
	
	//看门狗
	//watchdog_init();
	
	while(1)
	{
		//看门狗
		//watchdog_action();
		//
		//---------------------
		//按键1		左翻身
		ev=zhSCM_keyState(&btn1,TOUCHKEY_1_GPIO,TOUCHKEY_1_PIN);
    switch(ev)
    {
			case ZH_KEY_EVENT_NONE:
				break;
      case ZH_KEY_EVENT_DOWN:
				break;
      case ZH_KEY_EVENT_PRESS:
				break;
      case ZH_KEY_EVENT_UP:
			{
					ppxxStep=0;
					if(!isCleanRuning && 0==g_cCleanCurrentSence)
					{
							g_cCleanCurrentSence=ezhCleanSence1;
							isCleanRuning=1;
					}
					else
					{
							g_cCleanCurrentSence=0;
							isCleanRuning=0;
							allOutClose();
					}
			}
       break;
    }
		//按键2		右翻身
		ev=zhSCM_keyState(&btn2,TOUCHKEY_2_GPIO,TOUCHKEY_2_PIN);
    switch(ev)
    {
			case ZH_KEY_EVENT_NONE:
				break;
      case ZH_KEY_EVENT_DOWN:
        break;
      case ZH_KEY_EVENT_PRESS:
        break;
      case ZH_KEY_EVENT_UP:
			{
					ppxxStep=0;
					if(!isCleanRuning && 0==g_cCleanCurrentSence)
					{
							g_cCleanCurrentSence=ezhCleanSence2;
							isCleanRuning=1;
					}
					else
					{
							g_cCleanCurrentSence=0;
							isCleanRuning=0;
							allOutClose();
					}
			}
        break;
    }
		
		//按键3		恢复
		ev=zhSCM_keyState(&btn3,TOUCHKEY_3_GPIO,TOUCHKEY_3_PIN);
    switch(ev)
    {
			case ZH_KEY_EVENT_NONE:
				break;
      case ZH_KEY_EVENT_DOWN:
				break;
      case ZH_KEY_EVENT_PRESS:
				break;
      case ZH_KEY_EVENT_UP:
			{
					ppxxStep=0;
					if(!isCleanRuning && 0==g_cCleanCurrentSence)
					{
							g_cCleanCurrentSence=ezhCleanSence3;
							isCleanRuning=1;
					}
					else
					{
							g_cCleanCurrentSence=0;
							isCleanRuning=0;
							allOutClose();
					}
			}
        break;
    }
		//按键4		恢复
		ev=zhSCM_keyState(&btn4,TOUCHKEY_4_GPIO,TOUCHKEY_4_PIN);
    switch(ev)
    {
			case ZH_KEY_EVENT_NONE:
				break;
      case ZH_KEY_EVENT_DOWN:
				break;
      case ZH_KEY_EVENT_PRESS:
				break;
      case ZH_KEY_EVENT_UP:
			{
					ppxxStep=0;
					if(!isCleanRuning && 0==g_cCleanCurrentSence)
					{
							g_cCleanCurrentSence=ezhCleanSence4;
							isCleanRuning=1;
					}
					else
					{
							g_cCleanCurrentSence=0;
							isCleanRuning=0;
							allOutClose();
					}
			}
        break;
    }

	//------------------------------------------------------------------
	/*			if( 0==g_cCleanCurrentSence )
				{
						rPressureTmp = Get_Adc_Average(10);
						ntmp=rPressureTmp-rPressure;
						if(ntmp<60 && ntmp>-60) //限制突变幅度
						{
							if(rPressureTmp<g_tmeSetting.crotchPressure*100)
							{
								if(g_cCleanCurrentSence==0)
								{		udoKuZiCongQi(1);}
							}
							else
							{
								if(g_cCleanCurrentSence==0)
								{		udoKuZiCongQi(0);}
							}
							rTruePressure1=rPressureTmp;
							isCheckDZCQSensorErr=0;
						}
						else
						{
							isCheckDZCQSensorErr++;						
							if(isCheckDZCQSensorErr>10) //传感数据有毛病关掉继电器
							{
								if(g_cCleanCurrentSence==0)
								{	udoKuZiCongQi(0);}
							}
						}
						rPressure=rPressureTmp;
				}*/
				
				//------------------------------------------------------------------
				//床垫气压,功能已经废掉
				/*rPressure2Tmp= Get_Adc2_Average(10);
				ntmp=rPressure2Tmp-rPressure2;
				if(ntmp<60 && ntmp>-60) //限制突变幅度
				{
					if(rPressure2Tmp<g_tmeSetting.bedPressure*100)
					{
						if(g_cCleanCurrentSence==0)
						{
							udoBedCongQi(1);
						}
					}
					else
					{
						if(g_cCleanCurrentSence==0)
						{	udoBedCongQi(0);}
					}
					rTruePressure2=rPressure2Tmp;
					isCheckBedCQSensorErr=0;
				}
				else
				{
					isCheckBedCQSensorErr++;						
					if(isCheckBedCQSensorErr>10) //传感数据毛病太多关等继电器
					{
						if(g_cCleanCurrentSence==0)
						{	udoBedCongQi(0);}
					}
				}
				rPressure2=rPressure2Tmp;*/

		//------------------------------------------------------------------
		//场景功能
		if(kk_1ms)
		{
					LitteSenceRun();
					kk_1ms=0;
		}
	}
}

void LitteSenceRun()
{
		if(ezhCleanSence1==(g_cCleanCurrentSence))
		{
				litteSenceRun1();
		}
		else if(ezhCleanSence2==(g_cCleanCurrentSence))
		{			
				litteSenceRun2();
		}
		else
		{
				//没有场景
				g_cCleanCurrentSence=0;
		}
}


/*********************************************************

----运行场景----

***********************************************************/
void litteSenceRun1()
{					
					static int nCalca=0;	
					switch(ppxxStep)
					{
						case 0:				
							allSenceClose();
							g_cCleanCurrentSence=ezhCleanSence1;
							break;
						case 1:							
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*5);
							break;
						default: //完毕
							allOutClose();
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
}

void litteSenceRun2()
{				
				static int nCalca=0;
				switch(ppxxStep)
				{
					case 0:				
						allSenceClose();
						g_cCleanCurrentSence=ezhCleanSence2;
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
						break;
					default: //完毕
						allOutClose();
						g_cCleanCurrentSence=0;  		//场景复位
						ppxxStep=0;
						break;
				}
}


void litteSenceRun3()
{				
				static int nCalca=0;
				switch(ppxxStep)
				{
					case 0:				
						allSenceClose();
						g_cCleanCurrentSence=ezhCleanSence2;
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
						break;
					default: //完毕
						allOutClose();
						g_cCleanCurrentSence=0;  		//场景复位
						ppxxStep=0;
						break;
				}
}

void litteSenceRun4()
{				
				static int nCalca=0;
				switch(ppxxStep)
				{
					case 0:				
						allSenceClose();
						g_cCleanCurrentSence=ezhCleanSence2;
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
						break;
					default: //完毕
						allOutClose();
						g_cCleanCurrentSence=0;  		//场景复位
						ppxxStep=0;
						break;
				}
}
