#include "Stm32f1_uart3_diver.h"
#include "stdio.h"
#include "mini-data.h"
#include "SenceAct.h"
#include "stdlib.h"
#include "Motor_Diver.h"

//****************************************************************************
//*�������ܣ�
//*������
//*������
//****************************************************************************
void STM32F1_UART3SendData(u8_t nData)
{
    USART_SendData(USART3, nData);                  //�򴮿� 3 ��������
    while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
}
void STM32F1_UART3SendDataS(u8_t* nData,u8_t nNum)
{	
	u8_t nCnt;
	for (nCnt=0;nCnt<nNum;nCnt++)
	{
    int n=10000;
		USART_SendData(USART3, *(nData+nCnt));                  //�򴮿� 3 ��������
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET && n--); 
	}

}

//****************************************************************************
//*�������ܣ�ESP8266��ʼ��
//*������lBound-������
//*������
//****************************************************************************
void STM32F1_UART3_Init(u32_t lBaudRate)
{
    NVIC_InitTypeDef  NVIC_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //enable clock of GPIOB
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //enable clock of USART3
    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//ISART3_TX PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ�� 
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//USART3_RX  PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ�� 
	
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
    //�����ж�
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
    //ʹ�ܴ���
    USART_Cmd(USART3, ENABLE);//ʹ�ܴ���

}


//---------------------------------------
unsigned char Re_buf[11],counter=0;
float _mpu_a[3],_mpu_w[3],_mpu_angle[3],_mpu_T;
extern int g_nMPU_DO;
extern TagTimeingSetting g_tmeSetting;

//
void USART3_IRQHandler(void)
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
