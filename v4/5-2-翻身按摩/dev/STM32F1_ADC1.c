#include "Stm32f1_ADC1.h"
#include "STM32_Delay.h"

/////////////////////////////////////////////////////////////////////////
//11111111111111111111111111111111111111111
void Adc1_Init(void)
{
        ADC_InitTypeDef ADC_InitStructure; 
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1        , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        ADC_DeInit(ADC1);  //复位ADC1

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能
}

u16 Get_Adc1_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
			  //设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOA, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc2_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOA, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc3_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc4_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOA, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc5_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOA, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc6_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOA, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc7_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc8_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc9_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc10_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc11_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOB, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc12_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能

}    
   
u16 Get_Adc13_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1  , ENABLE );          //使能ADC1通道时钟
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

        //PA1 作为模拟通道输入引脚                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                //模拟输入引脚
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        ADC_DeInit(ADC1);  //复位ADC1 

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC工作模式:ADC1和ADC2工作在独立模式
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;        //模数转换工作在单通道模式
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //模数转换工作在单次转换模式
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件而不是外部触发启动
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
        ADC_InitStructure.ADC_NbrOfChannel = 2;        //顺序进行规则转换的ADC通道的数目
        ADC_Init(ADC1, &ADC_InitStructure);        //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

        ADC_Cmd(ADC1, ENABLE);        //使能指定的ADC1
        ADC_ResetCalibration(ADC1);        //使能复位校准  
        while(ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
        ADC_StartCalibration(ADC1);         //开启AD校准
        while(ADC_GetCalibrationStatus(ADC1));         //等待校准结束
//      ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能
}
   
u16 Get_Adc14_Average(u8 times)
{
        u32 temp_val1=0;
        u8 t1;
        for(t1=0;t1<times;t1++)
        {
				//设置指定ADC的规则组通道，一个序列，采样时间
				ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 2, ADC_SampleTime_239Cycles5 );        //ADC1,ADC通道,采样时间为239.5周期                                      
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);                //使能指定的ADC1的软件转换启动功能        
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
				temp_val1+=ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
                STM32_Delay_ms(5);
        }
        return temp_val1/times;
}

