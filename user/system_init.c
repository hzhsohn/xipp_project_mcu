#include "system_init.h"
#include "BeeSpeaker_Diver.h"
#include "Stm32F1_Timer3.h"
#include "TouchKey_Diver.h"
#include "AT24C02_Diver.h"
#include "STM32_Delay.h"
#include "Relay_Diver.h"
#include "Sensor.h"
#include "Stm32f1_uart1_diver.h"
#include "Stm32f1_uart2_diver.h"
#include "Stm32f1_uart3_diver.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1_Diver.h"
#include "Stm32f1_ADC2_Diver.h"
#include "Motor_Diver.h"
#include "ds18b20_1.h"

void System_Init(void)
{
		STM32_Delay_init();
		//	AT24C02IIC_Init();
		Relay_Init();
		LED_Configuration();
		//BeeSpeak_Init();
		Sensor_Init();
		TouchKey_Init();
		Stm32F1_Timer3Init();
		STM32F1_UART1_Init(115200);
		STM32F1_UART2_Init(230400);
		STM32F1_UART3_Init(115200);
		DS18B20_Init();
		DS18B20_Init1();
		Adc_Init();
		Adc2_Init();
		Motor_Init();
		//	x =AT24C02_ReadOneByte(0x00);
		//AT24C02_WriteOneByte(0x00,0xaa);
		//	x =AT24C02_ReadOneByte(0x00);
}
