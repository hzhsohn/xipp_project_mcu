#include "Stm32f1_ADC1.h"
#include "STM32_Delay.h"

/////////////////////////////////////////////////////////////////////////
//11111111111111111111111111111111111111111
void Adc1_Init(void)
{
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1        , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        ADC_DeInit(ADC1);  //��λADC1

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������
}

u16 Get_Adc1_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
			  //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}                    

////////////////////////////////////////////////////////////////////////////////////
//222222222222222222222222222222222
void Adc2_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOA, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc2_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}


////////////////////////////////////////////////////////////////////////////////////
//3333333333333333333333333333333333333333
void Adc3_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOA, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc3_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}

////////////////////////////////////////////////////////////////////////////////////
//44444444444444444444444
void Adc4_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc4_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}

////////////////////////////////////////////////////////////////////////////////////
//5555555555555555555555555555555
void Adc5_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOA, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc5_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}

////////////////////////////////////////////////////////////////////////////////////
//666666666666666666666666666666
void Adc6_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOA, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc6_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}

////////////////////////////////////////////////////////////////////////////////////
//777777777777777777777777777777777777
void Adc7_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOA, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc7_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}

////////////////////////////////////////////////////////////////////////////////////
//88888888888888888888888888888888
void Adc8_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc8_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}
////////////////////////////////////////////////////////////////////////////////////
//999999999999999999999999999999
void Adc9_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc9_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}
////////////////////////////////////////////////////////////////////////////////////
//10
void Adc10_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc10_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}
////////////////////////////////////////////////////////////////////////////////////
//11
void Adc11_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc11_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}
////////////////////////////////////////////////////////////////////////////////////
//12
void Adc12_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOB, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc12_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}
////////////////////////////////////////////////////////////////////////////////////
//13
void Adc13_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
   
u16 Get_Adc13_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}
////////////////////////////////////////////////////////////////////////////////////
//14
void Adc14_Init(void)
{         
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //ʹ��ADC1ͨ��ʱ��
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

        //PA1 ��Ϊģ��ͨ����������                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //ģ����������
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //��λADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //ģ��ת�������ڵ�ͨ��ģʽ
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ģ��ת�������ڵ���ת��ģʽ
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת��������������ⲿ��������
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //˳����й���ת����ADCͨ������Ŀ
        ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

        ADC_Cmd(ADC1, ENABLE);        //ʹ��ָ����ADC1
        ADC_ResetCalibration(ADC1);        //ʹ�ܸ�λУ׼  
        while(ADC_GetResetCalibrationStatus(ADC1));        //�ȴ���λУ׼����
        ADC_StartCalibration(ADC1);         //����ADУ׼
        while(ADC_GetCalibrationStatus(ADC1));         //�ȴ�У׼����
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������
}
   
u16 Get_Adc14_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
				ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
				temp_val1+=ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}

