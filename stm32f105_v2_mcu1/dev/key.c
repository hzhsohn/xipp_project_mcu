/*
  2018/7/9
  Copyright (C) Han.zhihong
*/


#include "key.h"

/*******************************************************************************
* ������       : zhSCM_GPIOConfig
* ��������      : ���ø�GPIO�˿ڹ���
* �������      : �Լ���
* ������      : ��
* ����ֵ        : ��
*******************************************************************************/
void zhSCM_GPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/*ʱ��ʹ��*/
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
* ������       : zhSCM_initKeyState
* ��������      : ��ʼ��GPIO����״̬
* �������      : EzhKeyState�ı���
* ������      : ��
* ����ֵ        : ��
*******************************************************************************/
void zhSCM_initKeyState(EzhKeyState *status)
{
  *status=ZH_KEY_STATE_0;
}
/*******************************************************************************
* ������       : zhSCM_keyState
* ��������      : ����GPIO�˿ڰ�������
* �������      : ������
* ������      : ��
* ����ֵ        : ��
*******************************************************************************/
EzhKeyEvent zhSCM_keyState(EzhKeyState *status,GPIO_TypeDef *GPIOx,u16 GPIO_Pin_x)
{
		int keyPort=0;
		EzhKeyEvent event;
		//��ȡGPIOA��I/O��ƽ
		keyPort=GPIO_ReadInputDataBit(GPIOx,GPIO_Pin_x); 
		keyPort=!keyPort;
		switch(*status)
		{
				/*ʹ��switch�жϼ���Ƿ�Ϊ�����ź�,������Ǳ㼴�в���*/
				case ZH_KEY_STATE_1:
				{
				 //�Ƕ������в���
				 if(keyPort)
				 {
						event=ZH_KEY_EVENT_DOWN;
				//�л�״̬
				 *status=ZH_KEY_STATE_2;
				 }
				 else
				 {
					 event=ZH_KEY_EVENT_NONE; 
				 *status=ZH_KEY_STATE_0;
				 }
				}
				break;
				/*��ѹ���*/
				case ZH_KEY_STATE_2:
				{
					if(keyPort)
					{
					 event=ZH_KEY_EVENT_PRESS;
				 *status=ZH_KEY_STATE_3;
					}
					else
					{
						 //�Ѿ�����,����״̬
						 *status=ZH_KEY_STATE_0;
				 event=ZH_KEY_EVENT_UP;
					}
				}
				break;
				/*���ּ��*/
				case ZH_KEY_STATE_3:
				{
					if(keyPort)
					{
					 event=ZH_KEY_EVENT_PRESS;
					}
					else
					{
						 //�Ѿ�����,����״̬
						 *status=ZH_KEY_STATE_0;
				 event=ZH_KEY_EVENT_UP;
					}
				}
				break;
				default:
				{
							//�е�ƽ�ź�����
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


