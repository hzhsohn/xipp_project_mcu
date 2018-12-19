#include "system_init.h"
#include "Stm32f1_uart1.h"
#include "Stm32f1_uart2.h"
#include "Stm32f1_uart3.h"
#include "InputDrive.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1.h"
#include "Stm32f1_ADC2.h"
#include "ds18b20_1.h"
#include "watchdog.h"
#include "flash_rw.h"
#include "Stm32F1_Timer2.h"
#include "Stm32F1_Timer3.h"
#include "key.h"
#include "OutputDrive.h"


//
void delay_s(int n)
{
		int i=0;
		for(i=0;i<n*10;i++)
		{ STM32_Delay_ms(100); }
}

/*


*/
void openGuiZi(void)
{
			int n=0,m=0;	
			if(!SENSOR5_STATE())
			{
				_unit1(1);
				_unit2(0);
				while(!SENSOR5_STATE()); //this have bug,for line unok
			}
			_unit1(0);
			_unit2(0);
			
			//
			if(!SENSOR8_STATE())
			{
				_unit3(0);
				_unit4(1);
				while(!SENSOR8_STATE()); //this have bug,for line unok
			}
			
			_unit3(0);
			_unit4(0);
}

void closeGuiZi(void)
{
			if(!SENSOR7_STATE())
			{
				_unit3(1);
				_unit4(0);
				while(!SENSOR7_STATE()); //this have bug,for line unok
			}
			_unit3(0);
			_unit4(0);			
			
			if(!SENSOR4_STATE())
			{
				_unit1(0);
				_unit2(1);
				while(!SENSOR4_STATE()); //this have bug,for line unok
			}			
			_unit1(0);
			_unit2(0);
}




