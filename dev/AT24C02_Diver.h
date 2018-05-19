#ifndef __AT24C02_DIVER_H__
#define __AT24C02_DIVER_H__

#include "system_init.h"
#define HIGH 1
#define LOW 0
/*�ܽŶ���*/
#define AT24C02_SCL_GPIO 	    GPIOB
#define AT24C02_SCL_PIN  	    GPIO_Pin_7
#define AT24C02_SDA_GPIO 	    GPIOB
#define AT24C02_SDA_PIN  	    GPIO_Pin_6

/*�ܽſ���*/
#define AT24C02_SCL_STATE(x) (x)>0?GPIO_SetBits(AT24C02_SCL_GPIO,AT24C02_SCL_PIN):GPIO_ResetBits(AT24C02_SCL_GPIO,AT24C02_SCL_PIN)
#define AT24C02_SDA_STATE(x) (x)>0?GPIO_SetBits(AT24C02_SDA_GPIO,AT24C02_SDA_PIN):GPIO_ResetBits(AT24C02_SDA_GPIO,AT24C02_SDA_PIN)
#define AT24C02_SDA_GET() GPIO_ReadInputDataBit(AT24C02_SDA_GPIO,AT24C02_SDA_PIN)

void AT24C02IIC_Init(void);                											//��ʼ��IIC��IO��
void AT24C02IIC_Start(void);																			//����IIC��ʼ�ź�
void AT24C02IIC_Stop(void);	  																	//����IICֹͣ�ź�
void AT24C02IIC_Send_Byte(u8_t txd);																//IIC����һ���ֽ�
u8_t AT24C02IIC_Read_Byte(u8_t ack);											//IIC��ȡһ���ֽ�
u8_t AT24C02IIC_Wait_Ack(void); 																		//IIC�ȴ�ACK�ź�
void AT24C02IIC_Ack(void);																				//IIC����ACK�ź�
void AT24C02IIC_NAck(void);																			//IIC������ACK�ź�

void AT24C02IIC_Write_One_Byte(u8_t daddr,u8_t addr,u8_t data);
u8_t AT24C02IIC_Read_One_Byte(u8_t daddr,u8_t addr);

u8_t AT24C02_ReadOneByte(u16_t ReadAddr);																//ָ����ַ��ȡһ���ֽ�
void AT24C02_WriteOneByte(u16_t WriteAddr,u8_t DataToWrite);						//ָ����ַд��һ���ֽ�
void AT24C02_WriteLenByte(u16_t WriteAddr,u32_t DataToWrite,u8_t Len);		//ָ����ַ��ʼд��ָ�����ȵ�����
u32_t AT24C02_ReadLenByte(u16_t ReadAddr,u8_t Len);												//ָ����ַ��ʼ��ȡָ����������
void AT24C02_Write16bits(u16_t WriteAddr,u16_t DataToWrite);
u16_t AT24C02_Read16bits(u16_t ReadAddr);
void AT24C02_Init(void);																						 //��ʼ��IIC

#endif

