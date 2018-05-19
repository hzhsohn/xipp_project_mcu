#include "AT24C02_Diver.h"
#include "STM32_Delay.h"
/**************************************************************
�������ƣ�	ICC �ܽų�ʼ��
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/*SCL*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_MyStruct.GPIO_Pin = AT24C02_SCL_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(AT24C02_SCL_GPIO, &GPIO_MyStruct);
    /*SDA*/
	GPIO_MyStruct.GPIO_Pin  = AT24C02_SDA_PIN;
	GPIO_MyStruct.GPIO_Pin = AT24C02_SDA_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(AT24C02_SDA_GPIO, &GPIO_MyStruct);

}
/**************************************************************
�������ƣ�	SDA���ó�����
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02_SDA_IN(void)
{

	GPIO_InitTypeDef GPIO_MyStruct;
	GPIO_MyStruct.GPIO_Pin = AT24C02_SDA_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(AT24C02_SDA_GPIO, &GPIO_MyStruct);
}
/**************************************************************
�������ƣ�	SDA���ó����
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	GPIO_MyStruct.GPIO_Pin = AT24C02_SDA_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(AT24C02_SDA_GPIO, &GPIO_MyStruct);
}

/**************************************************************
�������ƣ�	ICC ��ʼ�ź�
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02IIC_Start(void)
{
	AT24C02_SDA_OUT();     																//sda�����
	AT24C02_SDA_STATE(HIGH);
	AT24C02_SCL_STATE(HIGH);
	STM32_Delay_us(4);
  AT24C02_SDA_STATE(LOW);																		//START:when CLK is high,DATA change form high to low
	STM32_Delay_us(4);
	AT24C02_SCL_STATE(LOW);																		//ǯסI2C���ߣ�׼�����ͻ��������
}
/**************************************************************
�������ƣ�	ICC ֹͣ�ź�
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02IIC_Stop(void)
{
	AT24C02_SDA_OUT();																		//sda�����
	AT24C02_SCL_STATE(LOW);
	AT24C02_SDA_STATE(LOW);																	//STOP:when CLK is high DATA change form low to high
 	STM32_Delay_us(4);
	AT24C02_SCL_STATE(HIGH);
	AT24C02_SDA_STATE(HIGH);																	//����I2C���߽����ź�
	STM32_Delay_us(4);
}

/**************************************************************
�������ƣ�	ICC �ȴ�Ӧ���ź�
����˵����
������ڲ���������ֵ��1������Ӧ��ʧ��    0������Ӧ��ɹ�
���ı�ע��
**************************************************************/
u8_t AT24C02IIC_Wait_Ack(void)
{
	u8_t ucErrTime=0;
	AT24C02_SDA_IN();      									//SDA����Ϊ����
	AT24C02_SDA_STATE(HIGH);
	STM32_Delay_us(1);
	AT24C02_SCL_STATE(HIGH);
    STM32_Delay_us(1);
	while(AT24C02_SDA_GET())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			AT24C02IIC_Stop();
			return 1;
		}
	}
	AT24C02_SCL_STATE(LOW);									//ʱ�����0
	return 0;
}
/**************************************************************
�������ƣ�	ICC ����ACK�ź�
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02IIC_Ack(void)
{
	AT24C02_SCL_STATE(LOW);
	AT24C02_SDA_OUT();
	AT24C02_SDA_STATE(LOW);
	STM32_Delay_us(2);
	AT24C02_SCL_STATE(LOW);
	STM32_Delay_us(2);
	AT24C02_SCL_STATE(LOW);
}
/**************************************************************
�������ƣ�	ICC ������ACK�ź�
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02IIC_NAck(void)
{
	AT24C02_SCL_STATE(LOW);
	AT24C02_SDA_OUT();
	AT24C02_SDA_STATE(HIGH);
	STM32_Delay_us(2);
	AT24C02_SCL_STATE(HIGH);
	STM32_Delay_us(2);
	AT24C02_SCL_STATE(LOW);
}

/**************************************************************
�������ƣ�	ICC ����һ���ֽ�
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02IIC_Send_Byte(u8_t txd)
{
    u8_t t;
		AT24C02_SDA_OUT();
    AT24C02_SCL_STATE(LOW);												//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {
			if((txd&0x80)>>7)
				AT24C02_SDA_STATE(HIGH);
			else
				AT24C02_SDA_STATE(LOW);
			txd<<=1;
			STM32_Delay_us(2);   									//��TEA5767��������ʱ���Ǳ����
			AT24C02_SCL_STATE(HIGH);
			STM32_Delay_us(2);
			AT24C02_SCL_STATE(LOW);
			STM32_Delay_us(2);
    }
}

/**************************************************************
�������ƣ�	ICC ��һ���ֽ�
����˵����
������ڲ���������ֵ  ��ȡ����ֵ	 ack=1ʱ ����ACK��ack=0������nACK
���ı�ע��
**************************************************************/
u8_t AT24C02IIC_Read_Byte(u8_t ack)
{
	unsigned char i,receive=0;
	AT24C02_SDA_IN();													//SDA����Ϊ����
  for(i=0;i<8;i++ )
	{
        AT24C02_SCL_STATE(LOW);
        STM32_Delay_us(2);
			AT24C02_SCL_STATE(HIGH);
        receive<<=1;
        if(AT24C02_SDA_GET()) receive++;
				STM32_Delay_us(1);
  }
	if (!ack)
			AT24C02IIC_NAck();									//����nACK
	else
			AT24C02IIC_Ack(); 									//����ACK
	return receive;
}

/**************************************************************
�������ƣ�	AT24C02��ʼ��
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02_Init(void)
{
	AT24C02IIC_Init();
}
/**************************************************************
�������ƣ�	AT24C02��һ����ַ��ȡһ������
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
u8_t AT24C02_ReadOneByte(u16_t ReadAddr)
{
		u8_t temp=0;
		AT24C02IIC_Start();
		AT24C02IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   							//����������ַ0XA0,д����

		AT24C02IIC_Wait_Ack();
		AT24C02IIC_Send_Byte(ReadAddr%256);   												  //���͵͵�ַ
		AT24C02IIC_Wait_Ack();
		AT24C02IIC_Start();
		AT24C02IIC_Send_Byte(0XA1);           													//�������ģʽ
		AT24C02IIC_Wait_Ack();
		temp=AT24C02IIC_Read_Byte(0);
		AT24C02IIC_Stop();																						  //����һ��ֹͣ����
		return temp;
}
/**************************************************************
�������ƣ�	AT24C02��һ����ַд��һ������
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02_WriteOneByte(u16_t WriteAddr,u8_t DataToWrite)
{
		AT24C02IIC_Start();
		AT24C02IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   						//����������ַ0XA0,д����

		AT24C02IIC_Wait_Ack();
		AT24C02IIC_Send_Byte(WriteAddr%256);   											  //���͵͵�ַ
		AT24C02IIC_Wait_Ack();
		AT24C02IIC_Send_Byte(DataToWrite);     											  //�����ֽ�
		AT24C02IIC_Wait_Ack();
		AT24C02IIC_Stop();																						  //����һ��ֹͣ����
		STM32_Delay_ms(10);
}

/**************************************************************
�������ƣ�	AT24C02����д��һ��32λ����
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
void AT24C02_WriteLenByte(u16_t WriteAddr,u32_t DataToWrite,u8_t Len)
{
	u8_t t;
	for(t=0;t<Len;t++)
	{
		AT24C02_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}
}
/**************************************************************
�������ƣ�	AT24C02��������һ��32λ����
����˵����
������ڲ�����
���ı�ע��
**************************************************************/
u32_t AT24C02_ReadLenByte(u16_t ReadAddr,u8_t Len)
{
	u8_t t;
	u32_t temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24C02_ReadOneByte(ReadAddr+Len-t-1);
	}
	return temp;
}
void AT24C02_Write16bits(u16_t WriteAddr,u16_t DataToWrite)
{
	u8_t nDataBuffHigh;
	u8_t nDataBuffLow;
	nDataBuffHigh = (DataToWrite>>8);
	nDataBuffLow = DataToWrite&0xff;
	AT24C02_WriteOneByte(WriteAddr,nDataBuffHigh);
	AT24C02_WriteOneByte(WriteAddr+1,nDataBuffLow);
}
u16_t AT24C02_Read16bits(u16_t ReadAddr)
{
	u8_t nDataBuffHigh;
	u8_t nDataBuffLow;
	u16_t sDataBuff;
	nDataBuffHigh = AT24C02_ReadOneByte(ReadAddr);
	nDataBuffLow = AT24C02_ReadOneByte(ReadAddr+1);
	sDataBuff = nDataBuffHigh;
	sDataBuff = sDataBuff<<8;
	sDataBuff = sDataBuff + nDataBuffLow;
	return sDataBuff;
}
