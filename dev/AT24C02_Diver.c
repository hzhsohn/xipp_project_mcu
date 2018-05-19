#include "AT24C02_Diver.h"
#include "STM32_Delay.h"
/**************************************************************
函数名称：	ICC 管脚初始化
函数说明：
函出入口参数：
更改备注：
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
函数名称：	SDA设置成输入
函数说明：
函出入口参数：
更改备注：
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
函数名称：	SDA设置成输出
函数说明：
函出入口参数：
更改备注：
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
函数名称：	ICC 起始信号
函数说明：
函出入口参数：
更改备注：
**************************************************************/
void AT24C02IIC_Start(void)
{
	AT24C02_SDA_OUT();     																//sda线输出
	AT24C02_SDA_STATE(HIGH);
	AT24C02_SCL_STATE(HIGH);
	STM32_Delay_us(4);
  AT24C02_SDA_STATE(LOW);																		//START:when CLK is high,DATA change form high to low
	STM32_Delay_us(4);
	AT24C02_SCL_STATE(LOW);																		//钳住I2C总线，准备发送或接收数据
}
/**************************************************************
函数名称：	ICC 停止信号
函数说明：
函出入口参数：
更改备注：
**************************************************************/
void AT24C02IIC_Stop(void)
{
	AT24C02_SDA_OUT();																		//sda线输出
	AT24C02_SCL_STATE(LOW);
	AT24C02_SDA_STATE(LOW);																	//STOP:when CLK is high DATA change form low to high
 	STM32_Delay_us(4);
	AT24C02_SCL_STATE(HIGH);
	AT24C02_SDA_STATE(HIGH);																	//发送I2C总线结束信号
	STM32_Delay_us(4);
}

/**************************************************************
函数名称：	ICC 等待应答信号
函数说明：
函出入口参数：返回值：1，接收应答失败    0，接收应答成功
更改备注：
**************************************************************/
u8_t AT24C02IIC_Wait_Ack(void)
{
	u8_t ucErrTime=0;
	AT24C02_SDA_IN();      									//SDA设置为输入
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
	AT24C02_SCL_STATE(LOW);									//时钟输出0
	return 0;
}
/**************************************************************
函数名称：	ICC 产生ACK信号
函数说明：
函出入口参数：
更改备注：
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
函数名称：	ICC 不产生ACK信号
函数说明：
函出入口参数：
更改备注：
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
函数名称：	ICC 发送一个字节
函数说明：
函出入口参数：
更改备注：
**************************************************************/
void AT24C02IIC_Send_Byte(u8_t txd)
{
    u8_t t;
		AT24C02_SDA_OUT();
    AT24C02_SCL_STATE(LOW);												//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
			if((txd&0x80)>>7)
				AT24C02_SDA_STATE(HIGH);
			else
				AT24C02_SDA_STATE(LOW);
			txd<<=1;
			STM32_Delay_us(2);   									//对TEA5767这三个延时都是必须的
			AT24C02_SCL_STATE(HIGH);
			STM32_Delay_us(2);
			AT24C02_SCL_STATE(LOW);
			STM32_Delay_us(2);
    }
}

/**************************************************************
函数名称：	ICC 读一个字节
函数说明：
函出入口参数：返回值  读取的数值	 ack=1时 发送ACK，ack=0，发送nACK
更改备注：
**************************************************************/
u8_t AT24C02IIC_Read_Byte(u8_t ack)
{
	unsigned char i,receive=0;
	AT24C02_SDA_IN();													//SDA设置为输入
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
			AT24C02IIC_NAck();									//发送nACK
	else
			AT24C02IIC_Ack(); 									//发送ACK
	return receive;
}

/**************************************************************
函数名称：	AT24C02初始化
函数说明：
函出入口参数：
更改备注：
**************************************************************/
void AT24C02_Init(void)
{
	AT24C02IIC_Init();
}
/**************************************************************
函数名称：	AT24C02从一个地址读取一个数据
函数说明：
函出入口参数：
更改备注：
**************************************************************/
u8_t AT24C02_ReadOneByte(u16_t ReadAddr)
{
		u8_t temp=0;
		AT24C02IIC_Start();
		AT24C02IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   							//发送器件地址0XA0,写数据

		AT24C02IIC_Wait_Ack();
		AT24C02IIC_Send_Byte(ReadAddr%256);   												  //发送低地址
		AT24C02IIC_Wait_Ack();
		AT24C02IIC_Start();
		AT24C02IIC_Send_Byte(0XA1);           													//进入接收模式
		AT24C02IIC_Wait_Ack();
		temp=AT24C02IIC_Read_Byte(0);
		AT24C02IIC_Stop();																						  //产生一个停止条件
		return temp;
}
/**************************************************************
函数名称：	AT24C02往一个地址写入一个数据
函数说明：
函出入口参数：
更改备注：
**************************************************************/
void AT24C02_WriteOneByte(u16_t WriteAddr,u8_t DataToWrite)
{
		AT24C02IIC_Start();
		AT24C02IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   						//发送器件地址0XA0,写数据

		AT24C02IIC_Wait_Ack();
		AT24C02IIC_Send_Byte(WriteAddr%256);   											  //发送低地址
		AT24C02IIC_Wait_Ack();
		AT24C02IIC_Send_Byte(DataToWrite);     											  //发送字节
		AT24C02IIC_Wait_Ack();
		AT24C02IIC_Stop();																						  //产生一个停止条件
		STM32_Delay_ms(10);
}

/**************************************************************
函数名称：	AT24C02连续写入一个32位数据
函数说明：
函出入口参数：
更改备注：
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
函数名称：	AT24C02连续读出一个32位数据
函数说明：
函出入口参数：
更改备注：
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
