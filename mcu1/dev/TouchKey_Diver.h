#ifndef __TOUCHKEY_DIVER_H_
#define __TOUCHKEY_DIVER_H_
#include "system_init.h"

#define TOUCHKEY_NONE_VALUE                     0x00
#define TOUCHKEY_BUTTON1_VALUE									0x01
#define TOUCHKEY_BUTTON2_VALUE									0x02
#define TOUCHKEY_BUTTON3_VALUE									0x04
#define TOUCHKEY_BUTTON4_VALUE									0x08
#define TOUCHKEY_BUTTON5_VALUE									0x10
#define TOUCHKEY_BUTTON6_VALUE									0x20
#define TOUCHKEY_BUTTON7_VALUE									0x40
#define TOUCHKEY_BUTTON8_VALUE									0x80

#define TOUCHKEY_FLASCHECK_10MS                 30
#define TOUCHKEY_SHORTDOWN_10MS                 50
#define TOUCHKEY_LONGDOWN_10MS                  100
/*管脚定义*/
#define TOUCHKEY_TURNON_GPIO 	          
#define TOUCHKEY_TURNON_PIN  			      

#define TOUCHKEY_1_GPIO 			    			GPIOC
#define TOUCHKEY_1_PIN  				    		GPIO_Pin_6

#define TOUCHKEY_2_GPIO 			    			GPIOB
#define TOUCHKEY_2_PIN  				  			GPIO_Pin_0

#define TOUCHKEY_3_GPIO 			    			GPIOC
#define TOUCHKEY_3_PIN  				  			GPIO_Pin_5

#define TOUCHKEY_4_GPIO 				    		GPIOC
#define TOUCHKEY_4_PIN  				    		GPIO_Pin_0

#define TOUCHKEY_5_GPIO 								GPIOA
#define TOUCHKEY_5_PIN  								GPIO_Pin_7

#define TOUCHKEY_6_GPIO 								GPIOA
#define TOUCHKEY_6_PIN  								GPIO_Pin_6

#define TOUCHKEY_7_GPIO 								GPIOC
#define TOUCHKEY_7_PIN  								GPIO_Pin_4

#define TOUCHKEY_8_GPIO 								GPIOE
#define TOUCHKEY_8_PIN  								GPIO_Pin_1

/*管脚控制*/
#define TOUCHKEY_1_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_1_GPIO,TOUCHKEY_1_PIN)
#define TOUCHKEY_2_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_2_GPIO,TOUCHKEY_2_PIN)
#define TOUCHKEY_3_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_3_GPIO,TOUCHKEY_3_PIN)
#define TOUCHKEY_4_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_4_GPIO,TOUCHKEY_4_PIN)
#define TOUCHKEY_5_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_5_GPIO,TOUCHKEY_5_PIN)
#define TOUCHKEY_6_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_6_GPIO,TOUCHKEY_6_PIN)
#define TOUCHKEY_7_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_7_GPIO,TOUCHKEY_7_PIN)
#define TOUCHKEY_8_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_8_GPIO,TOUCHKEY_8_PIN)


void TouchKey_Init(void);
u8_t TouchKey_Collect(void);
void TouchKey_Scan(void);
void TOUCHKEY_TIMER_ISR(void);
#endif
