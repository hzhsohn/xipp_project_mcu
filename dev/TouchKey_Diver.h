#ifndef __TOUCHKEY_DIVER_H_
#define __TOUCHKEY_DIVER_H_
#include "system_init.h"

#define TOUCHKEY_NONE_VALUE                     0xFF
#define TOUCHKEY_TURNON_VALUE										0xFE
#define TOUCHKEY_BUTTON1_VALUE									0xFD
#define TOUCHKEY_BUTTON2_VALUE									0xFB
#define TOUCHKEY_BUTTON3_VALUE									0xF7
#define TOUCHKEY_BUTTON4_VALUE									0xEF
#define TOUCHKEY_BUTTON5_VALUE									0xDF
#define TOUCHKEY_BUTTON6_VALUE									0xBF
#define TOUCHKEY_BUTTON7_VALUE									0x7F

#define TOUCHKEY_FLASCHECK_10MS                 30
#define TOUCHKEY_SHORTDOWN_10MS                 50
#define TOUCHKEY_LONGDOWN_10MS                  100
/*管脚定义*/
#define TOUCHKEY_TURNON_GPIO 	          
#define TOUCHKEY_TURNON_PIN  			      

#define TOUCHKEY_1_GPIO 			    			GPIOA
#define TOUCHKEY_1_PIN  				    		GPIO_Pin_12

#define TOUCHKEY_2_GPIO 			    			GPIOC
#define TOUCHKEY_2_PIN  				  			GPIO_Pin_7

#define TOUCHKEY_3_GPIO 			    			GPIOA
#define TOUCHKEY_3_PIN  				  			GPIO_Pin_2

#define TOUCHKEY_4_GPIO 				    		GPIOA
#define TOUCHKEY_4_PIN  				    		GPIO_Pin_3

#define TOUCHKEY_5_GPIO 								GPIOA
#define TOUCHKEY_5_PIN  								GPIO_Pin_15

#define TOUCHKEY_6_GPIO 								GPIOC
#define TOUCHKEY_6_PIN  								GPIO_Pin_4

#define TOUCHKEY_7_GPIO 								GPIOC
#define TOUCHKEY_7_PIN  								GPIO_Pin_5

/*管脚控制*/
#define TOUCHKEY_1_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_1_GPIO,TOUCHKEY_1_PIN)
#define TOUCHKEY_2_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_2_GPIO,TOUCHKEY_2_PIN)
#define TOUCHKEY_3_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_3_GPIO,TOUCHKEY_3_PIN)
#define TOUCHKEY_4_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_4_GPIO,TOUCHKEY_4_PIN)
#define TOUCHKEY_5_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_5_GPIO,TOUCHKEY_5_PIN)
#define TOUCHKEY_6_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_6_GPIO,TOUCHKEY_6_PIN)
#define TOUCHKEY_7_STATE() 							GPIO_ReadInputDataBit(TOUCHKEY_7_GPIO,TOUCHKEY_7_PIN)
void TouchKey_Init(void);
u8_t TouchKey_Collect(void);
void TouchKey_Scan(void);
void TOUCHKEY_TIMER_ISR(void);
#endif
