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
#include "logic.h"

//是否自动化操作
unsigned char g_isAutomation=1;
unsigned char g_cCleanCurrentSence=0;  

//工作时间设置
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
		
	STM32_Delay_init();
	STM32F1_UART1_Init(115200);
	STM32F1_UART2_Init(115200);
	STM32F1_UART3_Init(19200);

	Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	InputDriveInit();
	zhSCM_GPIOConfig();
 
	//485通讯初始化
	{
		GPIO_InitTypeDef GPIO_MyStruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_10;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOD, &GPIO_MyStruct);
			GPIO_ResetBits(GPIOD,GPIO_Pin_10);	 
			//GPIO_SetBits(GPIOD,GPIO_Pin_10);
	}
	//-----------------------------------------
	//获取FALSH数据
	setFlashData();
  //-----------------------------------------

	//看门狗
	//watchdog_init();

	while(1)
	{
		//看门狗
		//watchdog_action();		
	}
}
