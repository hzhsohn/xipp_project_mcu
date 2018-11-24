#include "STM32_Delay.h"
u8_t  fac_us=0;
u16_t fac_ms=0;
/**************************************************************
函数名称：初始化滴答延迟函数
函数说明：
函出入口参数：
更改备注：
**************************************************************/
void STM32_Delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);										//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;																					//为系统时钟的1/8
	fac_ms=(u16_t)fac_us*1000;																								//代表每个ms需要的systick时钟数
}

/**************************************************************
函数名称：nus延迟函数
函数说明：
函出入口参数：
更改备注：
**************************************************************/
void STM32_Delay_us(u32_t nus)
{
	u32_t temp;
	SysTick->LOAD=nus*fac_us; 																							//时间加载
	SysTick->VAL=0x00;        																							//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          											//开始倒数
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));																			//等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;      													//关闭计数器
	SysTick->VAL =0X00;       																							//清空计数器
}

/**************************************************************
函数名称：nms延迟函数
函数说明：注意nms的范围
					SysTick->LOAD为24位寄存器,所以,最大延时为:
				  nms<=0xffffff*8*1000/SYSCLK
					SYSCLK单位为Hz,nms单位为ms
					对72M条件下,nms<=1864
函出入口参数：
更改备注：
**************************************************************/
void STM32_Delay_ms(u16_t nms)
{
	u32_t temp;
	SysTick->LOAD=(u32_t)nms*fac_ms;																					//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           																					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          											//开始倒数
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));																			//等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;      												  //关闭计数器
	SysTick->VAL =0X00;       																							//清空计数器
}

































