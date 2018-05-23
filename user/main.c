#include "system_init.h"
#include "BeeSpeaker_Diver.h"
#include "TouchKey_Diver.h"
#include "Stm32f1_uart1_diver.h"
#include "Stm32f1_uart2_diver.h"
#include "Relay_Diver.h"
#include "TouchKeyFunction.h"
#include "Stm32f1_uart3_diver.h"
#include "Sensor.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1_Diver.h"
#include "Stm32f1_ADC2_Diver.h"
#include "Motor_Diver.h"
//
u8_t haha[7]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};
extern u8_t kk;
extern uchar dst_buf[255];
extern uchar myData[20];
//是否自动化操作
unsigned char g_isAutomation=0;
//当前清洗小场景
unsigned char g_cCleanCurrentSence=0;  //0没执行,1小便 ,2大便

//--
u16_t pp,pp2,rTemperature;

//提交当前状态
void aurtEventSendStatus()
{
		unsigned char cbuf[13]={0};
		int myDataLen=0;
		//
		cbuf[0]=0;
		cbuf[1]=g_isAutomation;
		cbuf[2]=g_cCleanCurrentSence;
		cbuf[3]=0;//抽吸启用
		cbuf[4]=0;//烘干启用
		cbuf[5]=0;//除菌启用
		cbuf[6]=0;//大便启用
		cbuf[7]=0;//大便冲洗启用
		cbuf[8]=0;//小便启用
		cbuf[9]=0;//小便冲洗启用
		
		myDataLen = miniDataCreate(8,cbuf,dst_buf);
		STM32F1_UART3SendDataS(dst_buf,myDataLen);
}

void aurtEventSendUIButton(int i)
{
		int myDataLen=0;
		unsigned char cbuf[2]={0};
		cbuf[0]=0xAA;
		cbuf[1]=i;
		myDataLen = miniDataCreate(2,cbuf,dst_buf);
		STM32F1_UART3SendDataS(dst_buf,myDataLen);
}

int main(void)
{
	System_Init();
	
	Motor1_do(1);
	Motor1_do(0);
	Motor2_do(1);
	Motor2_do(0);

	while(1)
	{
		TouchKey_Scan();

		//---------------------
		//按键
		if(bButton1)
		{
				aurtEventSendUIButton(1);
				bButton1 = _Disable;
		}		
		if(bButton2)
		{
				aurtEventSendUIButton(2);
				bButton2 = _Disable;
		}
		if(bButton3)
		{
				aurtEventSendUIButton(3);
				bButton3 = _Disable;
		}
		if(bButton4)
		{
				aurtEventSendUIButton(4);
				bButton4 = _Disable;
		}
		if(bButton5)
		{
				aurtEventSendUIButton(5);
				bButton5 = _Disable;
		}
		if(bButton6)
		{
				aurtEventSendUIButton(6);
				bButton6 = _Disable;
		}
		if(bButton7)
		{
				aurtEventSendUIButton(7);
				bButton7 = _Disable;
		}		
		/*
		switch(nMPU_DO)
		{
			case 0:
				//sence_None();
				RELAY6_STATE(0);
				RELAY7_STATE(0);		
				break;
			case 1:
				//sence_POPOLeft();
				RELAY6_STATE(1);
				RELAY7_STATE(0);		
				break;
			case 2:
				//sence_POPORight();
				RELAY6_STATE(0);
				RELAY7_STATE(1);		
				break;
		}*/
		
		//---------------------
		//
		if(kk>=200)
		{
			haha[0]=SENSOR1_STATE()?1:0;
			haha[1]=SENSOR2_STATE()?1:0;
			haha[2]=SENSOR3_STATE()?1:0;
			haha[3]=SENSOR4_STATE()?1:0;
			haha[4]=SENSOR5_STATE()?1:0;
			//aurtEventSendStatus();
			kk=0;
		}
		pp = Get_Adc_Average(10);
		pp2= Get_Adc2_Average(10);
		rTemperature=DS18B20_Get_Temp();
	}
	
}
