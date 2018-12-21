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
//
extern int jaopan;

//是否自动化操作
unsigned char g_isAutomation=1;

unsigned char g_cCleanCurrentSence=0;  

//场景时间调度
#define DEF_TIME_MS_DELAY		100

/**************/
//继电器逻辑重定义
int isOpenDry=0;


/**************/
//传感器逻辑重定义
#define cgqSewageHeight  					SENSOR1_STATE()?1:0 //净化液低
#define cgqCleanWaterLow  				SENSOR2_STATE()?0:1 //清水低
#define cgqSewageSuitable  				SENSOR3_STATE()?1:0 //污水到位

//大小便检测
#define dxbPooPoo  				SENSOR4_STATE()?0:1    //屎
#define dxbXuXu	  				SENSOR5_STATE()?0:1    //尿

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
//屎屎尿尿的防抖动
int rPoopoDD=0;
int rXuxuDD=0;
int pdxbPooPoo;
int pdxbXuXu;
//
int isTextPOPO=0;
int isTextXUXU=0;

//角度 
extern unsigned char jiaodu[2];
//脉博
extern unsigned char cHeartJump;
//净化液低
char bSewageHeight=0;
//清水太少
char bCleanWaterLow=0;
//污水到位
char bSewageSuitable=0;
//工作时间设置
TagTimeingSetting g_tmeSetting={0};


//中断运行chart
int isCleanRuning=0;
int ppxxStep=0;

//摄像头电机
int xiiiLimit=90000;
int xiii=1000000;
int xiii2=1000000;
int Motor1_do_step=0;
int Motor2_do_step=0;
int motor1_p_or_n=0;
int motor2_p_or_n=0;
int monLimitState1L;
int monLimitState1R;
int monLimitState2L;
int monLimitState2R;


//按摩状态
static int anmiCurrentState=0;
static int baonianCurrentState=0;
//
void senceDelay(int*nCalca,int*ppxxStep,int jmpValue,int delay_ms,int ezhCleanSencePOS);

//
void LitteSenceRun(void);
/*
	ezhCleanSence1自动化小便																					
	ezhCleanSence2自动化大便 
	ezhCleanSence3护卫
	ezhCleanSence4冲洗
	ezhCleanSence5烘干
	ezhCleanSence6除菌
	ezhCleanSence7按摩
	ezhCleanSence8保暖
*/
void litteSenceRunPooPoo(void);
void litteSenceRunXuXu(void);
void litteSenceRunHuWai(void);
void litteSenceRunChongXi(void);
void litteSenceRunHongGan(void);
void litteSenceRunChuQun(void);
void litteSenceRunAnMo(void);
void litteSenceRunBaoNang(void);

//关闭所有输出
void allSenceClose()
{
		isOpenDry=0;
		jaopan=0;
		//
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
	 _unit13(0);
	 _unit14(0); 
	 _unit15(0); 	
}

//中断场景
void allOutClose()
{	
		isCleanRuning=0;
		allSenceClose();
		isTextPOPO=0;
		isTextXUXU=0;
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

//提交当前状态
void aurtEventStatus()
{
		uchar dst_buf[50]={0};
		unsigned char cbuf[23]={0};
		int myDataLen=0;
		//
		cbuf[0]=0;
		
		cbuf[1]=g_isAutomation;
		cbuf[2]=g_cCleanCurrentSence;
				
		cbuf[3]=bSewageHeight;//传感器污水满
		cbuf[4]=bCleanWaterLow;//传感器清水太小
		cbuf[5]=bSewageSuitable;//传感器污水管未安装到位
		
		cbuf[6]=cHeartJump; //脉博
		cbuf[7]=0;
		
		cbuf[8]=rTrueWaterTemp&0xff; //水温度
		cbuf[9]=rTrueWaterTemp>>8;
		
		cbuf[10]=rTrueGasTemp&0xff; //气温度
		cbuf[11]=rTrueGasTemp>>8;
		
		cbuf[12]=rTruePressure1&0xff; //裤档气压
		cbuf[13]=rTruePressure1>>8;
		
		cbuf[14]=rTruePressure2&0xff; //床垫气压
		cbuf[15]=rTruePressure2>>8;
		
		cbuf[16]=isWaterTooHot;//如果为1就是有问题,意思就是"加热功能不知道哪里有问题.."
		cbuf[17]=isGasTooHot;
		
		myDataLen = miniDataCreate(20,cbuf,dst_buf);
		STM32F1_UART1SendDataS(dst_buf,myDataLen);
		
		//
		cHeartJump=0;
}

void aurtEventBtn(int i)
{
		uchar dst_buf[10]={0};
		int myDataLen=0;
		unsigned char cbuf[5]={0};
		cbuf[0]=0x01;
		cbuf[1]=i;
		myDataLen = miniDataCreate(2,cbuf,dst_buf);
		STM32F1_UART1SendDataS(dst_buf,myDataLen);
}

void aurtEventUnitSence(EzhCleanSence i,int isEnable)
{
		/*
			1//继电器抽吸启用
			2//继电器烘干启用
			3//继电器除菌启用
			4//继电器大便启用
			5//继电器大便冲洗启用
			6//继电器小便启用
			7//继电器小便冲洗启用
		*/
		uchar dst_buf[50]={0};
		int myDataLen=0;
		unsigned char cbuf[5]={0};
		cbuf[0]=0x02;
		cbuf[1]=i;
		cbuf[2]=isEnable;
		myDataLen = miniDataCreate(3,cbuf,dst_buf);
		STM32F1_UART1SendDataS(dst_buf,myDataLen);
}

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
			g_tmeSetting.pooDelay=1;					  //拉屎后多少秒启动 ,单位分钟
			g_tmeSetting.xuxuDelay=10;				  //拉屎后多少秒启动 ,单位秒
			g_tmeSetting.pooFlush=30;					  //屎屎冲洗  ,	单位秒
			g_tmeSetting.xuxuFlush=10;				  //尿尿冲洗  	单位 秒
			g_tmeSetting.pooDry=2;      		  	//屎屎烘干时间 单位 分钟
			g_tmeSetting.xuxuDry=1;					  	//尿尿烘干时间 单位 分钟
			g_tmeSetting.pooSterilize=10;			  //屎屎消毒时间 单位 秒
			g_tmeSetting.xuxuSterilize=10;		  //尿尿消毒时间 单位 秒
			g_tmeSetting.crotchPressure=13;			//裤档气压 单位 100电压变数
			g_tmeSetting.bedPressure=13;   			//床垫的气压  单位 100电压变数
			g_tmeSetting.waterTemperature=38;		//最低水温   			单位摄氏度
			g_tmeSetting.airTemperature=50;  		//最低烘干温度   	单位摄氏度
			g_tmeSetting.mpuLeft=30;  					//
			g_tmeSetting.mpuRight=30;  					//
				
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
	DS18B20_Init1();
	Adc_Init();
	Adc2_Init();	
	Motor_Init();
	Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	InputDriveInit();
	OutputDriveInit();
	zhSCM_GPIOConfig();

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
		pdxbPooPoo=dxbPooPoo;
		pdxbXuXu=dxbXuXu;
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
					ppxxStep=0;
					if(!isCleanRuning && 0==g_cCleanCurrentSence)
					{
							aurtEventBtn(1);
							//g_cCleanCurrentSence=ezhCleanSence3;
										g_cCleanCurrentSence=ezhCleanSence1;
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
					ppxxStep=0;
					if(!isCleanRuning && 0==g_cCleanCurrentSence)
					{
							aurtEventBtn(2);
							//g_cCleanCurrentSence=ezhCleanSence4;
										g_cCleanCurrentSence=ezhCleanSence2;
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
					ppxxStep=0;
					if(!isCleanRuning && 0==g_cCleanCurrentSence)
					{
							aurtEventBtn(3);
							g_cCleanCurrentSence=ezhCleanSence5;
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

		//---------------------//
		if(kk>=10 && xiii>=xiiiLimit && xiii2>=xiiiLimit) //限制0.1秒执行一次,且步进电机不能有动作
		{
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
								else if(rWaterTemp<g_tmeSetting.waterTemperature*10 && 0==bCleanWaterLow) //默认小于40度就加热
								{
										_unit13(1);
								}
								else
								{
										_unit13(0);
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

					//-------------------------------------------------------------------
					//空气加热,实时条件限制
					rGasTemp=DS18B20_Get_Temp1(); 
					if(rGasTemp<2000 && rGasTemp> -200) //限制位
					{
						ntmp=rGasTemp-rGasTemperature;
						if(ntmp<20 && ntmp>-20) //限制突变幅度
						{
								isGasTooHot=0;							
								if(rGasTemp > 60*10) //加热器有问题了吧,太高了就是加热器有问题了.
								{
									//气温太热了.发到串口告诉上位机端,通知护士小妹妹,机器故障了
									isGasTooHot=1;
								}
								
								if(isOpenDry && rGasTemp<g_tmeSetting.airTemperature*10 ) //50度且烘开关的时候才处理
								{
									 _unit12(1);  //气加热单元
								}
								else
								{
									 _unit12(0);	//气加热单元
								}
								rTrueGasTemp=rGasTemp;
								isCheckGasSensorErr=0;
						}
						rGasTemperature=rGasTemp;
					}
					else
					{
						isCheckGasSensorErr++;						
						if(isCheckGasSensorErr>10) //传感数据有毛病关掉加热继电器
						{
								//传感器有毛病了.关掉继电器
								_unit12(0); //气加热单元
						}
					}

					//------------------------------------------------------------------
					//净化液低
					if(cgqSewageHeight)
					{
							bSewageHeight=1;
					}
					else
					{
							bSewageHeight=0;
					}

					//------------------------------------------------------------------
					//清水太少
					if(cgqCleanWaterLow)
					{
							bCleanWaterLow=1;
					}
					else
					{
							bCleanWaterLow=0;
					}

					//------------------------------------------------------------------
					//污水不到位
					if(cgqSewageSuitable)
					{
							bSewageSuitable=1;
					}
					else
					{
							bSewageSuitable=0;
					}
					//---------------------
					kk=0;
		}
		
		//------------------------------------------------------------------
		//冲屎洗尿功能
		if(kk_1ms)
		{
					LitteSenceRun();
					kk_1ms=0;			
					//
					if(g_cCleanCurrentSence)
					{LED1_RE;LED2_RE;LED3_RE;}
					else 
					{LED1_ON;LED2_ON;LED3_ON;}
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
							aurtEventUnitSence(ezhCleanSence1,1);
							g_cCleanCurrentSence=ezhCleanSence1;
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*5);
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
							aurtEventUnitSence(ezhCleanSence2,1);
							g_cCleanCurrentSence=ezhCleanSence2;
							_unit4(1);
							_unit11(1);
							_unit5(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
							break;
						case 2:
							_unit5(0);
							_unit6(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 3:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*4);
							break;
						case 4:
							_unit6(0);
							_unit11(0);
							_unit15(1);
							_unit9(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 5:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*6);
							break;
						case 6:		
							_unit15(0);
							_unit9(0);
							_unit11(1);
							_unit6(1);
							_unit7(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 7:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*6);
							break;
						case 8:		
							_unit11(0);
							_unit6(0);
							_unit7(0);
							_unit2(1);
							_unit12(1);
							_unit10(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 9:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50);
							break;
						case 10:		
							_unit2(0);
							_unit12(0);
							_unit10(0);
							_unit4(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 11:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*2);
							break;
						case 12:		
							_unit3(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 13:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15);
							break;
						case 14:		
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
				static int nCalca=0;
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
					}
}
void litteSenceRunChongXi(void)
{
				static int nCalca=0;
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
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
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

