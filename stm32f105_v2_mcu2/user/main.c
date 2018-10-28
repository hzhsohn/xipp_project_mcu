#include "system_init.h"
#include "Stm32f1_uart1.h"
#include "Stm32f1_uart2.h"
#include "Stm32f1_uart3.h"
#include "InputDrive.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1.h"
#include "Stm32f1_ADC2.h"
#include "Stm32f1_ADC3.h"
#include "Stm32f1_ADC4.h"
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

//����ʱ�����
#define DEF_TIME_MS_DELAY		100

/**************/
//�������߼��ض���
#define cgqWST1  					SENSOR1_STATE()?1:0 //��ˮͰ��

//��ѹ
u16 rPressure[4]={0};
u16 rPressureTmp[4]={0};
u16 rTruePressure[4]={0};
int isCheckQiYaErr[4]={0};

//����ʱ������
TagTimeingSetting g_tmeSetting={0};

//�����ж�����
int isCleanRuning=0;
int ppxxStep=0;

//��������
void btnEvent(void);
void qiqiqiYayaya(void);

//����
void senceDelayToValue(int*nCalca,int*ppxxStep,int jmpValue,int delay_ms);
void senceDelayToNext(int*nCalca,int*ppxxStep,int delay_ms);
void senceNext(int*nCalca,int*ppxxStep);
//
void LitteSenceRun(void);
/*
	ezhCleanSence1 1��																				
	ezhCleanSence2 2�� 
*/
void litteSenceRun1(void);
void litteSenceRun2(void);
void litteSenceRun3(void);
void litteSenceRun4(void);

//---------------------
//��������
EzhKeyEvent ev;
EzhKeyState btn1;
EzhKeyState btn2;
EzhKeyState btn3;
EzhKeyState btn4;

//�ر��������
void allSenceClose()
{
	 _unit16(0);
	 _unit17(0);
	 _unit18(0);
	 _unit19(0);
	 _unit20(0);
	 _unit21(0);
	 _unit22(0);
	 _unit23(0);
	 _unit24(0);
	 _unit25(0);
	 _unit26(0);
	 _unit27(0);
	 _unit10(0);
}

//�жϳ���
void allOutClose()
{	
		isCleanRuning=0;
		allSenceClose();
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
			g_tmeSetting.a=1;					  //
			g_tmeSetting.b=1;					  //
				
			FLASH_WriteByte(STARTADDRFLAG,(uint8_t*)binFlag,4);
			FLASH_WriteByte(STARTADDR,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));

	}
}

int main(void)
{
	//-----------------------------------------
	//��ȡFALSH����
	setFlashData();
  //-----------------------------------------
	
	STM32_Delay_init();
	STM32F1_UART1_Init(19200);  //�Խ�MCU1
	//STM32F1_UART2_Init(230400);
	//STM32F1_UART3_Init(9600);
	
	Adc_Init();
	Adc2_Init();	
	Adc3_Init();
	Adc4_Init();
	
	//Motor_Init();
	Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	InputDriveInit();
	zhSCM_GPIOConfig(); 

	OutputDriveInit();
/*
	//���
	MADA1A_STATE(1);
	MADA1B_STATE(0);
	
	MADA1A_STATE(0);
	MADA1B_STATE(1);

	MADA1A_STATE(0);
	MADA1B_STATE(0);
	
	//---------------------	
	MADA2A_STATE(1);
	MADA2B_STATE(0);
	
	MADA2A_STATE(0);
	MADA2B_STATE(1);

	MADA2A_STATE(0);
	MADA2B_STATE(0);
*/

//--------------------
RELAY1_STATE(1);
BAINA_STATE(1);
ANMO4_STATE(1);
ANMO3_STATE(1);
ANMO2_STATE(1);
ANMO1_STATE(1);
BAINA_STATE(0);
ANMO4_STATE(0);
ANMO3_STATE(0);
ANMO2_STATE(0);
ANMO1_STATE(0);

	//���Լ̵������߼�	
	#if 0
			allOutClose();
			RelayTest();
			allOutClose();
	#endif 
	
	//���Ź�
	//watchdog_init();
	
	zhSCM_initKeyState(&btn1);
	zhSCM_initKeyState(&btn2);
	zhSCM_initKeyState(&btn3);
	zhSCM_initKeyState(&btn4);

	while(1)
	{
		//���Ź�
		//watchdog_action();
		//
		btnEvent();

		//------------------------------------------------------------------
		//��ѹ����
		qiqiqiYayaya();

		//------------------------------------------------------------------
		//��������
		if(kk_1ms)
		{
					LitteSenceRun();
					kk_1ms=0;
		}
	}
}

void btnEvent(void)
{
//---------------------
		//����1		����
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
		//����2		�ҷ���
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
		
		//����3		�ָ�
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
		//����4		�ָ�
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
}
void qiqiqiYayaya(void)
{
				int ntmp;
	
				//��ѹ1	
				rPressureTmp[0]=Get_Adc2_Average(10);
				ntmp=rPressureTmp[0]-rPressure[0];
				if(ntmp<60 && ntmp>-60) //����ͻ�����
				{
						rTruePressure[0]=rPressureTmp[0];
						isCheckQiYaErr[0]=0;
				}
				else
				{
					isCheckQiYaErr[0]++;						
					if(isCheckQiYaErr[0]>10) //��������ë��̫��صȼ̵���
					{
						rTruePressure[0]=-1;
					}
				}
				rPressure[0]=rPressureTmp[0];

				//------------------------------------------------------------------
				//��ѹ2
				rPressureTmp[1]=Get_Adc2_Average(10);
				ntmp=rPressureTmp[1]-rPressure[1];
				if(ntmp<60 && ntmp>-60) //����ͻ�����
				{
						rTruePressure[1]=rPressureTmp[1];
						isCheckQiYaErr[1]=0;
				}
				else
				{
					isCheckQiYaErr[1]++;						
					if(isCheckQiYaErr[1]>10) //��������ë��̫��صȼ̵���
					{
						rTruePressure[1]=-1;
					}
				}
				rPressure[1]=rPressureTmp[1];
				
				//------------------------------------------------------------------
				//��ѹ3
				rPressureTmp[2]=Get_Adc3_Average(10);
				ntmp=rPressureTmp[2]-rPressure[2];
				if(ntmp<60 && ntmp>-60) //����ͻ�����
				{
						rTruePressure[2]=rPressureTmp[2];
						isCheckQiYaErr[2]=0;
				}
				else
				{
					isCheckQiYaErr[2]++;						
					if(isCheckQiYaErr[2]>10) //��������ë��̫��صȼ̵���
					{
						rTruePressure[2]=-1;
					}
				}
				rPressure[2]=rPressureTmp[2];
								
				//------------------------------------------------------------------
				//��ѹ4
				rPressureTmp[3]=Get_Adc4_Average(10);
				ntmp=rPressureTmp[3]-rPressure[3];
				if(ntmp<60 && ntmp>-60) //����ͻ�����
				{
						rTruePressure[3]=rPressureTmp[3];
						isCheckQiYaErr[3]=0;
				}
				else
				{
					isCheckQiYaErr[3]++;						
					if(isCheckQiYaErr[3]>10) //��������ë��̫��صȼ̵���
					{
						rTruePressure[3]=-1;
					}
				}
				rPressure[3]=rPressureTmp[3];
				
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
		else if(ezhCleanSence3==(g_cCleanCurrentSence))
		{
				litteSenceRun3();
		}
		else if(ezhCleanSence4==(g_cCleanCurrentSence))
		{
				litteSenceRun4();
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
void litteSenceRun1(void)
{					
					static int nCalca=0;	
					switch(ppxxStep)
					{
						case 0:				
							allSenceClose();
							g_cCleanCurrentSence=ezhCleanSence1;
							senceNext(&nCalca,&ppxxStep);
							break;
						case 1:	
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*5);
							break;
						case 2:
							_unit26(1);
							_unit10(1);		//MCU1
							_unit17(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 3:	
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*55);
							break;
						case 4:
							_unit26(0);
							_unit10(0);		//MCU1
							_unit17(0);
							_unit25(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 5:	
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15);
							break;
						case 6:
							_unit25(0);
							senceNext(&nCalca,&ppxxStep);
							break;
													
						default: //���
							allOutClose();
							g_cCleanCurrentSence=0;  		//������λ
							ppxxStep=0;
							break;
					}
}

void litteSenceRun2(void)
{				
				static int nCalca=0;
				switch(ppxxStep)
				{
					case 0:				
						allSenceClose();
						g_cCleanCurrentSence=ezhCleanSence2;
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
						break;
					case 2:
							_unit24(1);
							_unit10(1);		//MCU1
							_unit18(1);
						senceNext(&nCalca,&ppxxStep);
							break;
					case 3:	
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*55);
							break;
					case 4:
							_unit24(0);
							_unit10(0);		//MCU1
							_unit18(0);
					senceNext(&nCalca,&ppxxStep);
							break;
					default: //���
						allOutClose();
						g_cCleanCurrentSence=0;  		//������λ
						ppxxStep=0;
						break;
				}
}


void litteSenceRun3(void)
{				
				static int nCalca=0;
				switch(ppxxStep)
				{
					case 0:				
						allSenceClose();
						g_cCleanCurrentSence=ezhCleanSence3;
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
						break;
					case 2:
							_unit26(1);
							_unit10(1);		//MCU1
							_unit19(1);
						senceNext(&nCalca,&ppxxStep);
							break;
						case 3:	
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*55);
							break;
						case 4:
							_unit26(0);
							_unit10(0);		//MCU1
							_unit19(0);
							_unit25(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 5:	
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15);
							break;
						case 6:
							_unit25(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						
					default: //���
						allOutClose();
						g_cCleanCurrentSence=0;  		//������λ
						ppxxStep=0;
						break;
				}
}

void litteSenceRun4(void)
{				
				static int nCalca=0;
				switch(ppxxStep)
				{
					case 0:				
						allSenceClose();
						g_cCleanCurrentSence=ezhCleanSence4;
						senceNext(&nCalca,&ppxxStep);
						break;
					case 1:
						senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*3);
						break;
					case 2:
							_unit24(1);
							_unit10(1);		//MCU1
							_unit20(1);
						senceNext(&nCalca,&ppxxStep);
							break;
						case 3:	
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*55);
							break;
						case 4:
							_unit24(0);
							_unit10(0);		//MCU1
							_unit20(0);
							_unit25(1);
							senceNext(&nCalca,&ppxxStep);
							break;
						case 5:	
							senceDelayToNext(&nCalca,&ppxxStep,DEF_TIME_MS_DELAY*15);
							break;
						case 6:
							_unit25(0);
							senceNext(&nCalca,&ppxxStep);
							break;
						
					default: //���
						allOutClose();
						g_cCleanCurrentSence=0;  		//������λ
						ppxxStep=0;
						break;
				}
}
