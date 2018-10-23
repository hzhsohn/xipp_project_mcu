#include "Stm32f1_uart1.h"
#include "mini-data.h"
#include "flash_rw.h"
#include "Motor_Diver.h"

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



//------------------------------------------------------
//接收缓存
uchar g_cache[128]={0};
unsigned short g_uart1len=0;
TzhMiniData g_ocCmd;
uchar g_isGetCmdOk;
extern unsigned char g_isAutomation;
extern TagTimeingSetting g_tmeSetting;
//
extern int kkUart1count;
//中断当前动作
extern int isCleanRuning;

//
extern unsigned char g_cCleanCurrentSence;  

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
				u8 uart1Data;
				uart1Data = USART_ReceiveData(USART1);
				
			  //周期计数复位
			  kkUart1count=0;
			
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
								kkUart1count=0;
								
							  switch(g_ocCmd.parameter[0])
								{
									case 0x90:
											//Motor1_do_intpr_cmd(1);
											Motor_demo_up();
										break;
									case 0x91:
											//Motor1_do_intpr_cmd(2);
											Motor_demo_down();
										break;
									case 0x92:
											Motor2_do_intpr_cmd(1);
										break;
									case 0x93:
											Motor2_do_intpr_cmd(2);
										break;
									case 0xD0:
									case 0x94:				//摄像头演示模式
											Motor_demo();
										break;
									case 0xD1:
											if(0==g_cCleanCurrentSence)
											{
												//aurtEventBtn(0x60);
												g_cCleanCurrentSence=ezhCleanSenceA;
												isCleanRuning=1;
											}
										break;
									case 0xD2:
											if(0==g_cCleanCurrentSence)
											{
												//aurtEventBtn(0x60);
												g_cCleanCurrentSence=ezhCleanSenceB;
												isCleanRuning=1;
											}
										break;
									case 0xD3:
											if(0==g_cCleanCurrentSence)
											{
												//aurtEventBtn(0x60);
												g_cCleanCurrentSence=ezhCleanSenceC;
												isCleanRuning=1;
											}
										break;
									case 0xA0: //启用自动化
											g_isAutomation=g_ocCmd.parameter[1]?1:0;
										break;
									case 0xA1: //参数获取
											sendTimeCfg();
										break;
									case 0xA2: //设置参数
									{
											int i=0;
											char *pstr=(char *)&g_tmeSetting;
											for(i=0;i<sizeof(TagTimeingSetting);i++)
											{
												pstr[i]=(char)g_ocCmd.parameter[1+i];
											}
											FLASH_WriteByte(STARTADDR,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));
									}
										break;
									case 0xA3: //中断当前
										isCleanRuning=0;
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
