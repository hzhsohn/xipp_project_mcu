#include "AutoFunction.h"
#include "Relay_Diver.h"
#include "ds18b20.h"
u8_t CleanxbStep;
u8_t CleandbStep;
u16_t CleanxbCnt;
u16_t CleandbCnt;
extern u16_t rTemperature;
int nMPU_DO=0;
void HeatWater(void)
{
	rTemperature>=370?RELAY5_STATE(0):RELAY5_STATE(1);
}
void ChargeAir(void)
{
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
}
void CleanXiaoBian(void)
{
	switch(CleanxbStep)
	{
		case 0x00:
			RELAY1_STATE(1);
			break;
		case 0x01:
			break;
	}
}
void CLEANXB_TIME_ISR()
{
	switch(CleanxbStep)
	{
		case 0x00:
			CleanxbCnt++;
			if(CleanxbCnt>=300)
			{
				RELAY2_STATE(1);
				CleanxbCnt = 0;
				CleanxbStep = 0x01;
			}
			break;
		case 0x01:
			CleanxbCnt++;
			if(CleanxbCnt>=500)
			{
				RELAY2_STATE(0);
				RELAY3_STATE(1);
				CleanxbCnt = 0;
				CleanxbStep = 0x02;
			}
			break;
		case 0x02:
			CleanxbCnt++;
			if(CleanxbCnt>=1000)
			{
				RELAY3_STATE(0);
				RELAY4_STATE(1);
				CleanxbCnt = 0;
				CleanxbStep = 0x03;
			}
			break;
		case 0x03:
			CleanxbCnt++;
			if(CleanxbCnt>=18000)
			{
				RELAY4_STATE(0);
				RELAY1_STATE(0);
				CleanxbCnt = 0;
				CleanxbStep = 0x04;
			}
			break;
		case 0x04:
			break;
	}
}
void CLEANDB_TIME_ISR()
{
	switch(CleandbStep)
	{
		case 0x00:
			CleandbCnt++;
			if(CleandbCnt>=300)
			{
				RELAY2_STATE(1);
				CleandbCnt = 0;
				CleandbCnt = 0x01;
			}
			break;
		case 0x01:
			CleandbCnt++;
			if(CleandbCnt>=1000)
			{
				RELAY2_STATE(0);
				RELAY3_STATE(1);
				CleandbCnt = 0;
				CleandbCnt = 0x02;
			}
			break;
		case 0x02:
			CleandbCnt++;
			if(CleandbCnt>=1000)
			{
				RELAY3_STATE(0);
				RELAY4_STATE(1);
				CleandbCnt = 0;
				CleandbCnt = 0x03;
			}
			break;
		case 0x03:
			CleandbCnt++;
			if(CleandbCnt>=30000)
			{
				RELAY4_STATE(0);
				RELAY1_STATE(0);
				CleandbCnt = 0;
				CleandbCnt = 0x04;
			}
			break;
		case 0x04:
			break;
	}
}
