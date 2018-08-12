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

//
extern int g_nMPU_DO;
//ÊÇ·ñ×Ô¶¯»¯²Ù×÷
unsigned char g_isAutomation=1;

/*
//-----------µ±Ç°ÇåÏ´Ğ¡³¡¾°
	ezhCleanSenceNoneÃ»Ö´ĞĞ,
	ezhCleanSence1×Ô¶¯»¯Ğ¡±ã																					
	ezhCleanSence2×Ô¶¯»¯´ó±ã 
	ezhCleanSence3»¤ÎÀ
	ezhCleanSence4³åÏ´
	ezhCleanSence5ºæ¸É
	ezhCleanSence6³ı¾ú
	ezhCleanSence7°´Ä¦
	ezhCleanSence8±£Å¯
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

//³¡¾°Ê±¼äµ÷¶È
#define DEF_TIME_MS_DELAY		50
//
/**************/
//¼ÌµçÆ÷Âß¼­ÖØ¶¨Òå
int isOpenDry=0;


#define _unit1(x) 							RELAY1_STATE(!x)		//Ğ¡±ã×ª»»
#define _unit2(x) 							RELAY2_STATE(!x)		//´ó±ã×ª»»
#define _unit3(x) 							RELAY3_STATE(!x)		//´²Æø×ª»»
#define _unit4(x) 		 					RELAY4_STATE(!x)		//¿ã×ÓÆø×ª»ú
#define _unit5(x) 							RELAY5_STATE(!x)		//¼ÓÈÈÆø×ª»»
#define _unit6(x) 							RELAY6_STATE(!x)		//Æø¼ÓÈÈ
#define _unit7(x) 							RELAY7_STATE(!x)		//³éÎü»ú
#define _unit8(x) 				 			RELAY8_STATE(!x) 		//³éË®»ú
#define _unit9(x) 							RELAY9_STATE(!x)		//É±¾ú·¢ÉúÆ÷
#define _unit10(x) 				 			RELAY10_STATE(!x)		//´µÆø
#define _unit11(x)							RELAY11_STATE(!x) 	//Ë®¼ÓÈÈ
#define _unit12(x) 	 						RELAY12_STATE(!x)		//¾»»¯»ú
#define _unit13(x) 							RELAY13_STATE(!x)		//É±¾úÆø×ª»»

//
#define udoDry(x)						 			_unit5(x);_unit6(x);_unit10(x);isOpenDry=x		//ºæ¸É³ÌĞò
#define udoSterilization(x) 			_unit9(x);_unit10(x);_unit13(x)								//É±¾ú
#define udoWaterHeating(x) 				_unit11(x)																		//Ë®¼ÓÈÈ³ÌĞò
#define udoXuXuFlush(x) 					_unit1(x);_unit8(x)														//Ğ¡±ã³åÏ´
#define udoPoPoFlush(x) 					_unit2(x);_unit8(x)														//´ó±ã³åÏ´
#define udoKuZiCongQi(x) 					_unit4(x);_unit10(x)													//¿ã×Ó³äÆø
#define udoBedCongQi(x) 	 				_unit3(x);_unit10(x)													//´²µæ³äÆø
#define udoDeodorization(x) 			_unit7(x);_unit12(x)													//³ı³ô
#define udoKuZiHuanQi(x) 				 	_unit5(x);_unit10(x) 													//¿ã×Ó»»Æø
#define udoXuPooCollect(x) 				_unit7(x);_unit12(x)													//ÊºÊºÄòÄòÊÕ¼¯

/**************/
//´«¸ĞÆ÷Âß¼­ÖØ¶¨Òå
#define cgqSewageHeight  					SENSOR1_STATE()?1:0 //ÎÛË®Âú
#define cgqCleanWaterLow  				SENSOR2_STATE()?1:0 //ÇåË®µÍ
#define cgqSewageSuitable  				SENSOR3_STATE()?0:1 //ÎÛË®µ½Î»

//´óĞ¡±ã¼ì²â
#define dxbPooPoo  				SENSOR4_STATE()?0:1    //Êº
#define dxbXuXu	  				SENSOR5_STATE()?0:1    //Äò

//--
//ÎÂ¶È
int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0,rGasTemperature=0,rGasTemp=0;
s16 rTrueWaterTemp=0,rTrueGasTemp=0;
int isWaterTooHot=0;
int isGasTooHot=0;
int isCheckWaterSensorErr=0; //Ë®ÎÂ·À´íÎóÏŞÖÆ
int isCheckGasSensorErr=0;//Ë®ÎÂ·À´íÎóÏŞÖÆ
int isCheckBedCQSensorErr=0;//ÆøÑ¹·À´íÎóÏŞÖÆ
int isCheckDZCQSensorErr=0;	//ÆøÑ¹·À´íÎóÏŞÖÆ

//ÆøÑ¹
u16_t rPressure=0,rPressureTmp=0,rPressure2=0,rPressure2Tmp=0;
u16_t rTruePressure1=0,rTruePressure2=0;
//ÊºÊºÄòÄòµÄ·À¶¶¶¯
int rPoopoDD=0;
int rXuxuDD=0;

//Âö²©
unsigned char cHeartJump=0;
//ÎÛË®Âú
char bSewageHeight=0;
//ÇåË®Ì«ÉÙ
char bCleanWaterLow=0;
//ÎÛË®µ½Î»
char bSewageSuitable=0;
//Ê±¼äµ÷¶ÈÖµ
extern TagTimeingSetting g_tmeSetting;

//ÖĞ¶ÏÔËĞĞ
int isCleanRuning=0;
int ppxxStep=0;

//ÉãÏñÍ·µç»ú
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
	ezhCleanSence1×Ô¶¯»¯Ğ¡±ã																					
	ezhCleanSence2×Ô¶¯»¯´ó±ã 
	ezhCleanSence3»¤ÎÀ
	ezhCleanSence4³åÏ´
	ezhCleanSence5ºæ¸É
	ezhCleanSence6³ı¾ú
	ezhCleanSence7°´Ä¦
	ezhCleanSence8±£Å¯
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

//Ìá½»µ±Ç°×´Ì¬
void aurtEventStatus()
{
		uchar dst_buf[50]={0};
		unsigned char cbuf[23]={0};
		int myDataLen=0;
		//
		cbuf[0]=0;
		
		cbuf[1]=g_isAutomation;
		cbuf[2]=g_cCleanCurrentSence;
				
		cbuf[3]=bSewageHeight;//´«¸ĞÆ÷ÎÛË®Âú
		cbuf[4]=bCleanWaterLow;//´«¸ĞÆ÷ÇåË®Ì«Ğ¡
		cbuf[5]=bSewageSuitable;//´«¸ĞÆ÷ÎÛË®µ½Î»
		
		cbuf[6]=cHeartJump; //Âö²©
		cbuf[7]=0;
		
		cbuf[8]=rTrueWaterTemp&0xff; //Ë®ÎÂ¶È
		cbuf[9]=rTrueWaterTemp>>8;
		
		cbuf[10]=rTrueGasTemp&0xff; //ÆøÎÂ¶È
		cbuf[11]=rTrueGasTemp>>8;
		
		cbuf[12]=rTruePressure1&0xff; //¿ãµµÆøÑ¹
		cbuf[13]=rTruePressure1>>8;
		
		cbuf[14]=rTruePressure2&0xff; //´²µæÆøÑ¹
		cbuf[15]=rTruePressure2>>8;
		
		cbuf[16]=isWaterTooHot;//Èç¹ûÎª1¾ÍÊÇÓĞÎÊÌâ,¾ÍÊÇËûÄÌÄÌ¼ÓÈÈ¹¦ÄÜ²»ÖªµÀÄÄÀïÓĞÎÊÌâ..
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
			1//¼ÌµçÆ÷³éÎüÆôÓÃ
			2//¼ÌµçÆ÷ºæ¸ÉÆôÓÃ
			3//¼ÌµçÆ÷³ı¾úÆôÓÃ
			4//¼ÌµçÆ÷´ó±ãÆôÓÃ
			5//¼ÌµçÆ÷´ó±ã³åÏ´ÆôÓÃ
			6//¼ÌµçÆ÷Ğ¡±ãÆôÓÃ
			7//¼ÌµçÆ÷Ğ¡±ã³åÏ´ÆôÓÃ
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
	 _unit1(0); 									//Ğ¡±ã×ª»»
	 _unit2(0); 									//´ó±ã×ª»»
	 _unit3(0); 									//´²Æø×ª»»
	 _unit4(0); 		 							//¿ã×ÓÆø×ª»ú
	 _unit5(0); 									//¼ÓÈÈÆø×ª»»
	 _unit6(0); 									//Æø¼ÓÈÈ
	 _unit7(0); 									//³éÎü»ú
	 _unit8(0); 				 			 		//³éË®»ú
	 _unit9(0); 									//É±¾ú·¢ÉúÆ÷
	 _unit10(0); 				 					//´µÆø
	 _unit11(0);							 		//Ë®¼ÓÈÈ
	 _unit12(0); 	 								//¾»»¯»ú
	 _unit13(0); 									//É±¾úÆø×ª»»
}

int main(void)
{
	Code_Init();
	
	STM32F1_UART1SendDataS("start",6);

	/*
	//²âÊÔÂß¼­
	LED1_ON;
	LED1_OFF;
	allOutClose();
	RelayTest();
	allOutClose();
	*/
	//¿´ÃÅ¹·
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
	STM32_Delay_ms(2000);
	//
	LED1_ON;LED2_ON;LED3_ON;
	
	//»ñÈ¡Êı¾İ
	FLASH_ReadByte(STARTADDR ,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));
	
	if(g_tmeSetting.waterTemperature<10 || g_tmeSetting.waterTemperature>70)
	{
			g_tmeSetting.pooDelay=1;					  //À­Êººó¶àÉÙÃëÆô¶¯ ,µ¥Î»·ÖÖÓ
			g_tmeSetting.xuxuDelay=10;				  //À­Êººó¶àÉÙÃëÆô¶¯ ,µ¥Î»Ãë
			g_tmeSetting.pooFlush=30;					  //ÊºÊº³åÏ´  ,	µ¥Î»Ãë
			g_tmeSetting.xuxuFlush=10;				  //ÄòÄò³åÏ´  	µ¥Î» Ãë
			g_tmeSetting.pooDry=2;      		  //ÊºÊººæ¸ÉÊ±¼ä µ¥Î» ·ÖÖÓ
			g_tmeSetting.xuxuDry=1;					  //ÄòÄòºæ¸ÉÊ±¼ä µ¥Î» ·ÖÖÓ
			g_tmeSetting.pooSterilize=10;			  //ÊºÊºÏû¶¾Ê±¼ä µ¥Î» Ãë
			g_tmeSetting.xuxuSterilize=10;		  //ÄòÄòÏû¶¾Ê±¼ä µ¥Î» Ãë
			g_tmeSetting.crotchPressure=13;			//¿ãµµÆøÑ¹ µ¥Î» 100µçÑ¹±äÊı
			g_tmeSetting.bedPressure=13;   			//´²µæµÄÆøÑ¹  µ¥Î» 100µçÑ¹±äÊı
			g_tmeSetting.waterTemperature=38;		//×îµÍË®ÎÂ   			µ¥Î»ÉãÊÏ¶È
			g_tmeSetting.airTemperature=50;  		//×îµÍºæ¸ÉÎÂ¶È   	µ¥Î»ÉãÊÏ¶È
			g_tmeSetting.mpuLeft=30;  					//´²ÍÓÂİ×ó½Ç¶È  µ¥Î»½Ç¶È
			g_tmeSetting.mpuRight=30;  					//´²ÍÓÂİÓÒ½Ç¶È  µ¥Î»½Ç¶È
				
			FLASH_WriteByte(STARTADDR,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));
	}

		
	//-------------------
	Motor1_do(1);
	
	while(1)
	{
		//¿´ÃÅ¹·
		//watchdog_action();
		//
		sceMotor1_do();
		sceMotor2_do();
		//
		TouchKey_Scan();
		//---------------------
		//°´¼ü
		//1»¤ÎÀ¼ü
		//2³åÏ´¼ü
		//3ºæ¸É¼ü
		//4³ı¾ú¼ü
		//5°´Ä¦¼ü
		//6±£Å¯¼ü
		//7ÉèÖÃÁ´
		//8´ı»ú¿ª¹Ø
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
		//¼ì²âÓĞÎŞÄòÀ­ÏÂÀ´		
		if(rWaterTemperature>=g_tmeSetting.waterTemperature*10) //ÏŞÖÆÈç¹ûË®ÎÂ²»¹»²»²Ù×÷
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
		//¼ì²âÓĞÃ»ÓĞÊºµôÏÂÀ´
		if(rWaterTemperature>=g_tmeSetting.waterTemperature*10)  //ÏŞÖÆÈç¹ûË®ÎÂ²»¹»²»²Ù×÷
		if(dxbPooPoo)
		{
			rPoopoDD++;
			if(rPoopoDD>2000)
			{
					if(0==g_cCleanCurrentSence && g_isAutomation)//³¡¾°Ö´ĞĞÖĞ
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
		if(kk>=10 && xiii>=xiiiLimit && xiii>=xiiiLimit) //ÏŞÖÆ0.1ÃëÖ´ĞĞÒ»´Î,ÇÒ²½½øµç»ú²»ÄÜÓĞ¶¯×÷
		{
					//---------------------//
					//ÍÓÂİÈÎÎñ,×ö·­Éí¼ì²â,²»ÖªµÀÓĞÉ¶¸öÂ×ÓÃ
					switch(g_nMPU_DO)
					{
					case 0:
						break;
					case 1://×ó
						break;
					case 2://ÓÒ
						break;
					}
					//------------------------------------------------------------------
					//Ë®ÎÂ¼ÓÈÈ
					rWaterTemp=DS18B20_Get_Temp();
					if(rWaterTemp<2000 && rWaterTemp> -200) //ÏŞÖÆÎ»
					{
						ntmp=rWaterTemp-rWaterTemperature;
						if(ntmp<20 && ntmp>-20)	//ÏŞÖÆÍ»±ä·ù¶È
						{
							isWaterTooHot=0;							
							if(rWaterTemp > 60*10) //¼ÓÈÈÆ÷ÓĞÎÊÌâÁË°É,Ì«¸ßÁË¾ÍÊÇËûÂèµÄ¼ÓÈÈÆ÷ÓĞÎÊÌâÁË.
							{
								//Ë®ËûÂè±ØµÄÌ«ÈÈÁË.·¢µ½´®¿Ú¸æËßÉÏÎ»»ú¶Ë,Í¨Öª»¤Ê¿Ğ¡ÃÃÃÃ,»úÆ÷¹ÊÕÏÁË
								isWaterTooHot=1;
							}
							
							if(rWaterTemp<g_tmeSetting.waterTemperature*10 ) //Ä¬ÈÏĞ¡ÓÚ40¶È¾Í¼ÓÈÈ
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
						if(isCheckWaterSensorErr>10) //´«¸ĞÊı¾İÃ«²¡Ì«¶à¹Øµô¼ÓÈÈ¼ÌµçÆ÷
						{
							//´«¸ĞÆ÷ÓĞÃ«²¡ÁË.¹Øµô¼ÌµçÆ÷
							if(g_cCleanCurrentSence==0)
							{	udoWaterHeating(0);}
						}
					}
	
					//-------------------------------------------------------------------
					//¿ÕÆø¼ÓÈÈ,ÊµÊ±Ìõ¼şÏŞÖÆ
					rGasTemp=DS18B20_Get_Temp1(); 
					if(rGasTemp<2000 && rGasTemp> -200) //ÏŞÖÆÎ»
					{
						ntmp=rGasTemp-rGasTemperature;
						if(ntmp<20 && ntmp>-20) //ÏŞÖÆÍ»±ä·ù¶È
						{
							isGasTooHot=0;							
							if(rGasTemp > 60*10) //¼ÓÈÈÆ÷ÓĞÎÊÌâÁË°É,Ì«¸ßÁË¾ÍÊÇËûÂèµÄ¼ÓÈÈÆ÷ÓĞÎÊÌâÁË.
							{
								//ÆøÎÂËûÂè±ØµÄÌ«ÈÈÁË.·¢µ½´®¿Ú¸æËßÉÏÎ»»ú¶Ë,Í¨Öª»¤Ê¿Ğ¡ÃÃÃÃ,»úÆ÷¹ÊÕÏÁË
								isGasTooHot=1;
							}
							
							if(isOpenDry && rGasTemp<g_tmeSetting.airTemperature*10 ) //50¶ÈÇÒºæ¿ª¹ØµÄÊ±ºò²Å´¦Àí
							{
								_unit6(1);  //Æø¼ÓÈÈµ¥Ôª
							}
							else
							{
								_unit6(0);	//Æø¼ÓÈÈµ¥Ôª
							}
							rTrueGasTemp=rGasTemp;
							isCheckGasSensorErr=0;
						}
						rGasTemperature=rGasTemp;
					}
					else
					{
						isCheckGasSensorErr++;						
						if(isCheckGasSensorErr>10) //´«¸ĞÊı¾İÓĞÃ«²¡¹Øµô¼ÓÈÈ¼ÌµçÆ÷
						{
							//´«¸ĞÆ÷ÓĞÃ«²¡ÁË.¹Øµô¼ÌµçÆ÷
							_unit6(0); //Æø¼ÓÈÈµ¥Ôª
						}
					}

					//------------------------------------------------------------------
					//¿ãµµÆøÑ¹
					rPressureTmp = Get_Adc_Average(10);
					ntmp=rPressureTmp-rPressure;
					if(ntmp<60 && ntmp>-60) //ÏŞÖÆÍ»±ä·ù¶È
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
						if(isCheckDZCQSensorErr>10) //´«¸ĞÊı¾İÓĞÃ«²¡¹Øµô¼ÌµçÆ÷
						{
							if(g_cCleanCurrentSence==0)
							{	udoKuZiCongQi(0);}
						}
					}
					rPressure=rPressureTmp;
					
					//------------------------------------------------------------------
					//´²µæÆøÑ¹
					rPressure2Tmp= Get_Adc2_Average(10);
					ntmp=rPressure2Tmp-rPressure2;
					if(ntmp<60 && ntmp>-60) //ÏŞÖÆÍ»±ä·ù¶È
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
						if(isCheckBedCQSensorErr>10) //´«¸ĞÊı¾İÃ«²¡Ì«¶à¹ØµÈ¼ÌµçÆ÷
						{
							if(g_cCleanCurrentSence==0)
							{	udoBedCongQi(0);}
						}
					}
					rPressure2=rPressure2Tmp;

					//------------------------------------------------------------------
					//ÎÛË®Âú
					if(cgqSewageHeight)
					{
							bSewageHeight=1;
					}
					else
					{
							bSewageHeight=0;
					}

					//------------------------------------------------------------------
					//ÇåË®Ì«ÉÙ
					if(cgqCleanWaterLow)
					{
							bCleanWaterLow=1;
					}
					else
					{
							bCleanWaterLow=0;
					}

					//------------------------------------------------------------------
					//ÎÛË®µ½Î»
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
		//¶¨Ê±ÉÏ´«×´Ì¬
		if(kk2>200)
		{
					aurtEventStatus();
					kk2=0;
		}
		//------------------------------------------------------------------
		//³åÊºÏ´Äò¹¦ÄÜ
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
		if(ezhCleanSence1==(g_cCleanCurrentSence&0xf0) && g_isAutomation) //Äò
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}				
				litteSenceRunXuXu();
		}
		else if(ezhCleanSence2==(g_cCleanCurrentSence&0xf0) && g_isAutomation) //Êº
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
				//Ã»ÓĞ³¡¾°
				g_cCleanCurrentSence=0;
				
		}		
}


/*********************************************************

----ÔËĞĞ³¡¾°----

***********************************************************/
void litteSenceRunXuXu()
{					
					static int nCalca=0;	
					switch(ppxxStep)
					{
						case 0:
							aurtEventUnitSence(ezhCleanSence1,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//ÏÂÒ»²½
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.xuxuDelay)  //Ä¬ÈÏ10ÃëÑÓÊ±ºó¿ªÊ¼ÇåÀí
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:
							udoXuPooCollect(1);//############# ÊºÄòÊÕ¼¯Æ÷
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//ÏÂÒ»²½
							break;
						case 3:
							if(nCalca>DEF_TIME_MS_DELAY*10)  //10ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 4:
							udoXuXuFlush(1);//########### Ğ¡±ã³åÏ´
				
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//ÏÂÒ»²½
							break;
						case 5:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.xuxuFlush) //10ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 6:
							udoXuXuFlush(0);//########### Ğ¡±ã³åÏ´
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;//ÏÂÒ»²½
							break;
						case 7:
							if(nCalca>DEF_TIME_MS_DELAY*10) //10ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 8:						
							udoXuPooCollect(0);//############# ÊºÄòÊÕ¼¯Æ÷
						
							udoDry(1);//########### ºæ¸É
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							break;
						case 9:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.xuxuDry) //60ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 10:							
							udoDry(0);//########### ºæ¸É
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;
							break;						
						default: //Íê±Ï							
							aurtEventUnitSence(ezhCleanSence1,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//³¡¾°¸´Î»
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
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;	//ÏÂÒ»²½
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY* g_tmeSetting.pooDelay * 60)  //Ä¬ÈÏ60ÃëÑÓÊ±ºó¿ªÊ¼ÇåÀí
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:
							udoXuPooCollect(1);//############# ÊºÄòÊÕ¼¯Æ÷
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;//ÏÂÒ»²½
							break;
						case 3:
							if(nCalca>DEF_TIME_MS_DELAY*10)  //Ä¬ÈÏ10ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 4:
							udoPoPoFlush(1);//########### ´ó±ã³åÏ´
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;	//ÏÂÒ»²½
							break;
						case 5:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.pooFlush) //Ä¬ÈÏ30ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 6:		
							udoPoPoFlush(0);//########### ´ó±ã³åÏ´
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							break;
						case 7:
							if(nCalca>DEF_TIME_MS_DELAY*10) //10ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 8:
							udoXuPooCollect(0);//############# ÊºÄòÊÕ¼¯Æ÷
						
							udoDry(1);//########### ºæ¸É
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							break;
						case 9:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.pooDry*60) //120ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 10:
							
							udoDry(0);//########### ºæ¸É
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							break;
						
						default: //Íê±Ï
							aurtEventUnitSence(ezhCleanSence2,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//³¡¾°¸´Î»
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
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;	//ÏÂÒ»²½
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY* g_tmeSetting.pooDelay * 60)  //Ä¬ÈÏ60ÃëÑÓÊ±ºó¿ªÊ¼ÇåÀí
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:
							udoXuPooCollect(1);//############# ÊºÄòÊÕ¼¯Æ÷
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;//ÏÂÒ»²½
							break;
						case 3:
							if(nCalca>DEF_TIME_MS_DELAY*10)  //Ä¬ÈÏ10ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 4:
							udoPoPoFlush(1);//########### ´ó±ã³åÏ´
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;	//ÏÂÒ»²½
							break;
						case 5:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.pooFlush) //Ä¬ÈÏ30ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 6:		
							udoPoPoFlush(0);//########### ´ó±ã³åÏ´
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 7:
							if(nCalca>DEF_TIME_MS_DELAY*10) //10ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 8:
							udoXuPooCollect(0);//############# ÊºÄòÊÕ¼¯Æ÷
						
							udoDry(1);//########### ºæ¸É
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 9:
							if(nCalca>DEF_TIME_MS_DELAY*g_tmeSetting.pooDry*60) //120ÃëÑÓÊ±
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 10:
							
							udoDry(0);//########### ºæ¸É
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						
						default: //Íê±Ï
							aurtEventUnitSence(ezhCleanSence3,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//³¡¾°¸´Î»
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
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;	//ÏÂÒ»²½
						  udoPoPoFlush(1);
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY*5)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:	
							udoPoPoFlush(0);
						  udoDry(1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;//ÏÂÒ»²½
							break;
						case 3:
							if(nCalca>DEF_TIME_MS_DELAY*20)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 4:	
							udoDry(0);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;//ÏÂÒ»²½
							break;
						default: //Íê±Ï
							aurtEventUnitSence(ezhCleanSence4,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//³¡¾°¸´Î»
							ppxxStep=0;
							break;
					}
}

/********************************
//ºæ¸É
*********************************/
void litteSenceRunHongGan(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:							
							aurtEventUnitSence(ezhCleanSence5,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence5 | ppxxStep;	//ÏÂÒ»²½
						
							udoDry(1);//########### ºæ¸É
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY*20)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence5 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:
							
							udoDry(0);//########### ºæ¸É
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence5 | ppxxStep;//ÏÂÒ»²½
							break;
						default: //Íê±Ï
							aurtEventUnitSence(ezhCleanSence5,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//³¡¾°¸´Î»
							ppxxStep=0;
							break;
					}
}

/********************************
//³ı¾ú
*********************************/
void litteSenceRunChuQun(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:							
							aurtEventUnitSence(ezhCleanSence6,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;	//ÏÂÒ»²½

							udoSterilization(1); //########### ³ı¾ú
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY*20)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:
							udoSterilization(0); //########### ³ı¾ú
						
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//ÏÂÒ»²½
							break;
						default: //Íê±Ï
							aurtEventUnitSence(ezhCleanSence6,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//³¡¾°¸´Î»
							ppxxStep=0;
							break;
					}
}

/********************************
//°´Ä¦
*********************************/
void litteSenceRunAnMo(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:							
							aurtEventUnitSence(ezhCleanSence7,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;	//ÏÂÒ»²½
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY*10)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:							
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;//ÏÂÒ»²½
							break;
						default: //Íê±Ï
							aurtEventUnitSence(ezhCleanSence7,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//³¡¾°¸´Î»
							ppxxStep=0;
							break;
					}
}

/********************************
//±£Å¯
*********************************/
void litteSenceRunBaoNang(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:
							aurtEventUnitSence(ezhCleanSence8,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence8 | ppxxStep;	//ÏÂÒ»²½
						case 1:
							if(nCalca>DEF_TIME_MS_DELAY*10)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence8 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//ÖĞ¶Ï
									{g_cCleanCurrentSence=0;nCalca=0;allOutClose();}
									nCalca++;
							}
							break;
						case 2:							
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence8 | ppxxStep;//ÏÂÒ»²½
							break;
						default: //Íê±Ï
							aurtEventUnitSence(ezhCleanSence8,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//³¡¾°¸´Î»
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
											Motor1_do_step++;	//ÏÂÒ»²½							
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
											Motor1_do_step++;	//ÏÂÒ»²½							
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½							
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
											Motor1_do_step++;	//ÏÂÒ»²½							
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
											Motor1_do_step++;	//ÏÂÒ»²½
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
				//¹ØµôÏßÈ¦Ì×µÄÈÎºÎÍ¨µçĞĞÎª
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
						switch(Motor2_do_step)
						{
							case 1:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?							
								MOTOR2_A_STATE(1);
								MOTOR2_B_STATE(0);
								MOTOR2_C_STATE(0);
								MOTOR2_D_STATE(0);
							case 2:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 3:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?							
								MOTOR2_A_STATE(1);
								MOTOR2_B_STATE(1);
								MOTOR2_C_STATE(0);
								MOTOR2_D_STATE(0);
								break;
							case 4:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 5:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(0);
								MOTOR2_B_STATE(1);
								MOTOR2_C_STATE(0);
								MOTOR2_D_STATE(0);						
								break;
							case 6:
								if(nCalca>1000)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 7:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(0);
								MOTOR2_B_STATE(1);
								MOTOR2_C_STATE(1);
								MOTOR2_D_STATE(0);						
								break;
							case 8:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 9:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(0);
								MOTOR2_B_STATE(0);
								MOTOR2_C_STATE(1);
								MOTOR2_D_STATE(0);
								break;
							case 10:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 11:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(0);
								MOTOR2_B_STATE(0);
								MOTOR2_C_STATE(1);
								MOTOR2_D_STATE(1);
								break;
							case 12:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 13:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(0);
								MOTOR2_B_STATE(0);
								MOTOR2_C_STATE(0);
								MOTOR2_D_STATE(1);
								break;
							case 14:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 15:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(1);
								MOTOR2_B_STATE(0);
								MOTOR2_C_STATE(0);
								MOTOR2_D_STATE(1);
								break;
							case 16:
								Motor2_do_step=1;
								xiii++;
								break;
						}

			}
			else
			{
						switch(Motor2_do_step)
						{
							case 1:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?							
	MOTOR2_A_STATE(1);
	MOTOR2_B_STATE(0);
	MOTOR2_C_STATE(0);
	MOTOR2_D_STATE(1);
							case 2:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 3:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?							
	MOTOR2_A_STATE(0);
	MOTOR2_B_STATE(0);
	MOTOR2_C_STATE(0);
	MOTOR2_D_STATE(1);
								break;
							case 4:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 5:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
	MOTOR2_A_STATE(0);
	MOTOR2_B_STATE(0);
	MOTOR2_C_STATE(1);
	MOTOR2_D_STATE(1);				
								break;
							case 6:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 7:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
	MOTOR2_A_STATE(0);
	MOTOR2_B_STATE(0);
	MOTOR2_C_STATE(1);
	MOTOR2_D_STATE(0);				
								break;
							case 8:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 9:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
	MOTOR2_A_STATE(0);
	MOTOR2_B_STATE(1);
	MOTOR2_C_STATE(1);
	MOTOR2_D_STATE(0);
								break;
							case 10:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 11:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
	MOTOR2_A_STATE(0);
	MOTOR2_B_STATE(1);
	MOTOR2_C_STATE(0);
	MOTOR2_D_STATE(0);
								break;
							case 12:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 13:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
	MOTOR2_A_STATE(1);
	MOTOR2_B_STATE(1);
	MOTOR2_C_STATE(0);
	MOTOR2_D_STATE(0);
								break;
							case 14:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 15:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
	MOTOR2_A_STATE(1);
	MOTOR2_B_STATE(0);
	MOTOR2_C_STATE(0);
	MOTOR2_D_STATE(0);
								break;
							case 16:
								Motor2_do_step=1;
								break;
						}
			}
	}
	else
	{
				//¹ØµôÏßÈ¦Ì×µÄÈÎºÎÍ¨µçĞĞÎª
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(0);
	}
}
