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

//
extern int g_nMPU_DO;
//是否自动化操作
unsigned char g_isAutomation=1;

/*
//-----------当前清洗小场景
	ezhCleanSenceNone没执行,
	ezhCleanSence1自动化小便																					
	ezhCleanSence2自动化大便 
	ezhCleanSence3护卫
	ezhCleanSence4冲洗
	ezhCleanSence5烘干
	ezhCleanSence6除菌
	ezhCleanSence7按摩
	ezhCleanSence8保暖
*/
typedef enum _EzhCleanSence{
	ezhCleanSenceNone=0x00,
	ezhCleanSence1=0x10,
	ezhCleanSence2=0x20,
	ezhCleanSence3=0x30,
	ezhCleanSence4=0x40,
	ezhCleanSence5=0x50,
	ezhCleanSence6=0x60,
	ezhCleanSence7=0x70,
	ezhCleanSence8=0x80,
}EzhCleanSence;
unsigned char g_cCleanCurrentSence=0;  

//场景时间调度
#define DEF_TIME_MS_DELAY		50
//
/**************/
//继电器逻辑重定义
int isOpenDry=0;


#define _unit1(x) 							RELAY1_STATE(!x)		//小便转换
#define _unit2(x) 							RELAY2_STATE(!x)		//大便转换
#define _unit3(x) 							RELAY3_STATE(!x)		//床气转换
#define _unit4(x) 		 					RELAY4_STATE(!x)		//裤子气转机
#define _unit5(x) 							RELAY5_STATE(!x)		//加热气转换
#define _unit6(x) 							RELAY6_STATE(!x)		//气加热
#define _unit7(x) 							RELAY7_STATE(!x)		//抽吸机
#define _unit8(x) 				 			RELAY8_STATE(!x) 		//抽水机
#define _unit9(x) 							RELAY9_STATE(!x)		//杀菌发生器
#define _unit10(x) 				 			RELAY10_STATE(!x)		//吹气
#define _unit11(x)							RELAY11_STATE(!x) 	//水加热
#define _unit12(x) 	 						RELAY12_STATE(!x)		//净化机
#define _unit13(x) 							RELAY13_STATE(!x)		//杀菌气转换

//
#define udoDry(x)						 			_unit5(x);_unit6(x);_unit10(x);isOpenDry=x		//烘干程序
#define udoSterilization(x) 			_unit9(x);_unit10(x);_unit13(x)								//杀菌
#define udoWaterHeating(x) 				_unit11(x)																		//水加热程序
#define udoXuXuFlush(x) 					_unit1(x);_unit8(x)														//小便冲洗
#define udoPoPoFlush(x) 					_unit2(x);_unit8(x)														//大便冲洗
#define udoKuZiCongQi(x) 					_unit4(x);_unit10(x)													//裤子充气
#define udoBedCongQi(x) 	 				_unit3(x);_unit10(x)													//床垫充气
#define udoDeodorization(x) 			_unit7(x);_unit12(x)													//除臭
#define udoKuZiHuanQi(x) 				 	_unit5(x);_unit10(x) 													//裤子换气
#define udoXuPooCollect(x) 				_unit7(x);_unit12(x)													//屎屎尿尿收集

/**************/
//传感器逻辑重定义
#define cgqSewageHeight  					SENSOR1_STATE()?1:0 //污水满
#define cgqCleanWaterLow  				SENSOR2_STATE()?1:0 //清水低
#define cgqSewageSuitable  				SENSOR3_STATE()?0:1 //污水到位

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

//中断运行
int isCleanRuning=0;
int ppxxStep=0;

//摄像头电机
int xiiiLimit=100;
int xiii=0;
int xiii2=0;
int Motor1_do_step=0;
int Motor2_do_step=0;
int motor1_p_or_n=0;
int motor2_p_or_n=0;
void sceMotor1_do(void);
void sceMotor2_do(void);

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
		cbuf[5]=bSewageSuitable;//传感器污水到位
		
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
		
		cbuf[16]=isWaterTooHot;//如果为1就是有问题,就是他奶奶加热功能不知道哪里有问题..
		cbuf[17]=isGasTooHot;

		myDataLen = miniDataCreate(18,cbuf,dst_buf);
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

void allOutClose()
{	
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
}

int main(void)
{
	System_Init();
	/*
	//测试逻辑
	LED1_ON;
	LED1_OFF;
	allOutClose();
	RelayTest();
	allOutClose();
	*/
	//看门狗
	//watchdog_init();
	
	//allOutClose();
	//RELAY1_STATE(1);
	//RELAY2_STATE(1);
	//RELAY4_STATE(1);
	//RELAY5_STATE(1);
	//RELAY6_STATE(1);
	//RELAY7_STATE(1);
	//RELAY8_STATE(1);
	//RELAY9_STATE(1);
	//RELAY10_STATE(1);
	//RELAY11_STATE(1);
	//RELAY12_STATE(1);
	//RELAY13_STATE(1);
	 
	//RELAY3_STATE(1);//
	allOutClose();
	
	//-------------------------------
	//startup system delay-----------
	LED1_ON;
	STM32_Delay_ms(2000);
	g_tmeSetting.pooDelay=1;					  //拉屎后多少秒启动 ,单位分钟
	g_tmeSetting.xuxuDelay=10;				  //拉屎后多少秒启动 ,单位秒
	g_tmeSetting.pooFlush=30;					  //屎屎冲洗  ,	单位秒
	g_tmeSetting.xuxuFlush=10;				  //尿尿冲洗  	单位 秒
	g_tmeSetting.pooDry=2;      		  //屎屎烘干时间 单位 分钟
	g_tmeSetting.xuxuDry=1;					  //尿尿烘干时间 单位 分钟
	g_tmeSetting.pooSterilize=10;			  //屎屎消毒时间 单位 秒
	g_tmeSetting.xuxuSterilize=10;		  //尿尿消毒时间 单位 秒
	g_tmeSetting.crotchPressure=13;			//裤档气压 单位 100电压变数
	g_tmeSetting.bedPressure=13;   			//床垫的气压  单位 100电压变数
	g_tmeSetting.waterTemperature=38;		//最低水温   			单位摄氏度
	g_tmeSetting.airTemperature=50;  		//最低烘干温度   	单位摄氏度
	g_tmeSetting.mpuLeft=30;  					//床陀螺左角度  单位角度
	g_tmeSetting.mpuRight=30;  					//床陀螺右角度  单位角度
		
	//-------------------
	Motor1_do(1);
	STM32F1_UART1SendDataS("abc",3);
	STM32F1_UART2SendDataS("abc",3);
	STM32F1_UART3SendDataS("abc",3);
	
	while(1)
	{
		//看门狗
		//watchdog_action();
		//
		sceMotor1_do();
		sceMotor2_do();
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
		if(bButton1 && 0==g_cCleanCurrentSence)
		{
					aurtEventBtn(1);
					g_cCleanCurrentSence=ezhCleanSence3;
					isCleanRuning=1;
					bButton1 = _Disable;
		}
		if(bButton2 && 0==g_cCleanCurrentSence)
		{
					aurtEventBtn(2);
					g_cCleanCurrentSence=ezhCleanSence4;
					isCleanRuning=1;
					bButton2 = _Disable;
		}
		if(bButton3 && 0==g_cCleanCurrentSence)
		{
					aurtEventBtn(3);
					g_cCleanCurrentSence=ezhCleanSence5;
					isCleanRuning=1;
					bButton3 = _Disable;
		}
		if(bButton4 && 0==g_cCleanCurrentSence)
		{
					aurtEventBtn(4);
					g_cCleanCurrentSence=ezhCleanSence6;
					isCleanRuning=1;
					bButton4 = _Disable;
		}		
		if(bButton5 && 0==g_cCleanCurrentSence)
		{
					aurtEventBtn(5);
					g_cCleanCurrentSence=ezhCleanSence7;
					isCleanRuning=1;
					bButton5 = _Disable;
		}	
		if(bButton6 && 0==g_cCleanCurrentSence)
		{
					aurtEventBtn(6);
					g_cCleanCurrentSence=ezhCleanSence8;
					isCleanRuning=1;
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
		//------------------------------------------------------------------
		//检测有无尿拉下来		
		if(rWaterTemperature>=g_tmeSetting.waterTemperature*10) //限制如果水温不够不操作
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

		//------------------------------------------------------------------
		//检测有没有屎掉下来
		if(rWaterTemperature>=g_tmeSetting.waterTemperature*10)  //限制如果水温不够不操作
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

		//---------------------//
		if(kk>=10 && xiii>=xiiiLimit && xiii>=xiiiLimit) //限制0.1秒执行一次,且步进电机不能有动作
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
							if(rWaterTemp > 60*10) //加热器有问题了吧,太高了就是他妈的加热器有问题了.
							{
								//水他妈必的太热了.发到串口告诉上位机端,通知护士小妹妹,机器故障了
								isWaterTooHot=1;
							}
							
							if(rWaterTemp<g_tmeSetting.waterTemperature*10 ) //默认小于40度就加热
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
							if(rGasTemp > 60*10) //加热器有问题了吧,太高了就是他妈的加热器有问题了.
							{
								//气温他妈必的太热了.发到串口告诉上位机端,通知护士小妹妹,机器故障了
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
		//定时上传状态
		if(kk2>200)
		{
					aurtEventStatus();
					kk2=0;
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
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.xuxuDelay)  //默认10秒延时后开始清理
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:
							udoXuPooCollect(1);//############# 屎尿收集器
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//下一步
							break;
						case 3:
							if(nCalca>DEF_TIME_MS_DELAY*10)  //10秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 4:
							udoXuXuFlush(1);//########### 小便冲洗
				
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//下一步
							break;
						case 5:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.xuxuFlush) //10秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 6:
							udoXuXuFlush(0);//########### 小便冲洗
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;//下一步
							break;
						case 7:
							if(nCalca>DEF_TIME_MS_DELAY*10) //10秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 8:						
							udoXuPooCollect(0);//############# 屎尿收集器
						
							udoDry(1);//########### 烘干
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							break;
						case 9:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.xuxuDry) //60秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 10:							
							udoDry(0);//########### 烘干
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
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
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY* g_tmeSetting.pooDelay * 60)  //默认60秒延时后开始清理
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:
							udoXuPooCollect(1);//############# 屎尿收集器
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;//下一步
							break;
						case 3:
							if(nCalca>DEF_TIME_MS_DELAY*10)  //默认10秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 4:
							udoPoPoFlush(1);//########### 大便冲洗
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;	//下一步
							break;
						case 5:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.pooFlush) //默认30秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 6:		
							udoPoPoFlush(0);//########### 大便冲洗
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							break;
						case 7:
							if(nCalca>DEF_TIME_MS_DELAY*10) //10秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 8:
							udoXuPooCollect(0);//############# 屎尿收集器
						
							udoDry(1);//########### 烘干
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							break;
						case 9:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.pooDry*60) //120秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
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
							if(nCalca>DEF_TIME_MS_DELAY* g_tmeSetting.pooDelay * 60)  //默认60秒延时后开始清理
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:
							udoXuPooCollect(1);//############# 屎尿收集器
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;//下一步
							break;
						case 3:
							if(nCalca>DEF_TIME_MS_DELAY*10)  //默认10秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 4:
							udoPoPoFlush(1);//########### 大便冲洗
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;	//下一步
							break;
						case 5:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.pooFlush) //默认30秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 6:		
							udoPoPoFlush(0);//########### 大便冲洗
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 7:
							if(nCalca>DEF_TIME_MS_DELAY*10) //10秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 8:
							udoXuPooCollect(0);//############# 屎尿收集器
						
							udoDry(1);//########### 烘干
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 9:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.pooDry*60) //120秒延时
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 10:
							
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
							if(nCalca>DEF_TIME_MS_DELAY*5)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:	
							udoPoPoFlush(0);
						  udoDry(1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;//下一步
							break;
						case 3:
							if(nCalca>DEF_TIME_MS_DELAY*20)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 4:	
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
							if(nCalca>DEF_TIME_MS_DELAY*20)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence5 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
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
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;	//下一步

							udoSterilization(1); //########### 除菌
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY*20)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
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
							aurtEventUnitSence(ezhCleanSence7,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;	//下一步
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY*10)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:							
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;//下一步
							break;
						default: //完毕
							aurtEventUnitSence(ezhCleanSence7,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
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
							aurtEventUnitSence(ezhCleanSence8,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence8 | ppxxStep;	//下一步
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY*10)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence8 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//中断
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:							
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence8 | ppxxStep;//下一步
							break;
						default: //完毕
							aurtEventUnitSence(ezhCleanSence8,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//场景复位
							ppxxStep=0;
							break;
					}
}

void Motor1_do(int p_or_n)
{
	motor1_p_or_n=p_or_n;
	Motor1_do_step=1;
	xiii=0;
}
void Motor2_do(int p_or_n)
{
	motor2_p_or_n=p_or_n;
  Motor2_do_step=1;
	xiii2=0;
}
	
void sceMotor1_do(void)
{		
		static int dododyes=70;
		static int nCalca=0;
	  if(xiii<xiiiLimit)
		{
						if(motor1_p_or_n)
						{
									switch(Motor1_do_step)
									{
										case 1:
											nCalca=0;
											Motor1_do_step++;	//下一步							
											MOTOR1_A_STATE(1);
											MOTOR1_B_STATE(0);
											MOTOR1_C_STATE(0);
											MOTOR1_D_STATE(0);
										case 2:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 3:
											nCalca=0;
											Motor1_do_step++;	//下一步							
											MOTOR1_A_STATE(1);
											MOTOR1_B_STATE(1);
											MOTOR1_C_STATE(0);
											MOTOR1_D_STATE(0);
											break;
										case 4:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 5:
											nCalca=0;
											Motor1_do_step++;	//下一步
											MOTOR1_A_STATE(0);
											MOTOR1_B_STATE(1);
											MOTOR1_C_STATE(0);
											MOTOR1_D_STATE(0);						
											break;
										case 6:
											if(nCalca>1000)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 7:
											nCalca=0;
											Motor1_do_step++;	//下一步
											MOTOR1_A_STATE(0);
											MOTOR1_B_STATE(1);
											MOTOR1_C_STATE(1);
											MOTOR1_D_STATE(0);						
											break;
										case 8:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 9:
											nCalca=0;
											Motor1_do_step++;	//下一步
											MOTOR1_A_STATE(0);
											MOTOR1_B_STATE(0);
											MOTOR1_C_STATE(1);
											MOTOR1_D_STATE(0);
											break;
										case 10:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 11:
											nCalca=0;
											Motor1_do_step++;	//下一步
											MOTOR1_A_STATE(0);
											MOTOR1_B_STATE(0);
											MOTOR1_C_STATE(1);
											MOTOR1_D_STATE(1);
											break;
										case 12:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 13:
											nCalca=0;
											Motor1_do_step++;	//下一步
											MOTOR1_A_STATE(0);
											MOTOR1_B_STATE(0);
											MOTOR1_C_STATE(0);
											MOTOR1_D_STATE(1);
											break;
										case 14:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 15:
											nCalca=0;
											Motor1_do_step++;	//下一步
											MOTOR1_A_STATE(1);
											MOTOR1_B_STATE(0);
											MOTOR1_C_STATE(0);
											MOTOR1_D_STATE(1);
											break;
										case 16:
											Motor1_do_step=1;
											xiii++;
											break;
									}

						}
						else
						{
									switch(Motor1_do_step)
									{
										case 1:
											nCalca=0;
											Motor1_do_step++;	//下一步							
				MOTOR1_A_STATE(1);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(1);
										case 2:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 3:
											nCalca=0;
											Motor1_do_step++;	//下一步							
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(1);
											break;
										case 4:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 5:
											nCalca=0;
											Motor1_do_step++;	//下一步
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(1);
				MOTOR1_D_STATE(1);				
											break;
										case 6:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 7:
											nCalca=0;
											Motor1_do_step++;	//下一步
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(1);
				MOTOR1_D_STATE(0);				
											break;
										case 8:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 9:
											nCalca=0;
											Motor1_do_step++;	//下一步
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(1);
				MOTOR1_C_STATE(1);
				MOTOR1_D_STATE(0);
											break;
										case 10:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 11:
											nCalca=0;
											Motor1_do_step++;	//下一步
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(1);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(0);
											break;
										case 12:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 13:
											nCalca=0;
											Motor1_do_step++;	//下一步
				MOTOR1_A_STATE(1);
				MOTOR1_B_STATE(1);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(0);
											break;
										case 14:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 15:
											nCalca=0;
											Motor1_do_step++;	//下一步
				MOTOR1_A_STATE(1);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(0);
											break;
										case 16:
											Motor1_do_step=1;
											break;
									}
						}
	}
	else
	{
				//关掉线圈套的任何通电行为
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(0);
	}
}

void sceMotor2_do(void)
{
	static int dododyes=70;
	static int nCalca=0;
	if(xiii<xiiiLimit)
	{
		if(motor2_p_or_n)
		{
				

		}
		else
		{
					
		}
	}
	else
	{
				//关掉线圈套的任何通电行为
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(0);
	}
}
