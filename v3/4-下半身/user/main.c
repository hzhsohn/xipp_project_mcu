#include "system_init.h"
#include "Stm32f1_uart1.h"
#include "Stm32f1_uart2.h"
#include "Stm32f1_uart3.h"
#include "InputDrive.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1.h"
#include "Stm32f1_ADC2.h"
#include "ds18b20_1.h"
#include "watchdog.h"
#include "flash_rw.h"
#include "Stm32F1_Timer2.h"
#include "Stm32F1_Timer3.h"
#include "key.h"
#include "OutputDrive.h"

/**************/
//传感器逻辑重定义
#define cgqWaterHeight  					SENSOR1_STATE()?1:0 //
#define cgqWaterLow  				SENSOR2_STATE()?0:1 //清水低

//--
//水温度
int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0;
s16 rTrueWaterTemp=0;
int isWaterTooHot=0;
int isCheckWaterSensorErr=0; //水温防错误限制

//
void delay_s(int n)
{
		int i=0;
		for(i=0;i<n*10;i++)
		{ STM32_Delay_ms(100); }
}

////////////////////////////////////////////////////////////////
void setFlashData()
{
	char binFlag[4]={0};
	FLASH_ReadByte(STARTADDRFLAG ,(uint8_t*)binFlag,4);
	
	if(!(binFlag[0]=='a' && binFlag[1]=='b' && binFlag[2]=='c' && binFlag[3]=='d'))
	{
			binFlag[0]='a';
			binFlag[1]='b';
			binFlag[2]='c';
			binFlag[3]='d';

			FLASH_WriteByte(STARTADDRFLAG,(uint8_t*)binFlag,4);
	}
}
int main(void)
{
	EzhKeyEvent ev;
  EzhKeyState btn1;
	EzhKeyState btn2;
	EzhKeyState btn3;
	EzhKeyState btn4;
	EzhKeyState btn5;
	EzhKeyState btn6;
	EzhKeyState btn7;
	EzhKeyState btn8;
  zhSCM_initKeyState(&btn1);
	zhSCM_initKeyState(&btn2);
	zhSCM_initKeyState(&btn3);
	zhSCM_initKeyState(&btn4);
	zhSCM_initKeyState(&btn5);
	zhSCM_initKeyState(&btn6);
	zhSCM_initKeyState(&btn7);
	zhSCM_initKeyState(&btn8);
		
	STM32_Delay_init();
	STM32F1_UART1_Init(115200);
	STM32F1_UART2_Init(19200);
	STM32F1_UART3_Init(230400);
	
	DS18B20_Init();
	//DS18B20_Init1();
	//Adc_Init();
	//Adc2_Init();
	Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	InputDriveInit();
	OutputDriveInit();
	zhSCM_GPIOConfig();
	
	//-----------------------------------------
	//获取FALSH数据
	setFlashData();
  //-----------------------------------------

	//
	 _unit1(1); 								
	 _unit2(1); 					
	 _unit3(1); 					
	 _unit4(1); 		 					
	 _unit5(1); 						
	 _unit6(1); 							
	 _unit7(1); 							
	 _unit8(1); 				 	
	 _unit9(1); 								
	 _unit10(1); 				 		
	 _unit11(1);					
	 _unit12(1); 	 						
	 _unit13(1);
	 _unit14(1); 
	 _unit15(1); 
	
	//看门狗
	//watchdog_init();
	
	while(1)
	{
				//看门狗
				//watchdog_action();
				//
				//---------------------
				//按键1		护卫键
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
							
					}
					 break;
				}
				//按键2		冲洗键
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
							
					}
						break;
				}
				//按键3		烘干键
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
							
					}
						break;
				}
				//按键4		除菌键
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
									aurtEventBtn(4);
									g_cCleanCurrentSence=ezhCleanSence6;
									isCleanRuning=1;
							}
							else
							{
									g_cCleanCurrentSence=0;
									isCleanRuning=0;
									allOutClose();
									aurtEventBtn(0);
							}
					}
						break;
				}
				
				//按键5		按摩键
				ev=zhSCM_keyState(&btn5,TOUCHKEY_5_GPIO,TOUCHKEY_5_PIN);
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
								aurtEventBtn(5);
								g_cCleanCurrentSence=ezhCleanSence7;
								isCleanRuning=1;
								anmiCurrentState=!anmiCurrentState;
								ppxxStep=0; //复位场景
					}
						break;
				}
				//按键6		保暖键
				ev=zhSCM_keyState(&btn6,TOUCHKEY_6_GPIO,TOUCHKEY_6_PIN);
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
								aurtEventBtn(6);
								g_cCleanCurrentSence=ezhCleanSence8;
								isCleanRuning=1;
								baonianCurrentState=!baonianCurrentState;
								ppxxStep=0; //复位场景
					}
						break;
				}
				
				//按键7		设置链
				ev=zhSCM_keyState(&btn7,TOUCHKEY_7_GPIO,TOUCHKEY_7_PIN);
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
							aurtEventBtn(7);
					}
						break;
				}
				//按键8		待机开关
				ev=zhSCM_keyState(&btn8,TOUCHKEY_8_GPIO,TOUCHKEY_8_PIN);
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
							aurtEventBtn(8);
					}
						break;
				}

				//------------------------------------------------------------------
				//检测有无尿拉下来		
				//if(rTrueWaterTemp>=g_tmeSetting.waterTemperature*10) //限制如果水温不够不操作
				{
							if(dxbXuXu)
							{
								rXuxuDD++;
								if(rXuxuDD>2000)
								{
										if(0==g_cCleanCurrentSence && g_isAutomation)
										{
											aurtEventBtn(0x50);
											ppxxStep=0;
											g_cCleanCurrentSence=ezhCleanSence1;
											isCleanRuning=1;
										}
										rXuxuDD=0;
								}
							}
							else
							{
									rXuxuDD=0;
							}
				}
				//------------------------------------------------------------------
				//检测有没有屎掉下来
				//if(rTrueWaterTemp>=g_tmeSetting.waterTemperature*10)  //限制如果水温不够不操作
				{
							if(dxbPooPoo)
							{
								rPoopoDD++;
								if(rPoopoDD>2000)
								{
										if(0==g_cCleanCurrentSence && g_isAutomation)//场景执行中
										{
												aurtEventBtn(0x51);
												ppxxStep=0;
												g_cCleanCurrentSence=ezhCleanSence2;
												isCleanRuning=1;
										}
										rPoopoDD=0;
								}
							}
							else
							{
								rPoopoDD=0;
							}
				}

				//------------------------------------------------------------------
				//水温加热
				rWaterTemp=DS18B20_Get_Temp();
				if(rWaterTemp<2000 && rWaterTemp> -200) //限制位
				{
					ntmp=rWaterTemp-rWaterTemperature;
					if(ntmp<20 && ntmp>-20)	//限制突变幅度
					{
							isWaterTooHot=0;							
							if(rWaterTemp > 60*10) //加热器有问题了吧,太高了就是加热器有问题了.
							{
									//水太热了.发到串口告诉上位机端,通知护士小妹妹,机器故障了
									isWaterTooHot=1;
							}
							rTrueWaterTemp=rWaterTemp;
							isCheckWaterSensorErr=0;
					}
					rWaterTemperature=rWaterTemp;
				}
				else
				{
						isCheckWaterSensorErr++;						
						if(isCheckWaterSensorErr>10) //传感数据毛病太多关掉加热继电器
						{
							//传感器有毛病了.关掉继电器
							if(g_cCleanCurrentSence==0)
							{
										_unit13(0);
							}
						}
				}
	}
}

void LitteSenceRun()
{
		if(ezhCleanSence1==(g_cCleanCurrentSence)) //尿
		{
				litteSenceRunXuXu();
		}
		else if(ezhCleanSence2==(g_cCleanCurrentSence)) //屎
		{			
				litteSenceRunPooPoo();
		}
		else if(ezhCleanSence3==(g_cCleanCurrentSence))
		{
				litteSenceRunHuWai();
		}
		else if(ezhCleanSence4==(g_cCleanCurrentSence))
		{
				litteSenceRunChongXi();
		}
		else if(ezhCleanSence5==(g_cCleanCurrentSence))
		{
				litteSenceRunHongGan();
		}
		else if(ezhCleanSence6==(g_cCleanCurrentSence))
		{
				litteSenceRunChuQun();
		}
		else if(ezhCleanSence7==(g_cCleanCurrentSence))
		{
				litteSenceRunAnMo();
		}
		else if(ezhCleanSence8==(g_cCleanCurrentSence))
		{
				litteSenceRunBaoNang();
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
void litteSenceRunXuXu()
{					
					static int nCalca=0;	
					switch(ppxxStep)
					{
						case 0:				
							allSenceClose();
							//aurtEventUnitSence(ezhCleanSence1,1);
							g_cCleanCurrentSence=ezhCleanSence1;
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*60);
							break;
						case 2:
							_unit4(1);
							_unit11(1);
							_unit5(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 3:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
							break;
						case 4:
							_unit5(0);
							_unit6(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 5:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*4);
							break;
						case 6:
							_unit6(0);
							_unit11(0);
							_unit15(1);
							_unit9(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 7:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*6);
							break;
						case 8:		
							_unit15(0);
							_unit9(0);
							_unit11(1);
							_unit6(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 9:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*6);
							break;
						case 10:		
							_unit11(0);
							_unit6(0);
							_unit2(1);
							_unit12(1);
							_unit10(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 11:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50);
							break;
						case 12:		
							_unit2(0);
							_unit12(0);
							_unit10(0);
							_unit4(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 13:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*2);
							break;
						case 14:		
							_unit3(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 15:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15);
							break;
						case 16:		
							_unit3(0);
							senceNext(&nCalca,&ppxxStep);
							break;
									
						default: //完毕
							aurtEventUnitSence(ezhCleanSence1,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
}

void litteSenceRunPooPoo()
{				
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:				
							allSenceClose();
							//aurtEventUnitSence(ezhCleanSence2,1);
							g_cCleanCurrentSence=ezhCleanSence2;
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*30);
							break;
						case 2:
							_unit4(1);
							_unit11(1);
							_unit5(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 3:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
							break;
						case 4:
							_unit5(0);
							_unit6(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 5:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*4);
							break;
						case 6:
							_unit6(0);
							_unit11(0);
							_unit15(1);
							_unit9(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 7:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*6);
							break;
						case 8:		
							_unit15(0);
							_unit9(0);
							_unit11(1);
							_unit6(1);
							_unit7(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 9:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*6);
							break;
						case 10:		
							_unit11(0);
							_unit6(0);
							_unit7(0);
							_unit2(1);
							_unit12(1);
							_unit10(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 11:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50);
							break;
						case 12:		
							_unit2(0);
							_unit12(0);
							_unit10(0);
							_unit4(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 13:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*2);
							break;
						case 14:		
							_unit3(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 15:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15);
							break;
						case 16:		
							_unit3(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						
						default: //完毕
							aurtEventUnitSence(ezhCleanSence2,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
}

void litteSenceRunHuWai(void)
{		
		/*		static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:				
							allSenceClose();
							aurtEventUnitSence(ezhCleanSence3,1);
							g_cCleanCurrentSence=ezhCleanSence3;
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10);
							break;
						default: //完毕
							aurtEventUnitSence(ezhCleanSence3,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}*/
}
void litteSenceRunChongXi(void)
{
		/*		static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:							
							allSenceClose();				
							aurtEventUnitSence(ezhCleanSence4,1);
							g_cCleanCurrentSence=ezhCleanSence4;
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:	
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10);
							break;						
						default: //完毕
							aurtEventUnitSence(ezhCleanSence4,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}*/
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:				
							allSenceClose();
							//aurtEventUnitSence(ezhCleanSence4,1);
							g_cCleanCurrentSence=ezhCleanSence4;
							senceNext(&nCalca,&ppxxStep);
							break;

						case 1:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*1);
							break;
						case 2:
							_unit4(1);
							_unit11(1);
							_unit5(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 3:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
							break;
						case 4:
							_unit5(0);
							_unit6(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 5:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*4);
							break;
						case 6:
							_unit6(0);
							_unit11(0);
							_unit15(1);
							_unit9(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 7:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*6);
							break;
						case 8:		
							_unit15(0);
							_unit9(0);
							_unit11(1);
							_unit6(1);
							_unit7(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 9:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*6);
							break;
						case 10:		
							_unit11(0);
							_unit6(0);
							_unit7(0);
							_unit2(1);
							_unit12(1);
							_unit10(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 11:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50);
							break;
						case 12:		
							_unit2(0);
							_unit12(0);
							_unit10(0);
							_unit4(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 13:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*2);
							break;
						case 14:		
							_unit3(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 15:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15);
							break;
						case 16:		
							_unit3(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						
						default: //完毕
							aurtEventUnitSence(ezhCleanSence2,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
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
							allSenceClose();
							aurtEventUnitSence(ezhCleanSence5,1);
							g_cCleanCurrentSence=ezhCleanSence5;
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*1);
							break;
						case 2:
							_unit2(1);
							_unit12(1);
							_unit10(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 3:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50);
							break;
						case 4:
							_unit2(0);
							_unit12(0);
							_unit10(0);
							_unit1(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 5:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15);
							break;
						case 6:
							_unit1(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						
						default: //完毕
							aurtEventUnitSence(ezhCleanSence5,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
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
							allSenceClose();						
							aurtEventUnitSence(ezhCleanSence6,1);
							g_cCleanCurrentSence=ezhCleanSence6;
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*1);
							break;
						case 2:
							_unit12(1);
							_unit8(1);
							_unit2(1);
							_unit10(1);
							_unit4(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 3:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*5);
							break;
						case 4:
							_unit15(1);
							_unit9(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 5:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
							break;
						case 6:
							_unit15(0);
							_unit9(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 7:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50);
							break;
						case 8:
							_unit15(1);
							_unit9(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 9:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
							break;
						case 10:
							_unit15(0);
							_unit9(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 11:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50);
							break;
						case 12:
							_unit15(1);
							_unit9(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 13:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
							break;
						case 14:
							_unit15(0);
							_unit9(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 15:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50);
							break;
						case 16:
							_unit2(0);
							_unit4(0);
							_unit3(1);
							_unit1(1);
							_unit12(0);
							_unit8(0);
							_unit10(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 17:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15);
							break;
						case 18:
							_unit3(0);
							_unit1(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						
						default: //完毕
							aurtEventUnitSence(ezhCleanSence6,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
}

/********************************
//按摩
*********************************/
void litteSenceRunAnMo(void)
{

}

/********************************
//保暖
*********************************/
void litteSenceRunBaoNang(void)
{
	
}

