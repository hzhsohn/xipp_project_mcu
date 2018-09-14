#include "system_init.h"
#include "BeeSpeaker_Diver.h"
#include "TouchKey_Diver.h"
#include "Stm32f1_uart1_diver.h"
#include "Stm32f1_uart2_diver.h"
#include "Relay_Diver.h"
#include "Stm32f1_uart3_diver.h"
#include "Sensor.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1_Diver.h"
#include "Stm32f1_ADC2_Diver.h"
#include "Motor_Diver.h"
#include "ds18b20_1.h"
#include "SenceAct.h"
#include "watchdog.h"
#include "flash_rw.h"

//
extern u8_t kk,kk2;
extern int kk_1ms;
//
extern Func_Staus bButton1;
extern Func_Staus bButton2;
extern Func_Staus bButton3;
extern Func_Staus bButton4;
extern Func_Staus bButton5;
extern Func_Staus bButton6;
extern Func_Staus bButton7;
extern Func_Staus bButton8;

extern int jaopan;

//
extern int g_nMPU_DO;
//是否自动化操作
unsigned char g_isAutomation=1;

unsigned char g_cCleanCurrentSence=0;  

//场景时间调度
#define DEF_TIME_MS_DELAY		50

/**************/
//继电器逻辑重定义
int isOpenDry=0;

#define _unit1(x) 							RELAY7_STATE(x)		//小便转换
#define _unit2(x) 							RELAY6_STATE(x)		//大便转换
#define _unit3(x) 							RELAY11_STATE(x)	//床气转换
#define _unit4(x) 		 					RELAY12_STATE(x)	//裤子气转机
#define _unit5(x) 							RELAY10_STATE(x)	//加热气转换
#define _unit6(x) 							RELAY1_STATE(x)		//气加热
#define _unit7(x) 							RELAY9_STATE(x)		//抽吸机
#define _unit8(x) 				 			RELAY3_STATE(x) 	//抽水机
#define _unit9(x) 							RELAY2_STATE(x)		//杀菌发生器
#define _unit10(x) 				 			RELAY8_STATE(x)		//吹气
#define _unit11(x)							RELAY13_STATE(x) 	//水加热
#define _unit12(x) 	 						RELAY4_STATE(x)		//净化机
#define _unit13(x) 							RELAY5_STATE(x)		//杀菌气转换

//
#define udoDry(x)						 			_unit5(x);_unit6(x);_unit10(x);isOpenDry=x		//烘干程序
#define udoSterilization(x) 			_unit5(x);_unit9(x);_unit10(x);_unit13(x)			//杀菌
#define udoWaterHeating(x) 				_unit11(x)																		//水加热程序
#define udoXuXuFlush(x) 					_unit1(x);_unit7(x);_unit8(x)									//小便冲洗
#define udoPoPoFlush(x) 					_unit2(x);_unit7(x);_unit8(x)									//大便冲洗
#define udoKuZiCongQi(x) 					_unit4(x);_unit10(x)													//裤子充气
#define udoBedCongQi(x) 	 				_unit3(x);_unit10(x)													//床垫充气
#define udoDeodorization(x) 			_unit7(x);_unit12(x)													//除臭
#define udoKuZiHuanQi(x) 				 	_unit5(x);_unit10(x) 													//裤子换气
#define udoXuPooCollect(x) 				_unit7(x);_unit12(x)													//屎屎尿尿收集
#define udoJiaoPan(x)             jaopan=x																			//搅伴

/**************/
//传感器逻辑重定义
#define cgqSewageHeight  					SENSOR1_STATE()?1:0 //污水满
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

//角度 
extern unsigned char jiaodu[2];
//脉博
unsigned char cHeartJump=0;
//污水满
char bSewageHeight=0;
//清水太少
char bCleanWaterLow=0;
//污水到位
char bSewageSuitable=0;
//时间调度值
extern TagTimeingSetting g_tmeSetting;

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
//
void senceDelay(int*nCalca,int*ppxxStep,int delay_ms,int ezhCleanSencePOS);
////////////////////////////////////////////////////////////////

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
void litteSenceRunA(void);
void litteSenceRunB(void);
void litteSenceRunC(void);


void allOutClose()
{	
	 isCleanRuning=0;
	 isOpenDry=0;
	 _unit1(0); 									//小便转换
	 _unit2(0); 									//大便转换
	 _unit3(0); 									//床气转换
	 _unit4(0); 		 							//裤子气转机
	 _unit5(0); 									//加热气转换
	 _unit6(0); 									//气加热
	 _unit7(0); 									//抽吸机
	 _unit8(0); 				 			 		//抽水机
	 _unit9(0); 									//杀菌发生器
	 _unit10(0); 				 					//吹气
	 _unit11(0);							 		//水加热
	 _unit12(0); 	 								//净化机
	 _unit13(0); 									//杀菌气转换
		jaopan=0;
}
////////////////////////////////////////////////////////////////
//场景延时
void senceDelay(int*nCalca,int*ppxxStep,int delay_ms,int ezhCleanSencePOS)
{
	if((*nCalca) > delay_ms) 
	{
			*nCalca=0;
			(*ppxxStep)++; g_cCleanCurrentSence=ezhCleanSencePOS | (*ppxxStep);
	}
	else
	{
			if(0==isCleanRuning)//中断
			{g_cCleanCurrentSence=0;(*nCalca)=0;allOutClose();}
			(*nCalca)++;
	}
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


char binFlag[4]={0};
int main(void)
{
	Code_Init();
	
	//测试继电子器逻辑	
	#if 0
			allOutClose();
			RelayTest();
			allOutClose();
	#endif 
	
	//看门狗
	//watchdog_init();
	allOutClose();
	
	STM32F1_UART3SendDataS("123",3);
	
	//-------------------------------
	//startup system delay-----------
	STM32_Delay_ms(10000);
	//
	LED1_ON;LED2_ON;LED3_ON;
		
	//获取数据
	FLASH_ReadByte(STARTADDRFLAG ,(uint8_t*)binFlag,4);
	FLASH_ReadByte(STARTADDR ,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));
	
if(!(binFlag[0]=='a' && binFlag[1]=='b' && binFlag[2]=='c' && binFlag[3]=='d'))
{
		binFlag[0]='a';
		binFlag[1]='b';
		binFlag[2]='c';
		binFlag[3]='d';

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
		g_tmeSetting.mpuLeft=30;  					//??????  ????
		g_tmeSetting.mpuRight=30;  					//??????  ????
			
		FLASH_WriteByte(STARTADDRFLAG,(uint8_t*)binFlag,4);
		FLASH_WriteByte(STARTADDR,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));

}
	//-------------------
	while(1)
	{
		pdxbPooPoo=dxbPooPoo;
		pdxbXuXu=dxbXuXu;
		//看门狗
		//watchdog_action();
		//
		TouchKey_Scan();
		//---------------------
		//按键
		//1护卫键
		//2冲洗键
		//3烘干键
		//4除菌键
		//5按摩键
		//6保暖键
		//7设置链
		//8待机开关
		if(bButton1 )
		{
			if(!isCleanRuning && 0==g_cCleanCurrentSence)
			{
					aurtEventBtn(1);
					g_cCleanCurrentSence=ezhCleanSence3;
					isCleanRuning=1;
			}
			else
			{
					g_cCleanCurrentSence=0;
					isCleanRuning=0;
					allOutClose();
					aurtEventBtn(0);
			}
					bButton1 = _Disable;
		}
		if(bButton2 )
		{
			if(!isCleanRuning && 0==g_cCleanCurrentSence)
			{
					aurtEventBtn(2);
					g_cCleanCurrentSence=ezhCleanSence4;
					isCleanRuning=1;
			}
			else
			{
					g_cCleanCurrentSence=0;
					isCleanRuning=0;
					allOutClose();
					aurtEventBtn(0);
			}
					bButton2 = _Disable;
		}
		if(bButton3 )
		{
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
					bButton3 = _Disable;
		}
		if(bButton4 )
		{
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
					bButton4 = _Disable;
		}		
		if(bButton5 /*&& 0==g_cCleanCurrentSence*/)
		{
					aurtEventBtn(5);
					g_cCleanCurrentSence=ezhCleanSence7;
					isCleanRuning=1;
					anmiCurrentState=!anmiCurrentState;
					ppxxStep=0; //复位场景
					bButton5 = _Disable;
		}	
		if(bButton6 )
		{
			if(!isCleanRuning && 0==g_cCleanCurrentSence)
			{
					aurtEventBtn(6);
					g_cCleanCurrentSence=ezhCleanSence8;
					isCleanRuning=1;
			}
			else
			{
					g_cCleanCurrentSence=0;
					isCleanRuning=0;
					allOutClose();
					aurtEventBtn(0);
			}
					bButton6 = _Disable;
		}
		if(bButton7 && 0==g_cCleanCurrentSence)
		{
					aurtEventBtn(7);
					bButton7 = _Disable;
		}	
		
		if(bButton8 && 0==g_cCleanCurrentSence)
		{
					aurtEventBtn(8);
					bButton8 = _Disable;
		}	

		//A33POWER_STATE(TOUCHKEY_8_STATE());
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
					//---------------------//
					//陀螺任务,做翻身检测,不知道有啥个伦用
					switch(g_nMPU_DO)
					{
					case 0:
						break;
					case 1://左
						break;
					case 2://右
						break;
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
							else if(rWaterTemp<g_tmeSetting.waterTemperature*10 && 0==bCleanWaterLow) //默认小于40度就加热
							{
 								udoWaterHeating(1);
							}
							else
							{
								udoWaterHeating(0);
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
							{	udoWaterHeating(0);}
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
								_unit6(1);  //气加热单元
							}
							else
							{
								_unit6(0);	//气加热单元
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
							_unit6(0); //气加热单元
						}
					}

					//------------------------------------------------------------------
					//裤档气压
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
					
					//------------------------------------------------------------------
					//床垫气压
					rPressure2Tmp= Get_Adc2_Average(10);
					ntmp=rPressure2Tmp-rPressure2;
					if(ntmp<60 && ntmp>-60) //限制突变幅度
					{
						if(rPressure2Tmp<g_tmeSetting.bedPressure*100)
						{
							if(g_cCleanCurrentSence==0)
							{	udoBedCongQi(1);}
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
					rPressure2=rPressure2Tmp;

					//------------------------------------------------------------------
					//污水满
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
					//污水到位
					if(cgqSewageSuitable)
					{
							bSewageSuitable=1;
					}
					else
					{
							bSewageSuitable=0;
					}
					//---------------------s
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
		if(ezhCleanSence1==(g_cCleanCurrentSence&0xf0) && g_isAutomation) //尿
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}				
				litteSenceRunXuXu();
		}
		else if(ezhCleanSence2==(g_cCleanCurrentSence&0xf0) && g_isAutomation) //屎
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}				
				litteSenceRunPooPoo();
		}
		else if(ezhCleanSence3==(g_cCleanCurrentSence&0xf0))
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}
				 litteSenceRunHuWai();
		}
		else if(ezhCleanSence4==(g_cCleanCurrentSence&0xf0))
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}
				litteSenceRunChongXi();
		}
		else if(ezhCleanSence5==(g_cCleanCurrentSence&0xf0))
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}
				litteSenceRunHongGan();
		}
		else if(ezhCleanSence6==(g_cCleanCurrentSence&0xf0))
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}
				litteSenceRunChuQun();
		}
		else if(ezhCleanSence7==(g_cCleanCurrentSence&0xf0))
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}
				litteSenceRunAnMo();
		}
		else if(ezhCleanSence8==(g_cCleanCurrentSence&0xf0))
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}
				litteSenceRunBaoNang();
				
		}
		else if(ezhCleanSenceA==(g_cCleanCurrentSence&0xf0))
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}
				litteSenceRunA();
				
		}
		else if(ezhCleanSenceB==(g_cCleanCurrentSence&0xf0))
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}
				litteSenceRunB();
				
		}
		else if(ezhCleanSenceC==(g_cCleanCurrentSence&0xf0))
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}
				litteSenceRunC();
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
							aurtEventUnitSence(ezhCleanSence1,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//下一步
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*30/*g_tmeSetting.xuxuDelay*/,ezhCleanSence1);
							break;
						case 2:
							udoXuXuFlush(1);//########### 小便冲洗
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//下一步
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*5,ezhCleanSence1);
							break;
						case 4:
							udoXuXuFlush(0);//########### 小便冲洗
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//下一步
							udoXuPooCollect(1);//############# 屎尿收集器
							break;
						case 5:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*5/*g_tmeSetting.xuxuFlush*/,ezhCleanSence1);
							break;
						case 6:
							udoXuPooCollect(0);//############# 屎尿收集器
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;//下一步
							udoDry(1);//########### 烘干
							break;
						case 7:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50,ezhCleanSence1);
							break;
						case 8:							
							udoDry(0);//########### 烘干
							nCalca=0;
							ppxxStep++;
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
							aurtEventUnitSence(ezhCleanSence2,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;	//下一步
							udoJiaoPan(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*30/*g_tmeSetting.pooDelay * 60*/,ezhCleanSence2);
							break;
						case 2:
							udoPoPoFlush(1);//########### 大便冲洗
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;//下一步
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*4,ezhCleanSence2);
							break;
						case 4:
							udoPoPoFlush(0);//########### 大便冲洗
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;	//下一步
							udoXuPooCollect(1);//############# 屎尿收集器
							break;
						case 5:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*20/*g_tmeSetting.pooFlush*/,ezhCleanSence2);
							break;
						case 6:		
							udoXuPooCollect(0);//############# 屎尿收集器
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							udoPoPoFlush(1);//########### 大便冲洗
							break;
						case 7:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*5,ezhCleanSence2);
							break;
						case 8:
							udoPoPoFlush(0);//########### 大便冲洗
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
						
							udoDry(1);//########### 烘干
							break;
						case 9:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50/*g_tmeSetting.pooDry*10*/,ezhCleanSence2);
							break;
						case 10:
							udoDry(0);//########### 烘干
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
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
							aurtEventUnitSence(ezhCleanSence3,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;	//下一步
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*g_tmeSetting.pooDelay * 60,ezhCleanSence3);
							break;
						case 2:
							udoXuPooCollect(1);//############# 屎尿收集器
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;//下一步
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10,ezhCleanSence3);
							break;
						case 4:
							udoPoPoFlush(1);//########### 大便冲洗
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;	//下一步
							break;
						case 5:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*g_tmeSetting.pooFlush,ezhCleanSence3);
							break;
						case 6:		
							udoPoPoFlush(0);//########### 大便冲洗
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 7:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10,ezhCleanSence3);
							break;
						case 8:
							udoXuPooCollect(0);//############# 屎尿收集器
							udoDry(1);//########### 烘干
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 9:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*g_tmeSetting.pooDry*10,ezhCleanSence3);
							break;
						case 10:
							udoDry(0);//########### 烘干
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 11:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3,ezhCleanSence3);
							break;
						case 12:
							udoDry(1);//########### 烘干
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 13:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*g_tmeSetting.pooDry*10,ezhCleanSence3);
							break;
						case 14:
							udoDry(0);//########### 烘干
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
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
							aurtEventUnitSence(ezhCleanSence4,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;	//下一步
						  udoPoPoFlush(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10,ezhCleanSence4);
							break;
						case 2:	
							udoPoPoFlush(0);
						  udoXuPooCollect(1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;//下一步
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15,ezhCleanSence4);
							break;
						case 4:	
							udoXuPooCollect(0);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;//下一步
							udoDry(1);
							break;
						case 5:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50,ezhCleanSence4);
							break;
						case 6:	
							udoDry(0);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;//下一步
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
							aurtEventUnitSence(ezhCleanSence5,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence5 | ppxxStep;	//下一步
						
							udoDry(1);//########### 烘干
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50,ezhCleanSence5);
							break;
						case 2:
							udoDry(0);//########### 烘干
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence5 | ppxxStep;//下一步
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
							aurtEventUnitSence(ezhCleanSence6,1);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;	//下一步

							_unit5(1);_unit9(1);_unit10(1);_unit13(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3,ezhCleanSence6);
							break;
						case 2:
							_unit7(1);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//下一步
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3,ezhCleanSence6);
							break;
						case 4:
							_unit7(0);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//下一步
							break;
						case 5:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*45,ezhCleanSence6);
							break;
						case 6:
							_unit7(1);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//下一步
							break;
						case 7:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3,ezhCleanSence6);
							break;
						case 8:
							_unit7(0);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//下一步
							break;
						case 9:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*45,ezhCleanSence6);
							break;
						
						case 10:
							_unit7(1);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//下一步
							break;
						case 11:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3,ezhCleanSence6);
							break;
						case 12:
							_unit7(0);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//下一步
							break;
						
						case 13:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*33,ezhCleanSence6);
							break;
						
						case 14:
							_unit5(1);_unit9(1);_unit10(1);_unit13(1);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//下一步
							break;
						
						default: //完毕
							aurtEventUnitSence(ezhCleanSence6,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
					
				/*static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:							
							aurtEventUnitSence(ezhCleanSence6,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;	//下一步

							udoSterilization(1); //########### 除菌
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10,ezhCleanSence6);
							break;
						case 2:
							udoSterilization(0); //########### 除菌
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//下一步
							break;
						default: //完毕
							aurtEventUnitSence(ezhCleanSence6,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}*/
}

/********************************
//按摩
*********************************/
void litteSenceRunAnMo(void)
{
		if(anmiCurrentState)
		{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:							
							aurtEventUnitSence(ezhCleanSence7,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;	//下一步
							ANMO1_STATE(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,15,ezhCleanSence7);
							break;
						case 2:
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;//下一步
							ANMO1_STATE(0);
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,30,ezhCleanSence7);
							break;
						//-----------------------------------------------	
						case 4:							
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;	//下一步
							ANMO1_STATE(1);
						case 5:
							senceDelay(&nCalca,&ppxxStep,15,ezhCleanSence7);
							break;
						case 6:	
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;//下一步
							ANMO1_STATE(0);
							break;
						case 7:
							senceDelay(&nCalca,&ppxxStep,30,ezhCleanSence7);
							break;
						//-----------------------------------------------	
							
						case 8:							
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;	//下一步
							ANMO1_STATE(1);
						case 9:
							senceDelay(&nCalca,&ppxxStep,15,ezhCleanSence7);
							break;
						case 10:	
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;//下一步
							ANMO1_STATE(0);
							break;
						case 11:
							senceDelay(&nCalca,&ppxxStep,30,ezhCleanSence7);
							break;
							/*
						//-----------------------------------------------
							//延时
							case 12:
							if(nCalca>500)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{
										//中断信号
										ANMO1_STATE(1);
										STM32_Delay_ms(200);
										ANMO1_STATE(0);
										//
										g_cCleanCurrentSence=0;nCalca=0;allOutClose();
									}
									nCalca++;
							}
							break;*/
						default: //完毕
							aurtEventUnitSence(ezhCleanSence7,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
		}
		else 
		{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:							
							aurtEventUnitSence(ezhCleanSence7,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;	//下一步
							ANMO1_STATE(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,15,ezhCleanSence7);
							break;
						case 2:	
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;//下一步
							ANMO1_STATE(0);
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,30,ezhCleanSence7);
							break;
						default: //完毕
							aurtEventUnitSence(ezhCleanSence7,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
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
							aurtEventUnitSence(ezhCleanSence8,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence8 | ppxxStep;	//下一步
							BAONAN_STATE(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,10,ezhCleanSence8);
							break;
						case 2:		
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence8 | ppxxStep;//下一步
							BAONAN_STATE(0);
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,300,ezhCleanSence8);
							break;
						default: //完毕
							aurtEventUnitSence(ezhCleanSence8,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
}

//--------------------------------------------------------------------------
//体验场景
void litteSenceRunA(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:
							aurtEventUnitSence(ezhCleanSenceA,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceA | ppxxStep;	//下一步
							
						case 1:
							senceDelay(&nCalca,&ppxxStep,10,ezhCleanSenceA);
							break;
						case 2:		
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceA | ppxxStep;//下一步
							
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,300,ezhCleanSenceA);
							break;
						default: //完毕
							aurtEventUnitSence(ezhCleanSenceA,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
}
void litteSenceRunB(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:
							aurtEventUnitSence(ezhCleanSenceB,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceB | ppxxStep;	//下一步
							
						case 1:
							senceDelay(&nCalca,&ppxxStep,10,ezhCleanSenceB);
							break;
						case 2:		
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceB | ppxxStep;//下一步
							
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,300,ezhCleanSenceB);
							break;
						default: //完毕
							aurtEventUnitSence(ezhCleanSenceB,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
}
void litteSenceRunC(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:
							aurtEventUnitSence(ezhCleanSenceC,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceC | ppxxStep;	//下一步
							
						case 1:
							senceDelay(&nCalca,&ppxxStep,10,ezhCleanSenceC);
							break;
						case 2:		
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceC | ppxxStep;//下一步
							
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,300,ezhCleanSenceC);
							break;
						default: //完毕
							aurtEventUnitSence(ezhCleanSenceC,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
}

