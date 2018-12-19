#include "mini-data.h"
#include "Stm32f1_uart3.h"
#include "stdio.h"
#include "stdlib.h"
#include "logic.h"

//循环型执行链表
TzhDoCmd g_cmdDataList[20]={0};
int g_cmdSendPos=0;//发送游标
int g_cmdDataPos=0;//发送游戏
int g_cmdDataCount=0; //链表内记录数量
int g_cmdLastDoTime=0;

//获取状态
int g_getdev_status=0;

//
void sendLogic(void)
{
		if(g_cmdDataCount>0)
		{
			TzhDoCmd*p =&g_cmdDataList[g_cmdSendPos];
			uart3Send(p->bid,p->fid,p->second,(unsigned char*)p->buf,p->buflen);
			
			if(0==p->second)
			{
				g_cmdSendPos++;
				g_cmdSendPos%=20;
				
				memset(p,0,sizeof(TzhDoCmd));
				g_cmdDataCount--;
			}
			else if(p->second>0){
				p->second--;
			}
			else{
				p->second=0;
			}
		}
}

void stopSend(void)
{
		g_cmdSendPos=0;
		g_cmdDataCount=0;
		addLogicCmd(0xFF,0xFF,3,NULL,0); //全局停止操作指令,持续3秒
}

void recvLogic(int a,int b,unsigned char* data)
{
		switch(a)
		{
			case 0x01:
				s1_000(b, data);
			break;
			case 0x02:
				s2_000(b, data);
			break;
			case 0x03:
				s3_000(b, data);
			break;
			case 0x04:
				s4_000(b, data);
			break;
			case 0x05:
				s5_000(b, data);
			break;
		}
}

int getCmdCount(void)
{
		return g_cmdDataCount; //链表内记录数量
}

void addLogicCmd(unsigned char b,unsigned char f,int doSecond,unsigned char*data,int dataLen)
{
		int i=0;
			
		if(g_cmdDataCount<20)
		{
				if(20==g_cmdDataPos)
				{g_cmdDataPos=0;}
				
				for(i=0;i<dataLen;i++)
				{
						g_cmdDataList[g_cmdDataPos].buf[i]=data[i];
				}
				g_cmdDataList[g_cmdDataPos].bid=b;
				g_cmdDataList[g_cmdDataPos].fid=f;
				g_cmdDataList[g_cmdDataPos].second=doSecond*10;//时间同步定时器
				g_cmdDataList[g_cmdDataPos].buflen=dataLen;
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
				addLogicCmd(1,0,0,NULL,0);
			}
				break;
			case 1:
			{
				addLogicCmd(2,0,0,NULL,0);
			}
				break;
			case 2:
			{
				addLogicCmd(3,0,0,NULL,0);
			}
				break;
			case 3:
			{
				addLogicCmd(4,0,0,NULL,0);
			}
				break;
			case 4:
			{
				addLogicCmd(5,0,0,NULL,0);
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
		switch(b)
		{
			case 0x10:
			{
				TagUpData485_S4*p=(TagUpData485_S4*)data;
				switch(p->key)//按键功能
				{
					case 1:
					{
						addLogicCmd(1,0xA0,10,NULL,0);
					}
						break;
					case 2:
					{
					}
						break;
					case 3:
					{
					}
						break;
					case 4:
					{
					}	
						break;
					case 5:
					{
					}
						break;
					case 6:
					{
					}
						break;
					case 7:
					{
					}
						break;
					case 8:
					{
					}
						break;
				}
			}
				break;
		}
}
void s5_000(int b,unsigned char*data)
{
		
}


