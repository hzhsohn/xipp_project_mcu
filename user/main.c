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
//
u8_t haha[7]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};
extern u8_t kk;
extern uchar dst_buf[255];
extern uchar myData[20];
//
int nMPU_DO=0;
//--
u16_t pp,rTemperature;
//
void aurtEventSendStatus()
{
		unsigned char cbuf[13]={0};
		int myDataLen=0;
		cbuf[0]=1;
		cbuf[1]=haha[0];
		cbuf[2]=haha[1];
		cbuf[3]=haha[2];
		cbuf[4]=haha[3];
		cbuf[5]=haha[4];
		cbuf[6]=haha[5];
		cbuf[7]=haha[6];
		myDataLen = miniDataCreate(8,cbuf,dst_buf);
		STM32F1_UART3SendDataS(dst_buf,myDataLen);
}

void aurtEventSendUIButton(int i)
{
		int myDataLen=0;
		unsigned char cbuf[2]={0};
		cbuf[0]=0xAA;
		cbuf[0]=i;
		myDataLen = miniDataCreate(1,cbuf,dst_buf);
		STM32F1_UART3SendDataS(dst_buf,myDataLen);
}

int main(void)
{
	System_Init();

	while(1)
	{
		TouchKey_Scan();
			
		//---------------------
		//°´¼ü
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
		}
		
		//---------------------s
		//
		if(kk>=200)
		{
			haha[0]=SENSOR1_STATE()?1:0;
			haha[1]=SENSOR2_STATE()?1:0;
			haha[2]=SENSOR3_STATE()?1:0;
			haha[3]=SENSOR4_STATE()?1:0;
			haha[4]=SENSOR5_STATE()?1:0;
			haha[5]=SENSOR6_STATE()?1:0;
			haha[6]=SENSOR7_STATE()?1:0;
			aurtEventSendStatus();
			kk=0;
		}
		pp = Get_Adc_Average13(10);
		rTemperature=DS18B20_Get_Temp();
	}

}
