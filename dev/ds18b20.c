#include "ds18b20.h"

//��ʼ��DS18B20��IO�� DQ ͬʱ���DS�Ĵ���
//����1:������
//����0:����    	 
u8 DS18B20_Init()
{
	GPIO_InitTypeDef GPIO_MyStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_MyStruct.GPIO_Pin = DS18B20_DQ_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(DS18B20_DQ_GPIO, &GPIO_MyStruct);
	
	DS18B20_Rst();
	
	return DS18B20_Check();
}

void DS18B20_DQ_IN(void)
{

	GPIO_InitTypeDef GPIO_MyStruct;
	GPIO_MyStruct.GPIO_Pin = DS18B20_DQ_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(DS18B20_DQ_GPIO, &GPIO_MyStruct);
}
//channel:0~7
//status:0---low,1---high
void DS18B20_DQ_OUT(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	GPIO_MyStruct.GPIO_Pin = DS18B20_DQ_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(DS18B20_DQ_GPIO, &GPIO_MyStruct);
}

//��λDS18B20
void DS18B20_Rst()	   
{     
	DS18B20_DQ_OUT();	//����Ϊ���
	DS18B20_DQ_STATE(0);	//����DQ
	STM32_Delay_us(750);      		//����750us
	DS18B20_DQ_STATE(1);  	//DQ=1 
	STM32_Delay_us(15);       		//15US
}

//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
u8 DS18B20_Check() 	   
{   
	u8 retry=0;
	DS18B20_DQ_IN();    //����Ϊ����
	while(DS18B20_DQ_GET()&&retry<200)
	{
		retry++;
		STM32_Delay_us(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while(!DS18B20_DQ_GET()&&retry<240)
	{
		retry++;
		STM32_Delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}

//��DS18B20��ȡһ��λ
//����ֵ��1/0
u8 DS18B20_Read_Bit() 
{
	u8 data;
	
	DS18B20_DQ_OUT();		//����Ϊ���
	DS18B20_DQ_STATE(0);	
	STM32_Delay_us(2);
	DS18B20_DQ_STATE(1);	

	DS18B20_DQ_IN();    	//����Ϊ����
	STM32_Delay_us(12);
	if(DS18B20_DQ_GET())data=1;
	else data=0;	 
	STM32_Delay_us(50);
	
	return data;
}

//��DS18B20��ȡһ���ֽ�
//����ֵ������������
u8 DS18B20_Read_Byte()   
{        
	u8 i,j,dat;
	
	dat=0;
	for(i=1;i<=8;i++) 
	{
		j=DS18B20_Read_Bit();
		dat=(j<<7)|(dat>>1);
	}
	
	return dat;
}

//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
void DS18B20_Write_Byte(u8 dat)     
 {             
    u8 j;
    u8 testb;
	 
	DS18B20_DQ_OUT();		//����Ϊ���
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if(testb)       // д1
        {
			DS18B20_DQ_STATE(0);	
            STM32_Delay_us(2);                            
			DS18B20_DQ_STATE(1);	
			STM32_Delay_us(60);             
        }
        else            //д0
        {
			DS18B20_DQ_STATE(0);
            STM32_Delay_us(60);             
			DS18B20_DQ_STATE(1);
            STM32_Delay_us(2);                          
        }
    }
}
 
//��ʼ�¶�ת��
void DS18B20_Start()
{   						               
    DS18B20_Rst();	   
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0x44);// convert
}



//��ds18b20�õ��¶�ֵ��δCRCУ��
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250��,�Ŵ�ʮ������һλС����
//����״ֵ̬��0x7FFF(�Զ������״̬)---δ�ӻ�DQ�͵�ԴGND���ߣ�DQ���ԴVCC,GND��·��
//			  850(��̽ͷ������ֵ)---һֱδ�仯���ԴVCC����,�����ϵ�Ĭ��ֵ��
//			  0x7FFE(�Զ������״̬)---����̽ͷ��߲ɼ���Χ	
//			  0x7FFD(�Զ������״̬)---�ͳ�̽ͷ��Ͳɼ���Χ	
s16 DS18B20_Get_Temp()
{
    u8 temp;
    u8 TL,TH;
    s16 tem;
	
    DS18B20_Start();           	//��ʼת��
    DS18B20_Rst();
    if(DS18B20_Check()) return 0x7FFF; 
    DS18B20_Write_Byte(0xcc);  // skip rom
    DS18B20_Write_Byte(0xbe);  // convert	    	
    TL=DS18B20_Read_Byte();     	// LSB   
    TH=DS18B20_Read_Byte();    	// MSB   
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;//�¶�Ϊ��  
    }else temp=1;//�¶�Ϊ��	  	  
    tem=TH; //��ø߰�λ
    tem<<=8;    
    tem+=TL;//��õװ�λ
    tem=(double)tem*0.625;//ת��     
	temp += tem;
	
	if(temp)
	{
		if(tem > 1250) return 0x7FFE;
		return tem;
	}
	else
	{
		if(tem > 550) return 0x7FFD;
		return -tem;
	}
}
