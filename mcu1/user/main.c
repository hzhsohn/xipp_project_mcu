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
//�Ƿ��Զ�������
unsigned char g_isAutomation=1;

unsigned char g_cCleanCurrentSence=0;  

//����ʱ�����
#define DEF_TIME_MS_DELAY		50

/**************/
//�̵����߼��ض���
int isOpenDry=0;

#define _unit1(x) 							RELAY7_STATE(x)		//С��ת��
#define _unit2(x) 							RELAY6_STATE(x)		//���ת��
#define _unit3(x) 							RELAY11_STATE(x)	//����ת��
#define _unit4(x) 		 					RELAY12_STATE(x)	//������ת��
#define _unit5(x) 							RELAY10_STATE(x)	//������ת��
#define _unit6(x) 							RELAY1_STATE(x)		//������
#define _unit7(x) 							RELAY9_STATE(x)		//������
#define _unit8(x) 				 			RELAY3_STATE(x) 	//��ˮ��
#define _unit9(x) 							RELAY2_STATE(x)		//ɱ��������
#define _unit10(x) 				 			RELAY8_STATE(x)		//����
#define _unit11(x)							RELAY13_STATE(x) 	//ˮ����
#define _unit12(x) 	 						RELAY4_STATE(x)		//������
#define _unit13(x) 							RELAY5_STATE(x)		//ɱ����ת��

//
#define udoDry(x)						 			_unit5(x);_unit6(x);_unit10(x);isOpenDry=x		//��ɳ���
#define udoSterilization(x) 			_unit5(x);_unit9(x);_unit10(x);_unit13(x)			//ɱ��
#define udoWaterHeating(x) 				_unit11(x)																		//ˮ���ȳ���
#define udoXuXuFlush(x) 					_unit1(x);_unit7(x);_unit8(x)									//С���ϴ
#define udoPoPoFlush(x) 					_unit2(x);_unit7(x);_unit8(x)									//����ϴ
#define udoKuZiCongQi(x) 					_unit4(x);_unit10(x)													//���ӳ���
#define udoBedCongQi(x) 	 				_unit3(x);_unit10(x)													//�������
#define udoDeodorization(x) 			_unit7(x);_unit12(x)													//����
#define udoKuZiHuanQi(x) 				 	_unit5(x);_unit10(x) 													//���ӻ���
#define udoXuPooCollect(x) 				_unit7(x);_unit12(x)													//ʺʺ�����ռ�
#define udoJiaoPan(x)             jaopan=x																			//����

/**************/
//�������߼��ض���
#define cgqSewageHeight  					SENSOR1_STATE()?1:0 //��ˮ��
#define cgqCleanWaterLow  				SENSOR2_STATE()?0:1 //��ˮ��
#define cgqSewageSuitable  				SENSOR3_STATE()?1:0 //��ˮ��λ

//��С����
#define dxbPooPoo  				SENSOR4_STATE()?0:1    //ʺ
#define dxbXuXu	  				SENSOR5_STATE()?0:1    //��

//--
//�¶�
int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0,rGasTemperature=0,rGasTemp=0;
s16 rTrueWaterTemp=0,rTrueGasTemp=0;
int isWaterTooHot=0;
int isGasTooHot=0;
int isCheckWaterSensorErr=0; //ˮ�·���������
int isCheckGasSensorErr=0;//ˮ�·���������
int isCheckBedCQSensorErr=0;//��ѹ����������
int isCheckDZCQSensorErr=0;	//��ѹ����������

//��ѹ
u16_t rPressure=0,rPressureTmp=0,rPressure2=0,rPressure2Tmp=0;
u16_t rTruePressure1=0,rTruePressure2=0;
//ʺʺ����ķ�����
int rPoopoDD=0;
int rXuxuDD=0;
int pdxbPooPoo;
int pdxbXuXu;

//�Ƕ� 
extern unsigned char jiaodu[2];
//����
unsigned char cHeartJump=0;
//��ˮ��
char bSewageHeight=0;
//��ˮ̫��
char bCleanWaterLow=0;
//��ˮ��λ
char bSewageSuitable=0;
//ʱ�����ֵ
extern TagTimeingSetting g_tmeSetting;

//�ж�����chart
int isCleanRuning=0;
int ppxxStep=0;

//����ͷ���
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

//��Ħ״̬
static int anmiCurrentState=0;
//
void senceDelay(int*nCalca,int*ppxxStep,int delay_ms,int ezhCleanSencePOS);
////////////////////////////////////////////////////////////////

void LitteSenceRun(void);
/*
	ezhCleanSence1�Զ���С��																					
	ezhCleanSence2�Զ������ 
	ezhCleanSence3����
	ezhCleanSence4��ϴ
	ezhCleanSence5���
	ezhCleanSence6����
	ezhCleanSence7��Ħ
	ezhCleanSence8��ů
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
	 _unit1(0); 									//С��ת��
	 _unit2(0); 									//���ת��
	 _unit3(0); 									//����ת��
	 _unit4(0); 		 							//������ת��
	 _unit5(0); 									//������ת��
	 _unit6(0); 									//������
	 _unit7(0); 									//������
	 _unit8(0); 				 			 		//��ˮ��
	 _unit9(0); 									//ɱ��������
	 _unit10(0); 				 					//����
	 _unit11(0);							 		//ˮ����
	 _unit12(0); 	 								//������
	 _unit13(0); 									//ɱ����ת��
		jaopan=0;
}
////////////////////////////////////////////////////////////////
//������ʱ
void senceDelay(int*nCalca,int*ppxxStep,int delay_ms,int ezhCleanSencePOS)
{
	if((*nCalca) > delay_ms) 
	{
			*nCalca=0;
			(*ppxxStep)++; g_cCleanCurrentSence=ezhCleanSencePOS | (*ppxxStep);
	}
	else
	{
			if(0==isCleanRuning)//�ж�
			{g_cCleanCurrentSence=0;(*nCalca)=0;allOutClose();}
			(*nCalca)++;
	}
}
////////////////////////////////////////////////////////////////

//�ύ��ǰ״̬
void aurtEventStatus()
{
		uchar dst_buf[50]={0};
		unsigned char cbuf[23]={0};
		int myDataLen=0;
		//
		cbuf[0]=0;
		
		cbuf[1]=g_isAutomation;
		cbuf[2]=g_cCleanCurrentSence;
				
		cbuf[3]=bSewageHeight;//��������ˮ��
		cbuf[4]=bCleanWaterLow;//��������ˮ̫С
		cbuf[5]=bSewageSuitable;//��������ˮ��δ��װ��λ
		
		cbuf[6]=cHeartJump; //����
		cbuf[7]=0;
		
		cbuf[8]=rTrueWaterTemp&0xff; //ˮ�¶�
		cbuf[9]=rTrueWaterTemp>>8;
		
		cbuf[10]=rTrueGasTemp&0xff; //���¶�
		cbuf[11]=rTrueGasTemp>>8;
		
		cbuf[12]=rTruePressure1&0xff; //�㵵��ѹ
		cbuf[13]=rTruePressure1>>8;
		
		cbuf[14]=rTruePressure2&0xff; //������ѹ
		cbuf[15]=rTruePressure2>>8;
		
		cbuf[16]=isWaterTooHot;//���Ϊ1����������,��˼����"���ȹ��ܲ�֪������������.."
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
			1//�̵�����������
			2//�̵����������
			3//�̵�����������
			4//�̵����������
			5//�̵�������ϴ����
			6//�̵���С������
			7//�̵���С���ϴ����
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
	
	//���Լ̵������߼�	
	#if 0
			allOutClose();
			RelayTest();
			allOutClose();
	#endif 
	
	//���Ź�
	//watchdog_init();
	allOutClose();
	
	STM32F1_UART3SendDataS("123",3);
	
	//-------------------------------
	//startup system delay-----------
	STM32_Delay_ms(10000);
	//
	LED1_ON;LED2_ON;LED3_ON;
		
	//��ȡ����
	FLASH_ReadByte(STARTADDRFLAG ,(uint8_t*)binFlag,4);
	FLASH_ReadByte(STARTADDR ,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));
	
if(!(binFlag[0]=='a' && binFlag[1]=='b' && binFlag[2]=='c' && binFlag[3]=='d'))
{
		binFlag[0]='a';
		binFlag[1]='b';
		binFlag[2]='c';
		binFlag[3]='d';

		g_tmeSetting.pooDelay=1;					  //��ʺ����������� ,��λ����
		g_tmeSetting.xuxuDelay=10;				  //��ʺ����������� ,��λ��
		g_tmeSetting.pooFlush=30;					  //ʺʺ��ϴ  ,	��λ��
		g_tmeSetting.xuxuFlush=10;				  //�����ϴ  	��λ ��
		g_tmeSetting.pooDry=2;      		  	//ʺʺ���ʱ�� ��λ ����
		g_tmeSetting.xuxuDry=1;					  	//������ʱ�� ��λ ����
		g_tmeSetting.pooSterilize=10;			  //ʺʺ����ʱ�� ��λ ��
		g_tmeSetting.xuxuSterilize=10;		  //��������ʱ�� ��λ ��
		g_tmeSetting.crotchPressure=13;			//�㵵��ѹ ��λ 100��ѹ����
		g_tmeSetting.bedPressure=13;   			//�������ѹ  ��λ 100��ѹ����
		g_tmeSetting.waterTemperature=38;		//���ˮ��   			��λ���϶�
		g_tmeSetting.airTemperature=50;  		//��ͺ���¶�   	��λ���϶�
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
		//���Ź�
		//watchdog_action();
		//
		TouchKey_Scan();
		//---------------------
		//����
		//1������
		//2��ϴ��
		//3��ɼ�
		//4������
		//5��Ħ��
		//6��ů��
		//7������
		//8��������
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
					ppxxStep=0; //��λ����
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
		//���������������		
		//if(rTrueWaterTemp>=g_tmeSetting.waterTemperature*10) //�������ˮ�²���������
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
		//�����û��ʺ������
		//if(rTrueWaterTemp>=g_tmeSetting.waterTemperature*10)  //�������ˮ�²���������
		{
					if(dxbPooPoo)
					{
						rPoopoDD++;
						if(rPoopoDD>2000)
						{
								if(0==g_cCleanCurrentSence && g_isAutomation)//����ִ����
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
		if(kk>=10 && xiii>=xiiiLimit && xiii2>=xiiiLimit) //����0.1��ִ��һ��,�Ҳ�����������ж���
		{
					//---------------------//
					//��������,��������,��֪����ɶ������
					switch(g_nMPU_DO)
					{
					case 0:
						break;
					case 1://��
						break;
					case 2://��
						break;
					}
					//------------------------------------------------------------------
					//ˮ�¼���
					rWaterTemp=DS18B20_Get_Temp();
					if(rWaterTemp<2000 && rWaterTemp> -200) //����λ
					{
						ntmp=rWaterTemp-rWaterTemperature;
						if(ntmp<20 && ntmp>-20)	//����ͻ�����
						{
							isWaterTooHot=0;							
							if(rWaterTemp > 60*10) //�������������˰�,̫���˾��Ǽ�������������.
							{
								//ˮ̫����.�������ڸ�����λ����,֪ͨ��ʿС����,����������
								isWaterTooHot=1;
							}
							else if(rWaterTemp<g_tmeSetting.waterTemperature*10 && 0==bCleanWaterLow) //Ĭ��С��40�Ⱦͼ���
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
						if(isCheckWaterSensorErr>10) //��������ë��̫��ص����ȼ̵���
						{
							//��������ë����.�ص��̵���
							if(g_cCleanCurrentSence==0)
							{	udoWaterHeating(0);}
						}
					}
	
					//-------------------------------------------------------------------
					//��������,ʵʱ��������
					rGasTemp=DS18B20_Get_Temp1(); 
					if(rGasTemp<2000 && rGasTemp> -200) //����λ
					{
						ntmp=rGasTemp-rGasTemperature;
						if(ntmp<20 && ntmp>-20) //����ͻ�����
						{
							isGasTooHot=0;							
							if(rGasTemp > 60*10) //�������������˰�,̫���˾��Ǽ�������������.
							{
								//����̫����.�������ڸ�����λ����,֪ͨ��ʿС����,����������
								isGasTooHot=1;
							}
							
							if(isOpenDry && rGasTemp<g_tmeSetting.airTemperature*10 ) //50���Һ濪�ص�ʱ��Ŵ���
							{
								_unit6(1);  //�����ȵ�Ԫ
							}
							else
							{
								_unit6(0);	//�����ȵ�Ԫ
							}
							rTrueGasTemp=rGasTemp;
							isCheckGasSensorErr=0;
						}
						rGasTemperature=rGasTemp;
					}
					else
					{
						isCheckGasSensorErr++;						
						if(isCheckGasSensorErr>10) //����������ë���ص����ȼ̵���
						{
							//��������ë����.�ص��̵���
							_unit6(0); //�����ȵ�Ԫ
						}
					}

					//------------------------------------------------------------------
					//�㵵��ѹ
					rPressureTmp = Get_Adc_Average(10);
					ntmp=rPressureTmp-rPressure;
					if(ntmp<60 && ntmp>-60) //����ͻ�����
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
						if(isCheckDZCQSensorErr>10) //����������ë���ص��̵���
						{
							if(g_cCleanCurrentSence==0)
							{	udoKuZiCongQi(0);}
						}
					}
					rPressure=rPressureTmp;
					
					//------------------------------------------------------------------
					//������ѹ
					rPressure2Tmp= Get_Adc2_Average(10);
					ntmp=rPressure2Tmp-rPressure2;
					if(ntmp<60 && ntmp>-60) //����ͻ�����
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
						if(isCheckBedCQSensorErr>10) //��������ë��̫��صȼ̵���
						{
							if(g_cCleanCurrentSence==0)
							{	udoBedCongQi(0);}
						}
					}
					rPressure2=rPressure2Tmp;

					//------------------------------------------------------------------
					//��ˮ��
					if(cgqSewageHeight)
					{
							bSewageHeight=1;
					}
					else
					{
							bSewageHeight=0;
					}

					//------------------------------------------------------------------
					//��ˮ̫��
					if(cgqCleanWaterLow)
					{
							bCleanWaterLow=1;
					}
					else
					{
							bCleanWaterLow=0;
					}

					//------------------------------------------------------------------
					//��ˮ��λ
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
		//��ʺϴ����
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
		if(ezhCleanSence1==(g_cCleanCurrentSence&0xf0) && g_isAutomation) //��
		{
				if(0==(g_cCleanCurrentSence&0x0f))
				{ppxxStep=0;}				
				litteSenceRunXuXu();
		}
		else if(ezhCleanSence2==(g_cCleanCurrentSence&0xf0) && g_isAutomation) //ʺ
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
				//û�г���
				g_cCleanCurrentSence=0;
				
		}		
}


/*********************************************************

----���г���----

***********************************************************/
void litteSenceRunXuXu()
{					
					static int nCalca=0;	
					switch(ppxxStep)
					{
						case 0:
							aurtEventUnitSence(ezhCleanSence1,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//��һ��
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*30/*g_tmeSetting.xuxuDelay*/,ezhCleanSence1);
							break;
						case 2:
							udoXuXuFlush(1);//########### С���ϴ
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//��һ��
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*5,ezhCleanSence1);
							break;
						case 4:
							udoXuXuFlush(0);//########### С���ϴ
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;	//��һ��
							udoXuPooCollect(1);//############# ʺ���ռ���
							break;
						case 5:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*5/*g_tmeSetting.xuxuFlush*/,ezhCleanSence1);
							break;
						case 6:
							udoXuPooCollect(0);//############# ʺ���ռ���
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence1 | ppxxStep;//��һ��
							udoDry(1);//########### ���
							break;
						case 7:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50,ezhCleanSence1);
							break;
						case 8:							
							udoDry(0);//########### ���
							nCalca=0;
							ppxxStep++;
							break;
						default: //���
							aurtEventUnitSence(ezhCleanSence1,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//������λ
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
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;	//��һ��
							udoJiaoPan(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*30/*g_tmeSetting.pooDelay * 60*/,ezhCleanSence2);
							break;
						case 2:
							udoPoPoFlush(1);//########### ����ϴ
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;//��һ��
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*4,ezhCleanSence2);
							break;
						case 4:
							udoPoPoFlush(0);//########### ����ϴ
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;	//��һ��
							udoXuPooCollect(1);//############# ʺ���ռ���
							break;
						case 5:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*20/*g_tmeSetting.pooFlush*/,ezhCleanSence2);
							break;
						case 6:		
							udoXuPooCollect(0);//############# ʺ���ռ���
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							udoPoPoFlush(1);//########### ����ϴ
							break;
						case 7:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*5,ezhCleanSence2);
							break;
						case 8:
							udoPoPoFlush(0);//########### ����ϴ
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
						
							udoDry(1);//########### ���
							break;
						case 9:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50/*g_tmeSetting.pooDry*10*/,ezhCleanSence2);
							break;
						case 10:
							udoDry(0);//########### ���
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence2 | ppxxStep;
							break;

						default: //���
							aurtEventUnitSence(ezhCleanSence2,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//������λ
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
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;	//��һ��
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*g_tmeSetting.pooDelay * 60,ezhCleanSence3);
							break;
						case 2:
							udoXuPooCollect(1);//############# ʺ���ռ���
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;//��һ��
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10,ezhCleanSence3);
							break;
						case 4:
							udoPoPoFlush(1);//########### ����ϴ
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;	//��һ��
							break;
						case 5:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*g_tmeSetting.pooFlush,ezhCleanSence3);
							break;
						case 6:		
							udoPoPoFlush(0);//########### ����ϴ
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 7:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10,ezhCleanSence3);
							break;
						case 8:
							udoXuPooCollect(0);//############# ʺ���ռ���
							udoDry(1);//########### ���
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 9:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*g_tmeSetting.pooDry*10,ezhCleanSence3);
							break;
						case 10:
							udoDry(0);//########### ���
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 11:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3,ezhCleanSence3);
							break;
						case 12:
							udoDry(1);//########### ���
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						case 13:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*g_tmeSetting.pooDry*10,ezhCleanSence3);
							break;
						case 14:
							udoDry(0);//########### ���
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence3 | ppxxStep;
							break;
						
						default: //���
							aurtEventUnitSence(ezhCleanSence3,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//������λ
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
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;	//��һ��
						  udoPoPoFlush(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10,ezhCleanSence4);
							break;
						case 2:	
							udoPoPoFlush(0);
						  udoXuPooCollect(1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;//��һ��
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15,ezhCleanSence4);
							break;
						case 4:	
							udoXuPooCollect(0);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;//��һ��
							udoDry(1);
							break;
						case 5:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50,ezhCleanSence4);
							break;
						case 6:	
							udoDry(0);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence4 | ppxxStep;//��һ��
							break;
						
						default: //���
							aurtEventUnitSence(ezhCleanSence4,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//������λ
							ppxxStep=0;
							break;
					}
}

/********************************
//���
*********************************/
void litteSenceRunHongGan(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:
							aurtEventUnitSence(ezhCleanSence5,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence5 | ppxxStep;	//��һ��
						
							udoDry(1);//########### ���
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*50,ezhCleanSence5);
							break;
						case 2:
							udoDry(0);//########### ���
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence5 | ppxxStep;//��һ��
							break;
						
						default: //���
							aurtEventUnitSence(ezhCleanSence5,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//������λ
							ppxxStep=0;
							break;
					}
}

/********************************
//����
*********************************/
void litteSenceRunChuQun(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:							
							aurtEventUnitSence(ezhCleanSence6,1);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;	//��һ��

							_unit5(1);_unit9(1);_unit10(1);_unit13(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3,ezhCleanSence6);
							break;
						case 2:
							_unit7(1);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//��һ��
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3,ezhCleanSence6);
							break;
						case 4:
							_unit7(0);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//��һ��
							break;
						case 5:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*45,ezhCleanSence6);
							break;
						case 6:
							_unit7(1);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//��һ��
							break;
						case 7:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3,ezhCleanSence6);
							break;
						case 8:
							_unit7(0);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//��һ��
							break;
						case 9:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*45,ezhCleanSence6);
							break;
						
						case 10:
							_unit7(1);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//��һ��
							break;
						case 11:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3,ezhCleanSence6);
							break;
						case 12:
							_unit7(0);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//��һ��
							break;
						
						case 13:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*33,ezhCleanSence6);
							break;
						
						case 14:
							_unit5(1);_unit9(1);_unit10(1);_unit13(1);
							nCalca=0; ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//��һ��
							break;
						
						default: //���
							aurtEventUnitSence(ezhCleanSence6,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//������λ
							ppxxStep=0;
							break;
					}
					
				/*static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:							
							aurtEventUnitSence(ezhCleanSence6,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;	//��һ��

							udoSterilization(1); //########### ����
						case 1:
							senceDelay(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10,ezhCleanSence6);
							break;
						case 2:
							udoSterilization(0); //########### ����
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence6 | ppxxStep;//��һ��
							break;
						default: //���
							aurtEventUnitSence(ezhCleanSence6,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//������λ
							ppxxStep=0;
							break;
					}*/
}

/********************************
//��Ħ
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
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;	//��һ��
							ANMO1_STATE(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,15,ezhCleanSence7);
							break;
						case 2:
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;//��һ��
							ANMO1_STATE(0);
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,30,ezhCleanSence7);
							break;
						//-----------------------------------------------	
						case 4:							
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;	//��һ��
							ANMO1_STATE(1);
						case 5:
							senceDelay(&nCalca,&ppxxStep,15,ezhCleanSence7);
							break;
						case 6:	
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;//��һ��
							ANMO1_STATE(0);
							break;
						case 7:
							senceDelay(&nCalca,&ppxxStep,30,ezhCleanSence7);
							break;
						//-----------------------------------------------	
							
						case 8:							
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;	//��һ��
							ANMO1_STATE(1);
						case 9:
							senceDelay(&nCalca,&ppxxStep,15,ezhCleanSence7);
							break;
						case 10:	
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;//��һ��
							ANMO1_STATE(0);
							break;
						case 11:
							senceDelay(&nCalca,&ppxxStep,30,ezhCleanSence7);
							break;
							/*
						//-----------------------------------------------
							//��ʱ
							case 12:
							if(nCalca>500)
							{
									nCalca=0;
									ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;
							}
							else
							{
									if(0==isCleanRuning)//�ж�
									{
										//�ж��ź�
										ANMO1_STATE(1);
										STM32_Delay_ms(200);
										ANMO1_STATE(0);
										//
										g_cCleanCurrentSence=0;nCalca=0;allOutClose();
									}
									nCalca++;
							}
							break;*/
						default: //���
							aurtEventUnitSence(ezhCleanSence7,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//������λ
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
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;	//��һ��
							ANMO1_STATE(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,15,ezhCleanSence7);
							break;
						case 2:	
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence7 | ppxxStep;//��һ��
							ANMO1_STATE(0);
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,30,ezhCleanSence7);
							break;
						default: //���
							aurtEventUnitSence(ezhCleanSence7,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//������λ
							ppxxStep=0;
							break;
					}
		}
}

/********************************
//��ů
*********************************/
void litteSenceRunBaoNang(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:
							aurtEventUnitSence(ezhCleanSence8,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence8 | ppxxStep;	//��һ��
							BAONAN_STATE(1);
						case 1:
							senceDelay(&nCalca,&ppxxStep,10,ezhCleanSence8);
							break;
						case 2:		
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSence8 | ppxxStep;//��һ��
							BAONAN_STATE(0);
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,300,ezhCleanSence8);
							break;
						default: //���
							aurtEventUnitSence(ezhCleanSence8,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//������λ
							ppxxStep=0;
							break;
					}
}

//--------------------------------------------------------------------------
//���鳡��
void litteSenceRunA(void)
{
				static int nCalca=0;
				switch(ppxxStep)
					{
						case 0:
							aurtEventUnitSence(ezhCleanSenceA,1);
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceA | ppxxStep;	//��һ��
							
						case 1:
							senceDelay(&nCalca,&ppxxStep,10,ezhCleanSenceA);
							break;
						case 2:		
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceA | ppxxStep;//��һ��
							
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,300,ezhCleanSenceA);
							break;
						default: //���
							aurtEventUnitSence(ezhCleanSenceA,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//������λ
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
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceB | ppxxStep;	//��һ��
							
						case 1:
							senceDelay(&nCalca,&ppxxStep,10,ezhCleanSenceB);
							break;
						case 2:		
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceB | ppxxStep;//��һ��
							
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,300,ezhCleanSenceB);
							break;
						default: //���
							aurtEventUnitSence(ezhCleanSenceB,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//������λ
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
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceC | ppxxStep;	//��һ��
							
						case 1:
							senceDelay(&nCalca,&ppxxStep,10,ezhCleanSenceC);
							break;
						case 2:		
							nCalca=0;
							ppxxStep++; g_cCleanCurrentSence=ezhCleanSenceC | ppxxStep;//��һ��
							
							break;
						case 3:
							senceDelay(&nCalca,&ppxxStep,300,ezhCleanSenceC);
							break;
						default: //���
							aurtEventUnitSence(ezhCleanSenceC,0);
							allOutClose();						
							g_cCleanCurrentSence=0;  		//������λ
							ppxxStep=0;
							break;
					}
}

