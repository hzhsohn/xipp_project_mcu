#include "system_init.h"
#include "Stm32f1_uart1.h"
#include "Stm32f1_uart2.h"
#include "Stm32f1_uart3.h"
#include "InputDrive.h"
#include "mini-data.h"
#include "watchdog.h"
#include "flash_rw.h"
#include "Stm32F1_Timer2.h"
#include "Stm32F1_Timer3.h"
#include "key.h"


//�Ƿ��Զ�������
unsigned char g_isAutomation=1;
unsigned char g_cCleanCurrentSence=0;  

//����ʱ������
TagTimeingSetting g_tmeSetting={0};

//
void delay_s(int n)
{
		int i=0;
		for(i=0;i<n*10;i++)
		{ STM32_Delay_ms(100); }
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
		
	STM32_Delay_init();
	STM32F1_UART1_Init(115200);
	STM32F1_UART2_Init(19200);
	STM32F1_UART3_Init(230400);
	
	Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	InputDriveInit();
	zhSCM_GPIOConfig();
 
	
	//-----------------------------------------
	//��ȡFALSH����
	setFlashData();
  //-----------------------------------------

	
	//���Ź�
	//watchdog_init();
	
	while(1)
	{
		//���Ź�
		//watchdog_action();
		
	}
}
