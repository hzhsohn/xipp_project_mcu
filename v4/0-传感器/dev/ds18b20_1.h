#ifndef __DS18B20_1_H
#define __DS18B20_1_H

#include "system_init.h"
#include "STM32_Delay.h"

#define DS18B20_DQ1_GPIO 	    GPIOD
#define DS18B20_DQ1_PIN  	    GPIO_Pin_5
#define DS18B20_DQ1_STATE(x) (x)>0?GPIO_SetBits(DS18B20_DQ1_GPIO,DS18B20_DQ1_PIN):GPIO_ResetBits(DS18B20_DQ1_GPIO,DS18B20_DQ1_PIN)
#define DS18B20_DQ1_GET() GPIO_ReadInputDataBit(DS18B20_DQ1_GPIO,DS18B20_DQ1_PIN)
u8 DS18B20_Init1(void);			//初始化DS18B20
s16 DS18B20_Get_Temp1(void);		//获取温度
void DS18B20_Start1(void);			//开始温度转换
void DS18B20_Write_Byte1(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte1(void);		//读出一个字节
u8 DS18B20_Read_Bit1(void);		//读出一个位
u8 DS18B20_Check1(void);			//检测是否存在DS18B20
void DS18B20_Rst1(void);			//复位DS18B20 

#endif
