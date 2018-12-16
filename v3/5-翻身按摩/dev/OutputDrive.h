#ifndef __OUTPUT__DIVER__H___
#define __OUTPUT__DIVER__H___

#include "system_init.h"


//-----------------------------------------------
//保暖
#define RELAY1_GPIO 	GPIOC
#define RELAY1_PIN  	GPIO_Pin_6

#define RELAY2_GPIO 	GPIOC
#define RELAY2_PIN  	GPIO_Pin_9
//----------------------------------------------
//按摩
#define RELAY3_GPIO 	GPIOC
#define RELAY3_PIN  	GPIO_Pin_8

#define RELAY4_GPIO 	GPIOD
#define RELAY4_PIN  	GPIO_Pin_12

#define RELAY5_GPIO 	GPIOD
#define RELAY5_PIN  	GPIO_Pin_13
                                    
#define RELAY6_GPIO 	GPIOD
#define RELAY6_PIN  	GPIO_Pin_14

#define RELAY7_GPIO 	GPIOD
#define RELAY7_PIN  	GPIO_Pin_15

//--------------------------------------------------------
//自动储气罐开关 
#define RELAY8_GPIO 	GPIOE
#define RELAY8_PIN  	GPIO_Pin_7

//--------------------------------------------------------
//排污
#define RELAY9_GPIO 	GPIOE
#define RELAY9_PIN  	GPIO_Pin_8

#define RELAY10_GPIO 	GPIOE
#define RELAY10_PIN  	GPIO_Pin_9

//---------------------------------------------------------
//小便阀门
#define RELAY11_GPIO 	GPIOB
#define RELAY11_PIN  	GPIO_Pin_2

//---------------------------------------------------------
#define RELAY12_GPIO 	GPIOB
#define RELAY12_PIN  	GPIO_Pin_13

#define RELAY13_GPIO 	GPIOD
#define RELAY13_PIN  	GPIO_Pin_10

#define RELAY14_GPIO 	GPIOA
#define RELAY14_PIN  	GPIO_Pin_15

#define RELAY15_GPIO 	GPIOD
#define RELAY15_PIN  	GPIO_Pin_3

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
#define RELAY14_STATE(x) (!x)>0?GPIO_SetBits(RELAY14_GPIO,RELAY14_PIN):GPIO_ResetBits(RELAY14_GPIO,RELAY14_PIN)
#define RELAY15_STATE(x) (!x)>0?GPIO_SetBits(RELAY15_GPIO,RELAY15_PIN):GPIO_ResetBits(RELAY15_GPIO,RELAY15_PIN)

//初始化
void OutputDriveInit(void);

//继电器输出测试
void RelayTest(void);//
	
#endif
