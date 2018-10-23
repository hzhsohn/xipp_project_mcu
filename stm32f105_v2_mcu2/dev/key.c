/*
  2018/7/9
  Copyright (C) Han.zhihong
*/


#include "key.h"

/*******************************************************************************
* 函数名       : zhSCM_GPIOConfig
* 函数描述      : 设置各GPIO端口功能
* 输入参数      : 自己看
* 输出结果      : 无
* 返回值        : 无
*******************************************************************************/
void zhSCM_GPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/*时钟使能*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_1_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_1_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_2_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_2_GPIO, &GPIO_MyStruct);

	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_3_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_3_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_4_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_4_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_5_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_5_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_6_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_6_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_7_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_7_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_8_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_8_GPIO, &GPIO_MyStruct);
}
/*******************************************************************************
* 函数名       : zhSCM_initKeyState
* 函数描述      : 初始各GPIO按键状态
* 输入参数      : EzhKeyState的变量
* 输出结果      : 无
* 返回值        : 无
*******************************************************************************/
void zhSCM_initKeyState(EzhKeyState *status)
{
  *status=ZH_KEY_STATE_0;
}
/*******************************************************************************
* 函数名       : zhSCM_keyState
* 函数描述      : 检测各GPIO端口按键功能
* 输入参数      : 几个呗
* 输出结果      : 无
* 返回值        : 无
*******************************************************************************/
EzhKeyEvent zhSCM_keyState(EzhKeyState *status,GPIO_TypeDef *GPIOx,u16 GPIO_Pin_x)
{
		int keyPort=0;
		EzhKeyEvent event;
		//读取GPIOA的I/O电平
		keyPort=GPIO_ReadInputData(GPIOx); 
		keyPort=keyPort&GPIO_Pin_x;
		keyPort=!keyPort;
		switch(*status)
		{
				/*使用switch判断检测是否为抖动信号,如果不是便即行操作*/
				case ZH_KEY_STATE_1:
				{
				 //非抖动进行操作
				 if(keyPort)
				 {
						event=ZH_KEY_EVENT_DOWN;
				//切换状态
				 *status=ZH_KEY_STATE_2;
				 }
				 else
				 {
					 event=ZH_KEY_EVENT_NONE; 
				 *status=ZH_KEY_STATE_0;
				 }
				}
				break;
				/*按压检测*/
				case ZH_KEY_STATE_2:
				{
					if(keyPort)
					{
					 event=ZH_KEY_EVENT_PRESS;
				 *status=ZH_KEY_STATE_3;
					}
					else
					{
						 //已经松手,更新状态
						 *status=ZH_KEY_STATE_0;
				 event=ZH_KEY_EVENT_UP;
					}
				}
				break;
				/*松手检测*/
				case ZH_KEY_STATE_3:
				{
					if(keyPort)
					{
					 event=ZH_KEY_EVENT_PRESS;
					}
					else
					{
						 //已经松手,更新状态
						 *status=ZH_KEY_STATE_0;
				 event=ZH_KEY_EVENT_UP;
					}
				}
				break;
				default:
				{
							//有电平信号输入
							if(keyPort)
							{
									*status=ZH_KEY_STATE_1; 
							}
							event=ZH_KEY_EVENT_NONE;
				}
				break;
		}
		return event;
}


