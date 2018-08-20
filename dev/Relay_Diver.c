#include "Relay_Diver.h"

void Relay_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/*ʱ��ʹ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
	/*RELAY1*/
	GPIO_MyStruct.GPIO_Pin = RELAY1_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY1_GPIO, &GPIO_MyStruct);
	RELAY1_STATE(LOW);
	/*RELAY2*/
	GPIO_MyStruct.GPIO_Pin = RELAY2_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY2_GPIO, &GPIO_MyStruct);
	RELAY2_STATE(LOW);
	/*RELAY3*/
	GPIO_MyStruct.GPIO_Pin = RELAY3_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY3_GPIO, &GPIO_MyStruct);
	RELAY3_STATE(LOW);
	/*RELAY4*/
	GPIO_MyStruct.GPIO_Pin = RELAY4_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY4_GPIO, &GPIO_MyStruct);
	RELAY4_STATE(LOW);
	/*RELAY5*/
	GPIO_MyStruct.GPIO_Pin = RELAY5_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY5_GPIO, &GPIO_MyStruct);
	RELAY5_STATE(LOW);
	/*RELAY6*/
	GPIO_MyStruct.GPIO_Pin = RELAY6_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY6_GPIO, &GPIO_MyStruct);
	RELAY6_STATE(LOW);
	/*RELAY7*/
	GPIO_MyStruct.GPIO_Pin = RELAY7_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY7_GPIO, &GPIO_MyStruct);
	RELAY7_STATE(LOW);
	/*RELAY8*/
	GPIO_MyStruct.GPIO_Pin = RELAY8_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RELAY8_GPIO, &GPIO_MyStruct);
	RELAY8_STATE(LOW);
	/*RELAY9*/
	GPIO_MyStruct.GPIO_Pin = RELAY9_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY9_GPIO, &GPIO_MyStruct);
	RELAY9_STATE(LOW);


	/*RELAY10*/
	GPIO_MyStruct.GPIO_Pin = RELAY10_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY10_GPIO, &GPIO_MyStruct);
	RELAY10_STATE(LOW);


	/*RELAY11*/
	GPIO_MyStruct.GPIO_Pin = RELAY11_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY11_GPIO, &GPIO_MyStruct);
	RELAY11_STATE(LOW);


	/*RELAY12*/
	GPIO_MyStruct.GPIO_Pin = RELAY12_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY12_GPIO, &GPIO_MyStruct);
	RELAY12_STATE(LOW);


	/*RELAY13*/
	GPIO_MyStruct.GPIO_Pin = RELAY13_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(RELAY13_GPIO, &GPIO_MyStruct);
	RELAY13_STATE(LOW);
	

}


void POWER_Configuration(void)
{
		GPIO_InitTypeDef GPIO_MyStruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);

		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_2;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOE, &GPIO_MyStruct);
		GPIO_SetBits(GPIOE,GPIO_Pin_2);
	
		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_3;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOE, &GPIO_MyStruct);
		GPIO_SetBits(GPIOE,GPIO_Pin_3);
	
	//-------------------------------------------------
	//A33���ػ�
	/*	GPIO_MyStruct.GPIO_Pin = GPIO_Pin_7;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOD, &GPIO_MyStruct);
		GPIO_SetBits(GPIOD,GPIO_Pin_7);*/
}

void VOLUME_Configuration(void)
{
		GPIO_InitTypeDef GPIO_MyStruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_4;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_MyStruct);
		GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	
		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_5;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_MyStruct);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
}

void ANMO_Configuration(void)
{
		GPIO_InitTypeDef GPIO_MyStruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_6;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_MyStruct);
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
	
		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_7;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_MyStruct);
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
}


void LED_Configuration(void)
{
		GPIO_InitTypeDef GPIO_MyStruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);

		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_13;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOE, &GPIO_MyStruct);
		GPIO_SetBits(GPIOE,GPIO_Pin_13);
	
		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_14;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOE, &GPIO_MyStruct);
		GPIO_SetBits(GPIOE,GPIO_Pin_14);
	
		GPIO_MyStruct.GPIO_Pin = GPIO_Pin_15;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOE, &GPIO_MyStruct);
		GPIO_SetBits(GPIOE,GPIO_Pin_15);
}


void RelayTest()
{
	int tmeCal=0;
	
	RELAY1_STATE(0);
	RELAY2_STATE(0);
	RELAY3_STATE(0);
	RELAY4_STATE(0);
	RELAY5_STATE(0);
	RELAY6_STATE(0);
	RELAY7_STATE(0);
	RELAY8_STATE(0);
	RELAY9_STATE(0);
	RELAY10_STATE(0);
	RELAY11_STATE(0);
	RELAY12_STATE(0);
	RELAY13_STATE(0);
	//-------------------------------------------------
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY1_STATE(1); 						//ˮ����
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY2_STATE(1); 							//������
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY3_STATE(1); 						//��ˮ�� 
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY4_STATE(1); 				 			 		//��ˮ��
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY5_STATE(1); 	 					//��������
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY6_STATE(1); 						//ɱ��
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY7_STATE(1); 						//С����ϴת����
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY8_STATE(1); 				//һ��ʺ��ϴת��
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY9_STATE(1); 				 					//������
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY10_STATE(1);						 					//���
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY11_STATE(1); 										//����ת��
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY12_STATE(1); 		 					//����ת������
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
	RELAY13_STATE(1); 						//����ת������
	tmeCal=0;
	while(tmeCal<1600000)
	{
		tmeCal++;
	}
	
}
