#include "Stm32f1_uart2.h"
#include "mini-data.h"
#include "flash_rw.h"
#include "system_init.h"

//--------------------------------------------
//接收缓存
u8 uart2Data;
uchar g_cache2[128]={0};
unsigned short g_uart2len=0;
TzhMiniData g_ocCmd2;
uchar g_isGetCmdOk2;
int g_timeoverUart2=0;
	
//****************************************************************************
//*函数功能：
//*参数：
//*返还：
//****************************************************************************
void STM32F1_UART2SendData(u8_t nData)
{
    USART_SendData(USART2, nData);                  //向串口 2 发送数据
    while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
}
void STM32F1_UART2SendDataS(u8_t* nData,u8_t nNum)
{	
	u8_t nCnt;
	for (nCnt=0;nCnt<nNum;nCnt++)
	{
		int n=10000;
		USART_SendData(USART2, *(nData+nCnt));                  //向串口 2 发送数据
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET && n--); 
	}
}

//****************************************************************************
//*函数功能：ESP8266初始化
//*参数：lBound-波特率
//*返还：
//****************************************************************************
void STM32F1_UART2_Init(u32_t lBaudRate)
{
    NVIC_InitTypeDef  NVIC_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //enable clock of GPIOA
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //enable clock of USART1
    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//ISART2_TX PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 GPIOA.2
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//USART2_RX  PA.3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 GPIOA.3

    USART_InitStructure.USART_BaudRate          =   lBaudRate;
    USART_InitStructure.USART_WordLength        =   USART_WordLength_8b;
    USART_InitStructure.USART_StopBits          =   USART_StopBits_1;
    USART_InitStructure.USART_Parity            =   USART_Parity_No;
    USART_InitStructure.USART_Mode              =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART2,&USART_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //开启中断
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
    //使能串口
    USART_Cmd(USART2, ENABLE);
}

void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
    {
				uart2Data = USART_ReceiveData(USART1);
				
			  //周期计数复位
			  g_timeoverUart2=0;
			
				if(g_uart2len+1>128){ g_uart2len=0; }
				g_cache2[g_uart2len]=uart2Data;
				g_uart2len++;
				if(0xFA==uart2Data)
				{
						 int tmp;
					_nnc:
						 tmp=miniDataGet(g_cache2,g_uart2len,&g_ocCmd2,&g_isGetCmdOk2);
						 //
						 if(g_isGetCmdOk2)
						 {
								//周期计数复位
								g_timeoverUart2=0;
								//
							  switch(g_ocCmd2.parameter[0])
								{
									case 0x00:
										break;
								}
						 }
						 if(tmp>0)
						 {
								int n;
								g_uart2len-=tmp;
								for(n=0;n<g_uart2len;n++)
								{
									g_cache2[n]=g_cache2[tmp+n]; 
								}
								goto _nnc;
						 }
				 }
    }
}

//发送
void uart2Send(unsigned char i)
{
		uchar dst_buf[32]={0};
		int myDataLen=0;
		unsigned char cbuf[24]={0};
		cbuf[0]=0x00;
		cbuf[1]=i;
		cbuf[2]=0;
		
		myDataLen = miniDataCreate(3,cbuf,dst_buf);
		STM32F1_UART2SendDataS(dst_buf,myDataLen);
}
