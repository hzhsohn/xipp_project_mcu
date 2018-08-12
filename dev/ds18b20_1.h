#ifndef __DS18B20_1_H
#define __DS18B20_1_H

#include "system_init.h"
#include "STM32_Delay.h"

#define DS18B20_DQ1_GPIO 	    GPIOA
#define DS18B20_DQ1_PIN  	    GPIO_Pin_2
#define DS18B20_DQ1_STATE(x) (x)>0?GPIO_SetBits(DS18B20_DQ1_GPIO,DS18B20_DQ1_PIN):GPIO_ResetBits(DS18B20_DQ1_GPIO,DS18B20_DQ1_PIN)
#define DS18B20_DQ1_GET() GPIO_ReadInputDataBit(DS18B20_DQ1_GPIO,DS18B20_DQ1_PIN)
u8 DS18B20_Init1(void);			//��ʼ��DS18B20
s16 DS18B20_Get_Temp1(void);		//��ȡ�¶�
void DS18B20_Start1(void);			//��ʼ�¶�ת��
void DS18B20_Write_Byte1(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte1(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit1(void);		//����һ��λ
u8 DS18B20_Check1(void);			//����Ƿ����DS18B20
void DS18B20_Rst1(void);			//��λDS18B20 

#endif
