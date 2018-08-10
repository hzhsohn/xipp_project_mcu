#ifndef __RELAY_DIVER_H_
#define __RELAY_DIVER_H_
#include "system_init.h"
#define HIGH 	1
#define LOW 	0
/*管脚定义*/
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

#define RELAY10_GPIO 	GPIOB
#define RELAY10_PIN  	GPIO_Pin_13

#define RELAY11_GPIO 	GPIOC
#define RELAY11_PIN  	GPIO_Pin_8

#define RELAY12_GPIO 	GPIOA
#define RELAY12_PIN  	GPIO_Pin_8

#define RELAY13_GPIO 	GPIOD
#define RELAY13_PIN  	GPIO_Pin_2


#define RELAY1_STATE(x) (!x)>0?GPIO_SetBits(RELAY1_GPIO,RELAY1_PIN):GPIO_ResetBits(RELAY1_GPIO,RELAY1_PIN)
#define RELAY2_STATE(x) (!x)>0?GPIO_SetBits(RELAY2_GPIO,RELAY2_PIN):GPIO_ResetBits(RELAY2_GPIO,RELAY2_PIN)
#define RELAY3_STATE(x) (!x)>0?GPIO_SetBits(RELAY3_GPIO,RELAY3_PIN):GPIO_ResetBits(RELAY3_GPIO,RELAY3_PIN)
#define RELAY4_STATE(x) (!x)>0?GPIO_SetBits(RELAY4_GPIO,RELAY4_PIN):GPIO_ResetBits(RELAY4_GPIO,RELAY4_PIN)
#define RELAY5_STATE(x) (!x)>0?GPIO_SetBits(RELAY5_GPIO,RELAY5_PIN):GPIO_ResetBits(RELAY5_GPIO,RELAY5_PIN)
#define RELAY6_STATE(x) (!x)>0?GPIO_SetBits(RELAY6_GPIO,RELAY6_PIN):GPIO_ResetBits(RELAY6_GPIO,RELAY6_PIN)
#define RELAY7_STATE(x) (!x)>0?GPIO_SetBits(RELAY7_GPIO,RELAY7_PIN):GPIO_ResetBits(RELAY7_GPIO,RELAY7_PIN)
#define RELAY8_STATE(x) (!x)>0?GPIO_SetBits(RELAY8_GPIO,RELAY8_PIN):GPIO_ResetBits(RELAY8_GPIO,RELAY8_PIN)
#define RELAY9_STATE(x) (!x)>0?GPIO_SetBits(RELAY9_GPIO,RELAY9_PIN):GPIO_ResetBits(RELAY9_GPIO,RELAY9_PIN)
#define RELAY10_STATE(x) (!x)>0?GPIO_SetBits(RELAY10_GPIO,RELAY10_PIN):GPIO_ResetBits(RELAY10_GPIO,RELAY10_PIN)
#define RELAY11_STATE(x) (!x)>0?GPIO_SetBits(RELAY11_GPIO,RELAY11_PIN):GPIO_ResetBits(RELAY11_GPIO,RELAY11_PIN)
#define RELAY12_STATE(x) (!x)>0?GPIO_SetBits(RELAY12_GPIO,RELAY12_PIN):GPIO_ResetBits(RELAY12_GPIO,RELAY12_PIN)
#define RELAY13_STATE(x) (!x)>0?GPIO_SetBits(RELAY13_GPIO,RELAY13_PIN):GPIO_ResetBits(RELAY13_GPIO,RELAY13_PIN)

#define LED1_OFF 		GPIO_ResetBits(GPIOC , GPIO_Pin_4)
#define LED1_ON 		GPIO_SetBits(GPIOC , GPIO_Pin_4)
#define LED1_RE 		GPIO_WriteBit(GPIOC , GPIO_Pin_4,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_4)));

void LED_Configuration(void);
void Relay_Init(void);

//继电器输出测试
void RelayTest(void);//
	
#endif
