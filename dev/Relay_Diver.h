#ifndef __RELAY_DIVER_H_
#define __RELAY_DIVER_H_
#include "system_init.h"
#define HIGH 	1
#define LOW 	0
/*�ܽŶ���*/
#define RELAY1_GPIO 	GPIOA
#define RELAY1_PIN  	GPIO_Pin_6

#define RELAY2_GPIO 	GPIOA
#define RELAY2_PIN  	GPIO_Pin_7

#define RELAY3_GPIO 	GPIOB
#define RELAY3_PIN  	GPIO_Pin_2

#define RELAY4_GPIO 	GPIOC
#define RELAY4_PIN  	GPIO_Pin_11

#define RELAY5_GPIO 	GPIOC
#define RELAY5_PIN  	GPIO_Pin_10
                                                                            
#define RELAY6_GPIO 	GPIOB
#define RELAY6_PIN  	GPIO_Pin_9

#define RELAY7_GPIO 	GPIOB
#define RELAY7_PIN  	GPIO_Pin_5

#define RELAY8_GPIO 	GPIOB
#define RELAY8_PIN  	GPIO_Pin_14

#define RELAY9_GPIO 	GPIOC
#define RELAY9_PIN  	GPIO_Pin_13

#define RELAY1_STATE(x) (x)>0?GPIO_SetBits(RELAY1_GPIO,RELAY1_PIN):GPIO_ResetBits(RELAY1_GPIO,RELAY1_PIN)
#define RELAY2_STATE(x) (x)>0?GPIO_SetBits(RELAY2_GPIO,RELAY2_PIN):GPIO_ResetBits(RELAY2_GPIO,RELAY2_PIN)
#define RELAY3_STATE(x) (x)>0?GPIO_SetBits(RELAY3_GPIO,RELAY3_PIN):GPIO_ResetBits(RELAY3_GPIO,RELAY3_PIN)
#define RELAY4_STATE(x) (x)>0?GPIO_SetBits(RELAY4_GPIO,RELAY4_PIN):GPIO_ResetBits(RELAY4_GPIO,RELAY4_PIN)
#define RELAY5_STATE(x) (x)>0?GPIO_SetBits(RELAY5_GPIO,RELAY5_PIN):GPIO_ResetBits(RELAY5_GPIO,RELAY5_PIN)
#define RELAY6_STATE(x) (x)>0?GPIO_SetBits(RELAY6_GPIO,RELAY6_PIN):GPIO_ResetBits(RELAY6_GPIO,RELAY6_PIN)
#define RELAY7_STATE(x) (x)>0?GPIO_SetBits(RELAY7_GPIO,RELAY7_PIN):GPIO_ResetBits(RELAY7_GPIO,RELAY7_PIN)
#define RELAY8_STATE(x) (x)>0?GPIO_SetBits(RELAY8_GPIO,RELAY8_PIN):GPIO_ResetBits(RELAY8_GPIO,RELAY8_PIN)
#define RELAY9_STATE(x) (x)>0?GPIO_SetBits(RELAY9_GPIO,RELAY9_PIN):GPIO_ResetBits(RELAY9_GPIO,RELAY9_PIN)


void Relay_Init(void);
#endif
