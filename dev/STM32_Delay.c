#include "STM32_Delay.h"
u8_t  fac_us=0;
u16_t fac_ms=0;
/**************************************************************
�������ƣ���ʼ���δ��ӳٺ���
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void STM32_Delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);										//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;																					//Ϊϵͳʱ�ӵ�1/8
	fac_ms=(u16_t)fac_us*1000;																								//����ÿ��ms��Ҫ��systickʱ����
}

/**************************************************************
�������ƣ�nus�ӳٺ���
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void STM32_Delay_us(u32_t nus)
{
	u32_t temp;
	SysTick->LOAD=nus*fac_us; 																							//ʱ�����
	SysTick->VAL=0x00;        																							//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          											//��ʼ����
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));																			//�ȴ�ʱ�䵽��
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;      													//�رռ�����
	SysTick->VAL =0X00;       																							//��ռ�����
}

/**************************************************************
�������ƣ�nms�ӳٺ���
����˵����ע��nms�ķ�Χ
					SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
				  nms<=0xffffff*8*1000/SYSCLK
					SYSCLK��λΪHz,nms��λΪms
					��72M������,nms<=1864
������ڲ�����
���ı�ע��
**************************************************************/
void STM32_Delay_ms(u16_t nms)
{
	u32_t temp;
	SysTick->LOAD=(u32_t)nms*fac_ms;																					//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           																					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          											//��ʼ����
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));																			//�ȴ�ʱ�䵽��
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;      												  //�رռ�����
	SysTick->VAL =0X00;       																							//��ռ�����
}

































