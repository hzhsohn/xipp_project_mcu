#include "system_init.h"
#include "BeeSpeaker_Diver.h"
#include "Stm32F1_Timer3.h"
#include "TouchKey_Diver.h"
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

void Code_Init(void)
{

	 /*!< RCC system reset(for debug purpose) */
  /*!< Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;
  /*!< Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], ADCPRE[1:0] and MCO[2:0] bits */
  RCC->CFGR &= (uint32_t)0xF8FF0000;  
  /*!< Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;
  /*!< Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;
  /*!< Reset PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;
  /*!< Disable all interrupts */
  RCC->CIR = 0x00000000;
    

		SystemInit();	
		SystemCoreClockUpdate();
		STM32_Delay_init();
		STM32F1_UART1_Init(115200);
		STM32F1_UART2_Init(230400);
		STM32F1_UART3_Init(115200);

		Relay_Init();
		LED_Configuration();
		Sensor_Init();
		TouchKey_Init();
		Stm32F1_Timer3Init();
		DS18B20_Init();
		DS18B20_Init1();
		Adc_Init();
		Adc2_Init();
		Motor_Init();
}
