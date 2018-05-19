#ifndef __AT24C02_DIVER_H__
#define __AT24C02_DIVER_H__

#include "system_init.h"
#define HIGH 1
#define LOW 0
/*管脚定义*/
#define AT24C02_SCL_GPIO 	    GPIOB
#define AT24C02_SCL_PIN  	    GPIO_Pin_7
#define AT24C02_SDA_GPIO 	    GPIOB
#define AT24C02_SDA_PIN  	    GPIO_Pin_6

/*管脚控制*/
#define AT24C02_SCL_STATE(x) (x)>0?GPIO_SetBits(AT24C02_SCL_GPIO,AT24C02_SCL_PIN):GPIO_ResetBits(AT24C02_SCL_GPIO,AT24C02_SCL_PIN)
#define AT24C02_SDA_STATE(x) (x)>0?GPIO_SetBits(AT24C02_SDA_GPIO,AT24C02_SDA_PIN):GPIO_ResetBits(AT24C02_SDA_GPIO,AT24C02_SDA_PIN)
#define AT24C02_SDA_GET() GPIO_ReadInputDataBit(AT24C02_SDA_GPIO,AT24C02_SDA_PIN)

void AT24C02IIC_Init(void);                											//初始化IIC的IO口
void AT24C02IIC_Start(void);																			//发送IIC开始信号
void AT24C02IIC_Stop(void);	  																	//发送IIC停止信号
void AT24C02IIC_Send_Byte(u8_t txd);																//IIC发送一个字节
u8_t AT24C02IIC_Read_Byte(u8_t ack);											//IIC读取一个字节
u8_t AT24C02IIC_Wait_Ack(void); 																		//IIC等待ACK信号
void AT24C02IIC_Ack(void);																				//IIC发送ACK信号
void AT24C02IIC_NAck(void);																			//IIC不发送ACK信号

void AT24C02IIC_Write_One_Byte(u8_t daddr,u8_t addr,u8_t data);
u8_t AT24C02IIC_Read_One_Byte(u8_t daddr,u8_t addr);

u8_t AT24C02_ReadOneByte(u16_t ReadAddr);																//指定地址读取一个字节
void AT24C02_WriteOneByte(u16_t WriteAddr,u8_t DataToWrite);						//指定地址写入一个字节
void AT24C02_WriteLenByte(u16_t WriteAddr,u32_t DataToWrite,u8_t Len);		//指定地址开始写入指定长度的数据
u32_t AT24C02_ReadLenByte(u16_t ReadAddr,u8_t Len);												//指定地址开始读取指定长度数据
void AT24C02_Write16bits(u16_t WriteAddr,u16_t DataToWrite);
u16_t AT24C02_Read16bits(u16_t ReadAddr);
void AT24C02_Init(void);																						 //初始化IIC

#endif

