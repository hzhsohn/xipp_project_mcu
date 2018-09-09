#include "Stm32f1_ADC2_Diver.h"
#include "STM32_Delay.h"

//****************************************************************************
//*�������ܣ�
//*������
//*������
//****************************************************************************
void Adc2_Init(void)
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

//        ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������

}    
u16 Get_Adc11(u8 ch)   
{
          //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
        ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADCͨ��,����ʱ��Ϊ239.5����                                      
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //ʹ��ָ����ADC1�����ת����������        
        while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
        return ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
} 
   
u16 Get_Adc2_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
                        temp_val1+=Get_Adc11(ADC_Channel_11);
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}                    
