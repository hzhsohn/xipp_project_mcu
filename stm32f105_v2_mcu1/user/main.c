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

//�Ƿ��Զ�������
unsigned char g_isAutomation=1;

unsigned char g_cCleanCurrentSence=0;  

//����ʱ�����
#define DEF_TIME_MS_DELAY		100

/**************/
//�̵����߼��ض���
int isOpenDry=0;


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
//
int isTextPOPO=0;
int isTextXUXU=0;

//�Ƕ� 
extern unsigned char jiaodu[2];
//����
extern unsigned char cHeartJump;
//��ˮ��
char bSewageHeight=0;
//��ˮ̫��
char bCleanWaterLow=0;
//��ˮ��λ
char bSewageSuitable=0;
//����ʱ������
TagTimeingSetting g_tmeSetting={0};


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
static int baonianCurrentState=0;
//
void senceDelay(int*nCalca,int*ppxxStep,int jmpValue,int delay_ms,int ezhCleanSencePOS);

//
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

//�ر��������
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

//�жϳ���
void allOutClose()
{	
		isCleanRuning=0;
		allSenceClose();
		isTextPOPO=0;
		isTextXUXU=0;
}
////////////////////////////////////////////////////////////////
//������ʱ
void senceDelayToValue(int*nCalca,int*ppxxStep,int jmpValue,int delay_ms)
{
	if((*nCalca) > delay_ms) 
	{
			*nCalca=0;
			(*ppxxStep)++;
	}
	else
	{
			if(0==isCleanRuning)//�ж�
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
			if(0==isCleanRuning)//�ж�
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

//��ʾ��Ϣָ��
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

			//��ʼ��FLASH����
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
	//��ȡFALSH����
	setFlashData();
  //-----------------------------------------

	//���Լ̵������߼�	
	#if 0
			allOutClose();
			RelayTest();
			allOutClose();
	#endif 
	
	//���Ź�
	//watchdog_init();
	
	while(1)
	{
		//���Ź�
		//watchdog_action();
		//
		pdxbPooPoo=dxbPooPoo;
		pdxbXuXu=dxbXuXu;
		//
		//---------------------
		//����1		������
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
		//����2		��ϴ��
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
		//����3		��ɼ�
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
		//����4		������
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
		
		//����5		��Ħ��
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
						ppxxStep=0; //��λ����
			}
        break;
    }
		//����6		��ů��
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
						ppxxStep=0; //��λ����
			}
        break;
    }
		
		//����7		������
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
		//����8		��������
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
		if(kk>=10 && xiii>=xiiiLimit && xiii2>=xiiiLimit) //����0.1��ִ��һ��,�Ҳ�����������ж���
		{
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
							if(isCheckWaterSensorErr>10) //��������ë��̫��ص����ȼ̵���
							{
								//��������ë����.�ص��̵���
								if(g_cCleanCurrentSence==0)
								{
											_unit13(0);
								}
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
									 _unit12(1);  //�����ȵ�Ԫ
								}
								else
								{
									 _unit12(0);	//�����ȵ�Ԫ
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
								_unit12(0); //�����ȵ�Ԫ
						}
					}

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
					//��ˮ����λ
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
		if(ezhCleanSence1==(g_cCleanCurrentSence)) //��
		{
				litteSenceRunXuXu();
		}
		else if(ezhCleanSence2==(g_cCleanCurrentSence)) //ʺ
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
							allSenceClose();
							aurtEventUnitSence(ezhCleanSence3,1);
							g_cCleanCurrentSence=ezhCleanSence3;
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10);
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
							allSenceClose();				
							aurtEventUnitSence(ezhCleanSence4,1);
							g_cCleanCurrentSence=ezhCleanSence4;
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:	
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*10);
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
						
						default: //���
							aurtEventUnitSence(ezhCleanSence6,0);
							allOutClose();
							g_cCleanCurrentSence=0;  		//������λ
							ppxxStep=0;
							break;
					}
}

/********************************
//��Ħ
*********************************/
void litteSenceRunAnMo(void)
{

}

/********************************
//��ů
*********************************/
void litteSenceRunBaoNang(void)
{
	
}

