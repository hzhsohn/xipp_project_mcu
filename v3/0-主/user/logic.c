#include "mini-data.h"
#include "Stm32f1_uart3.h"
#include "stdio.h"
#include "stdlib.h"
#include "logic.h"

//循环型执行链表
unsigned char g_cmdDataList[20][10]={0};
int g_cmdSendPos=0;//发送游标
int g_cmdDataPos=0;//发送游戏
int g_cmdDataCount=0; //链表内记录数量

//获取状态
int g_getdev_status=0;

//
void sendLogic(void)
{
		if(g_cmdDataCount>0)
		{
			unsigned char*buf=g_cmdDataList[g_cmdSendPos];
			uart3Send(buf[0],buf[1],&buf[2],8);
			g_cmdSendPos++;
			g_cmdSendPos%=20;
			
			memset(buf,0,10);
			g_cmdDataCount--;
		}
}
void recvLogic(int a,int b,unsigned char* data)
{
		switch(a)
		{
			case 0x01:
				s1_000(b, data);
			break;
			case 0x02:
			//	s2_000(b, data);
			break;
			case 0x03:
			//	s3_000(b, data);
			break;
			case 0x04:
			//	s4_000(b, data);
			break;
			case 0x05:
			//	s5_000(b, data);
			break;
		}
}

int getCmdCount(void)
{
		return g_cmdDataCount; //链表内记录数量
}

void addLogicCmd(unsigned char*data,int dataLen)
{
		int i=0;
	
		if(dataLen!=10)
		{return;}
		
		if(g_cmdDataCount<20)
		{
				if(20==g_cmdDataPos)
				{g_cmdDataPos=0;}
				
				for(i=0;i<dataLen;i++)
				{
						g_cmdDataList[g_cmdDataPos][i]=data[i];
				}
				g_cmdDataPos++;
				g_cmdDataCount++;
		}
}

void dev_status(void)
{
		switch(g_getdev_status)
		{
			case 0:
			{
		unsigned char data[]={	1,0,0,0,0,
														0,0,0,0,0};
				addLogicCmd(data,10);
			}
				break;
			case 1:
			{
		unsigned char data[]={	2,0,0,0,0,
														0,0,0,0,0};
				addLogicCmd(data,10);
			}
				break;
			case 2:
			{
		unsigned char data[]={	3,0,0,0,0,
														0,0,0,0,0};
				addLogicCmd(data,10);
			}
				break;
			case 3:
			{
		unsigned char data[]={	4,0,0,0,0,
														0,0,0,0,0};
				addLogicCmd(data,10);
			}
				break;
			case 4:
			{
		unsigned char data[]={	5,0,0,0,0,
														0,0,0,0,0};
				addLogicCmd(data,10);
			}
				break;
		}
		g_getdev_status++;
		g_getdev_status%=5;
}

//------------------------------------------
void s1_000(int b,unsigned char*data)
{
		
}
void s2_000(int b,unsigned char*data)
{
		
}
void s3_000(int b,unsigned char*data)
{
		
}
void s4_000(int b,unsigned char*data)
{
		
}
void s5_000(int b,unsigned char*data)
{
		
}

//------------------------------------------
void s1_001(unsigned char*data)
{
		
}
void s2_001(unsigned char*data)
{
		
}
void s3_001(unsigned char*data)
{
		
}
void s4_001(unsigned char*data)
{
		
}
void s5_001(unsigned char*data)
{
		
}

//-------------------------------------------
//发送控制
void s1_002(unsigned char*data)
{

}
void s2_002(unsigned char*data)
{

}
void s3_002(unsigned char*data)
{

}
void s4_002(unsigned char*data)
{

}
void s5_002(unsigned char*data)
{

}
