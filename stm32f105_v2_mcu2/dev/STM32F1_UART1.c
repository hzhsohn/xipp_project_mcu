#include "Stm32f1_uart1.h"
#include "mini-data.h"
#include "flash_rw.h"
#include "OutputDrive.h"
#include "system_init.h"

//------------------------------------------------------
//接收缓存
u8 uart1Data;
uchar g_cache[128]={0};
unsigned short g_uart1len=0;
TzhMiniData g_ocCmd;
uchar g_isGetCmdOk;
int g_timeoverUart1=0;
//
extern TagTimeingSetting g_tmeSetting;
//
//中断当前动作
extern int isCleanRuning;
//
extern unsigned char g_cCleanCurrentSence;  
//
void uartRelayProc(unsigned char i,char isOn);

//****************************************************************************
//*函数功能：
//*参数：
//*返还：
//****************************************************************************
void STM32F1_UART1SendData(u8_t nData)
{
    USART_SendData(USART1, nData);                  //向串口 1 发送数据
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
}
void STM32F1_UART1SendDataS(u8_t* nData,u8_t nNum)
{	
		u8_t nCnt;
		for (nCnt=0;nCnt<nNum;nCnt++)
		{
			int n=10000;
			USART_SendData(USART1, *(nData+nCnt));                  //向串口 1 发送数据
			while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET && n--); 
		}
}

//****************************************************************************
//*函数功能：ESP8266初始化
//*参数：lBound-波特率
//*返还：
//****************************************************************************
void STM32F1_UART1_Init(u32_t lBaudRate)
{
    NVIC_InitTypeDef  NVIC_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //enable clock of GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //enable clock of USART1
    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//ISART1_TX PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 GPIOA.9
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//USART1_RX  PA.10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 GPIOA.10
	
    USART_InitStructure.USART_BaudRate          =   lBaudRate;
    USART_InitStructure.USART_WordLength        =   USART_WordLength_8b;
    USART_InitStructure.USART_StopBits          =   USART_StopBits_1;
    USART_InitStructure.USART_Parity            =   USART_Parity_No;
    USART_InitStructure.USART_Mode              =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1,&USART_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //开启中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
    //使能串口
    USART_Cmd(USART1, ENABLE);//使能串口
}



//发送时间参数
void sendTimeCfg()
{
		int i=0;
		char *pstr;
		uchar dst_buf[55]={0};
		int myDataLen=0;
		unsigned char cbuf[50]={0};
		cbuf[0]=0xB1;
		pstr=(char *)&g_tmeSetting;
		for(i=0;i<sizeof(TagTimeingSetting);i++)
		{
			cbuf[i+1]=pstr[i];
		}
		myDataLen = miniDataCreate(sizeof(TagTimeingSetting)+1,cbuf,dst_buf);
		STM32F1_UART1SendDataS(dst_buf,myDataLen);
}

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
				uart1Data = USART_ReceiveData(USART1);
				
			  //周期计数复位
			  g_timeoverUart1=0;
			
				if(g_uart1len+1>128){ g_uart1len=0; }
				g_cache[g_uart1len]=uart1Data;
				g_uart1len++;
				if(0xFA==uart1Data)
				{
						 int tmp;
					_nnc:
						 tmp=miniDataGet(g_cache,g_uart1len,&g_ocCmd,&g_isGetCmdOk);
						 //
						 if(g_isGetCmdOk)
						 {
								//周期计数复位
								g_timeoverUart1=0;
								
							  switch(g_ocCmd.parameter[0])
								{
									case 0x00:
											uartRelayProc(g_ocCmd.parameter[1],g_ocCmd.parameter[2]);
										break;
								}
						 }
						 if(tmp>0)
						 {
								int n;
								g_uart1len-=tmp;
								for(n=0;n<g_uart1len;n++)
								{
									g_cache[n]=g_cache[tmp+n];
								}
								goto _nnc;
						 }
				 }
		 }
}

void uartRelayProc(unsigned char i,char isOn)
{
	switch(i)
	{
		//继电器处理
		case 16: 
				_unit16(isOn);
			break;
		case 17:
				_unit17(isOn);
			break;
		case 18:
				_unit18(isOn);
			break;
		case 19:
				_unit19(isOn);
			break;
		case 20:
				_unit20(isOn);
			break;
		case 21:
				_unit21(isOn);
			break;
		case 22:
				_unit22(isOn);
			break;
		case 23:
				_unit23(isOn);
			break;
		case 24:
				_unit24(isOn);
			break;
		case 25:
				_unit25(isOn);
			break;
		case 26:
				_unit26(isOn);
			break;
		case 27:
				_unit27(isOn);
			break;
	}
}

//发送控制继电器
void uartSendUartRelay(unsigned char i,char isOn)
{
		uchar dst_buf[32]={0};
		int myDataLen=0;
		unsigned char cbuf[24]={0};
		cbuf[0]=0x00;
		cbuf[1]=i;
		cbuf[2]=isOn;
		
		myDataLen = miniDataCreate(3,cbuf,dst_buf);
		STM32F1_UART1SendDataS(dst_buf,myDataLen);
}