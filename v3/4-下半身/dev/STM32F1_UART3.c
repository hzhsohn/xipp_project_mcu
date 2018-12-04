#include "Stm32f1_uart3.h"
#include "stdio.h"
#include "mini-data.h"
#include "stdlib.h"

extern TagUpData485 ud485;

//
void recvLogic(int a,int b,unsigned char* data);
//--------------------------------------------
//接收缓存
u8 uart3Data;
uchar g_cache3[128]={0};
unsigned short g_uart3len=0;
TzhMiniData g_ocCmd3;
uchar g_isGetCmdOk3;
int g_timeoverUart3=0;

//****************************************************************************
//*函数功能：
//*参数：
//*返还：
//****************************************************************************
void STM32F1_UART3SendData(u8_t nData)
{
    USART_SendData(USART3, nData);                  //向串口 3 发送数据
    while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
}
void STM32F1_UART3SendDataS(u8_t* nData,u8_t nNum)
{	
	u8_t nCnt;
	for (nCnt=0;nCnt<nNum;nCnt++)

	{
    int n=10000;
		USART_SendData(USART3, *(nData+nCnt));                  //向串口 3 发送数据
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET && n--); 
	}

}

//****************************************************************************
//*函数功能：ESP8266初始化
//*参数：lBound-波特率
//*返还：
//****************************************************************************
void STM32F1_UART3_Init(u32_t lBaudRate)
{
    NVIC_InitTypeDef  NVIC_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //enable clock of GPIOB
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //enable clock of USART3
    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//ISART3_TX PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化 
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//USART3_RX  PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化 
	
    USART_InitStructure.USART_BaudRate          =   lBaudRate;
    USART_InitStructure.USART_WordLength        =   USART_WordLength_8b;
    USART_InitStructure.USART_StopBits          =   USART_StopBits_1;
    USART_InitStructure.USART_Parity            =   USART_Parity_No;
    USART_InitStructure.USART_Mode              =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART3,&USART_InitStructure);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //开启中断
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
    //使能串口
    USART_Cmd(USART3, ENABLE);//使能串口

}


//---------------------------------------
void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
    {
				uart3Data = USART_ReceiveData(USART3);
				
			  //周期计数复位
			  g_timeoverUart3=0;
			
				if(g_uart3len+1>128){ g_uart3len=0; }
				g_cache3[g_uart3len]=uart3Data;
				g_uart3len++;
				if(0xFA==uart3Data)
				{
						 int tmp;
					_nnc:
						 tmp=miniDataGet(g_cache3,g_uart3len,&g_ocCmd3,&g_isGetCmdOk3);
						 //
						 if(g_isGetCmdOk3)
						 {
								int a=0;
								int b=0;
								unsigned char *pdata=NULL;
								//周期计数复位
								g_timeoverUart3=0;
								//
								a=g_ocCmd3.parameter[0];
								b=g_ocCmd3.parameter[1];
								pdata=&g_ocCmd3.parameter[2];
								//
								if(a==4)
								{
										recvLogic(a,b,pdata);
								}
						 }
						 if(tmp>0)
						 {
								int n;
								g_uart3len-=tmp;
								for(n=0;n<g_uart3len;n++)
								{
									g_cache3[n]=g_cache3[tmp+n];
								}
								goto _nnc;
						 }
				 }
    }
}

//发送
void uart3Send(unsigned char f,char*data,int datalen)
{
		int i=0;
		uchar dst_buf[36]={0};
		int myDataLen=0;
		unsigned char cbuf[30]={0};
				
		cbuf[0]=4; //位置 0-5 ,4代表本机
		cbuf[1]=f; //功能
		
		if(data)
		{
				for(i=0;i<datalen;i++)
				{
					cbuf[i+2]=data[i];
				}
		}

		myDataLen = miniDataCreate(2+datalen,cbuf,dst_buf);
		STM32F1_UART3SendDataS(dst_buf,myDataLen);
}

void uart3SendNull(unsigned char f)
{
		uart3Send(f,NULL,0);
}


void recvLogic(int a,int b,unsigned char* data)
{
		switch(b)
		{
			case 0x00: //获取传感器
			{
					 uart3Send(0x10,(char*)&ud485,sizeof(TagUpData485));
			}
			break;
			//-----------------------------------------
			case 0xA0: //抽水机开
			{					
					//工作秒数
					unsigned char t=data[0];
			}
			break;
			case 0xA1: //抽             水机关
			{
					
			}
			break;
			//-----------------------------------------
			case 0xA2: //水加热开
			{				
					//工作秒数
					unsigned char t=data[0];
			}
			break;
			case 0xA3: //水加热关
			{
			}
			break;
			//-----------------------------------------
			case 0xA4: //大便斗冲水阀开
			{				
					//工作秒数
					unsigned char t=data[0];
			}
			break;
			case 0xA5: //大便斗冲水阀关
			{
			}
			break;			
			//-----------------------------------------
			case 0xA6: //清洁冲水阀开
			{
					//工作秒数
					unsigned char t=data[0];
			}
			break;			
			case 0xA7: //清洁冲水阀关
			{				
			}
			break;			
			//-----------------------------------------
			case 0xA8: //小便斗冲水阀开
			{				
					//工作秒数
					unsigned char t=data[0];
			}
			break;
			case 0xA9:	//小便斗冲水阀
			{
			}
			break;
			
		}
}
