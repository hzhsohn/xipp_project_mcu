#include "Stm32f1_uart3.h"
#include "stdio.h"
#include "mini-data.h"
#include "stdlib.h"
#include "Motor_Diver.h"

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
//
void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
    {
				USART_ReceiveData(USART3);
    }
}
