#include "Stm32f1_uart1_diver.h"
#include "mini-data.h"
#include "SenceAct.h"

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

    RCC_AHBPeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //enable clock of GPIOA
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

//---------------------------------------
unsigned char Re_buf[11],counter=0;
float _mpu_a[3],_mpu_w[3],_mpu_angle[3],_mpu_T;
extern int g_nMPU_DO;
extern TagTimeingSetting g_tmeSetting;

//
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
				Re_buf[counter]=USART_ReceiveData(USART1);
				if(counter==0&&Re_buf[0]!=0x55) return; 

				counter++;				
				if(counter==11) 
				{    
					  counter=0;
					  //
						switch(Re_buf [1])
						{
						case 0x51:
							_mpu_a[0] = (short)(Re_buf [3]<<8| Re_buf [2])/32768.0*16;
							_mpu_a[1] = (short)(Re_buf [5]<<8| Re_buf [4])/32768.0*16;
							_mpu_a[2] = (short)(Re_buf [7]<<8| Re_buf [6])/32768.0*16;
							_mpu_T = (short)(Re_buf [9]<<8| Re_buf [8])/340.0+36.25;
						break;
						case 0x52:
							_mpu_w[0] = (short)(Re_buf [3]<<8| Re_buf [2])/32768.0*2000;
							_mpu_w[1] = (short)(Re_buf [5]<<8| Re_buf [4])/32768.0*2000;
							_mpu_w[2] = (short)(Re_buf [7]<<8| Re_buf [6])/32768.0*2000;
							_mpu_T = (short)(Re_buf [9]<<8| Re_buf [8])/340.0+36.25;
						break;
						case 0x53:
							_mpu_angle[0] = (short)(Re_buf [3]<<8| Re_buf [2])/32768.0*180;
							_mpu_angle[1] = (short)(Re_buf [5]<<8| Re_buf [4])/32768.0*180;
							_mpu_angle[2] = (short)(Re_buf [7]<<8| Re_buf [6])/32768.0*180;
							_mpu_T = (short)(Re_buf [9]<<8| Re_buf [8])/340.0+36.25;
							if(_mpu_angle[1]<(-g_tmeSetting.mpuLeft))
							{g_nMPU_DO=1;}
							else
							if(_mpu_angle[1]>g_tmeSetting.mpuRight)
							{g_nMPU_DO=2;}
							else
							{g_nMPU_DO=0;}
						break;						
						}
				}			
    }
}
