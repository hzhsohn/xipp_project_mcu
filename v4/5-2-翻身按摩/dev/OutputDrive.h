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
#define RELAY3_PIN  	GPIO_Pin_8// 电源

#define RELAY4_GPIO 	GPIOD
#define RELAY4_PIN  	GPIO_Pin_12

#define RELAY5_GPIO 	GPIOD
#define RELAY5_PIN  	GPIO_Pin_13  //faqi
                                    
#define RELAY6_GPIO 	GPIOD
#define RELAY6_PIN  	GPIO_Pin_14

#define RELAY7_GPIO 	GPIOD
#define RELAY7_PIN  	GPIO_Pin_15 //qy kai

//--------------------------------------------------------
//自动储气罐充气阀
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
//气垫阀门

//				充气阀			REL_1
//				放气阀			REL_2

//				头充气			REL_3
//				头放气			REL_4

//左肩充气			REL_L1		REL_R1		右肩充气
//左肩放气			REL_L2		REL_R2		右肩放气

//左腰充气			REL_L3		REL_R3		右腰充气
//左腰放气			REL_L4		REL_R4		右腰放气

//左屁股充气			REL_L5		REL_R5		右屁股充气
//左屁股放气			REL_L6		REL_R6		右屁股放气

//左大腿充气			REL_L7		REL_R7		右大腿充气
//左大腿放气			REL_L8		REL_R8		右大腿放气

//左小腿充气			REL_L9		REL_R9		右小腿充气
//左小腿放气			REL_L10		REL_R10		右小腿放气

//左脚充气			REL_L11		REL_R11		右脚充气
//左脚放气			REL_L12		REL_R12		右脚放气

#define REL_1_GPIO 		GPIOE
#define REL_1_PIN  		GPIO_Pin_6

#define REL_2_GPIO 		GPIOE
#define REL_2_PIN  		GPIO_Pin_5

#define REL_3_GPIO 		GPIOE
#define REL_3_PIN  		GPIO_Pin_4

#define REL_4_GPIO 		GPIOE
#define REL_4_PIN  		GPIO_Pin_3


#define REL_L1_GPIO 	GPIOE
#define REL_L1_PIN  	GPIO_Pin_2

#define REL_L2_GPIO 	GPIOE
#define REL_L2_PIN  	GPIO_Pin_1

#define REL_L3_GPIO 	GPIOE
#define REL_L3_PIN  	GPIO_Pin_0

#define REL_L4_GPIO 	GPIOB
#define REL_L4_PIN  	GPIO_Pin_6

#define REL_L5_GPIO 	GPIOB
#define REL_L5_PIN  	GPIO_Pin_5

#define REL_L6_GPIO 	GPIOD
#define REL_L6_PIN  	GPIO_Pin_1

#define REL_L7_GPIO 	GPIOD
#define REL_L7_PIN  	GPIO_Pin_0

#define REL_L8_GPIO 	GPIOD
#define REL_L8_PIN  	GPIO_Pin_7

#define REL_L9_GPIO 	GPIOD
#define REL_L9_PIN  	GPIO_Pin_6

#define REL_L10_GPIO 	GPIOD
#define REL_L10_PIN  	GPIO_Pin_5

#define REL_L11_GPIO 	GPIOD
#define REL_L11_PIN  	GPIO_Pin_4

#define REL_L12_GPIO 	GPIOD
#define REL_L12_PIN  	GPIO_Pin_3


#define REL_R1_GPIO 	GPIOD
#define REL_R1_PIN  	GPIO_Pin_11

#define REL_R2_GPIO 	GPIOC
#define REL_R2_PIN  	GPIO_Pin_7

#define REL_R3_GPIO 	GPIOD
#define REL_R3_PIN  	GPIO_Pin_9

#define REL_R4_GPIO 	GPIOD
#define REL_R4_PIN  	GPIO_Pin_8

#define REL_R5_GPIO 	GPIOB
#define REL_R5_PIN  	GPIO_Pin_15

#define REL_R6_GPIO 	GPIOB
#define REL_R6_PIN  	GPIO_Pin_14

#define REL_R7_GPIO 	GPIOE
#define REL_R7_PIN  	GPIO_Pin_15

#define REL_R8_GPIO 	GPIOE
#define REL_R8_PIN  	GPIO_Pin_14

#define REL_R9_GPIO 	GPIOE
#define REL_R9_PIN  	GPIO_Pin_13

#define REL_R10_GPIO 	GPIOE
#define REL_R10_PIN  	GPIO_Pin_12

#define REL_R11_GPIO 	GPIOE
#define REL_R11_PIN  	GPIO_Pin_11

#define REL_R12_GPIO 	GPIOE
#define REL_R12_PIN  	GPIO_Pin_10


#define RELAY1_STATE(x) (!x)?GPIO_SetBits(RELAY1_GPIO,RELAY1_PIN):GPIO_ResetBits(RELAY1_GPIO,RELAY1_PIN)
#define RELAY2_STATE(x) (!x)?GPIO_SetBits(RELAY2_GPIO,RELAY2_PIN):GPIO_ResetBits(RELAY2_GPIO,RELAY2_PIN)
#define RELAY3_STATE(x) (!x)?GPIO_SetBits(RELAY3_GPIO,RELAY3_PIN):GPIO_ResetBits(RELAY3_GPIO,RELAY3_PIN)
#define RELAY4_STATE(x) (!x)?GPIO_SetBits(RELAY4_GPIO,RELAY4_PIN):GPIO_ResetBits(RELAY4_GPIO,RELAY4_PIN)
#define RELAY5_STATE(x) (!x)?GPIO_SetBits(RELAY5_GPIO,RELAY5_PIN):GPIO_ResetBits(RELAY5_GPIO,RELAY5_PIN)
#define RELAY6_STATE(x) (!x)?GPIO_SetBits(RELAY6_GPIO,RELAY6_PIN):GPIO_ResetBits(RELAY6_GPIO,RELAY6_PIN)
#define RELAY7_STATE(x) (!x)?GPIO_SetBits(RELAY7_GPIO,RELAY7_PIN):GPIO_ResetBits(RELAY7_GPIO,RELAY7_PIN)
#define RELAY8_STATE(x) (x)?GPIO_SetBits(RELAY8_GPIO,RELAY8_PIN):GPIO_ResetBits(RELAY8_GPIO,RELAY8_PIN)
#define RELAY9_STATE(x) (!x)?GPIO_SetBits(RELAY9_GPIO,RELAY9_PIN):GPIO_ResetBits(RELAY9_GPIO,RELAY9_PIN)
#define RELAY10_STATE(x) (!x)?GPIO_SetBits(RELAY10_GPIO,RELAY10_PIN):GPIO_ResetBits(RELAY10_GPIO,RELAY10_PIN)
#define RELAY11_STATE(x) (!x)?GPIO_SetBits(RELAY11_GPIO,RELAY11_PIN):GPIO_ResetBits(RELAY11_GPIO,RELAY11_PIN)

//---------------------------------------------------------
//气垫阀门
#define REL_1_STATE(x) (!x)?GPIO_SetBits(REL_1_GPIO,REL_1_PIN):GPIO_ResetBits(REL_1_GPIO,REL_1_PIN)
#define REL_2_STATE(x) (!x)?GPIO_SetBits(REL_2_GPIO,REL_2_PIN):GPIO_ResetBits(REL_2_GPIO,REL_2_PIN)
//头气
#define REL_TOP_a_STATE(x) (!x)?GPIO_SetBits(REL_3_GPIO,REL_3_PIN):GPIO_ResetBits(REL_3_GPIO,REL_3_PIN)
#define REL_TOP_b_STATE(x) (!x)?GPIO_SetBits(REL_4_GPIO,REL_4_PIN):GPIO_ResetBits(REL_4_GPIO,REL_4_PIN)
//
#define REL_L1_a_STATE(x) (!x)?GPIO_SetBits(REL_L1_GPIO,REL_L1_PIN):GPIO_ResetBits(REL_L1_GPIO,REL_L1_PIN) 
#define REL_L1_b_STATE(x) (!x)?GPIO_SetBits(REL_L2_GPIO,REL_L2_PIN):GPIO_ResetBits(REL_L2_GPIO,REL_L2_PIN)
#define REL_L2_a_STATE(x) (!x)?GPIO_SetBits(REL_L3_GPIO,REL_L3_PIN):GPIO_ResetBits(REL_L3_GPIO,REL_L3_PIN)
#define REL_L2_b_STATE(x) (!x)?GPIO_SetBits(REL_L4_GPIO,REL_L4_PIN):GPIO_ResetBits(REL_L4_GPIO,REL_L4_PIN)
#define REL_L3_a_STATE(x) (!x)?GPIO_SetBits(REL_L5_GPIO,REL_L5_PIN):GPIO_ResetBits(REL_L5_GPIO,REL_L5_PIN)
#define REL_L3_b_STATE(x) (!x)?GPIO_SetBits(REL_L6_GPIO,REL_L6_PIN):GPIO_ResetBits(REL_L6_GPIO,REL_L6_PIN)
#define REL_L4_a_STATE(x) (!x)?GPIO_SetBits(REL_L7_GPIO,REL_L7_PIN):GPIO_ResetBits(REL_L7_GPIO,REL_L7_PIN)
#define REL_L4_b_STATE(x) (!x)?GPIO_SetBits(REL_L8_GPIO,REL_L8_PIN):GPIO_ResetBits(REL_L8_GPIO,REL_L8_PIN)
#define REL_L5_a_STATE(x) (!x)?GPIO_SetBits(REL_L9_GPIO,REL_L9_PIN):GPIO_ResetBits(REL_L9_GPIO,REL_L9_PIN)
#define REL_L5_b_STATE(x) (!x)?GPIO_SetBits(REL_L10_GPIO,REL_L10_PIN):GPIO_ResetBits(REL_L10_GPIO,REL_L10_PIN)
#define REL_L6_a_STATE(x) (!x)?GPIO_SetBits(REL_L11_GPIO,REL_L11_PIN):GPIO_ResetBits(REL_L11_GPIO,REL_L11_PIN)
#define REL_L6_b_STATE(x) (!x)?GPIO_SetBits(REL_L12_GPIO,REL_L12_PIN):GPIO_ResetBits(REL_L12_GPIO,REL_L12_PIN)

#define REL_R1_a_STATE(x) (!x)?GPIO_SetBits(REL_R1_GPIO,REL_R1_PIN):GPIO_ResetBits(REL_R1_GPIO,REL_R1_PIN)
#define REL_R1_b_STATE(x) (!x)?GPIO_SetBits(REL_R2_GPIO,REL_R2_PIN):GPIO_ResetBits(REL_R2_GPIO,REL_R2_PIN)
#define REL_R2_a_STATE(x) (!x)?GPIO_SetBits(REL_R3_GPIO,REL_R3_PIN):GPIO_ResetBits(REL_R3_GPIO,REL_R3_PIN)
#define REL_R2_b_STATE(x) (!x)?GPIO_SetBits(REL_R4_GPIO,REL_R4_PIN):GPIO_ResetBits(REL_R4_GPIO,REL_R4_PIN)
#define REL_R3_a_STATE(x) (!x)?GPIO_SetBits(REL_R5_GPIO,REL_R5_PIN):GPIO_ResetBits(REL_R5_GPIO,REL_R5_PIN)
#define REL_R3_b_STATE(x) (!x)?GPIO_SetBits(REL_R6_GPIO,REL_R6_PIN):GPIO_ResetBits(REL_R6_GPIO,REL_R6_PIN)
#define REL_R4_a_STATE(x) (!x)?GPIO_SetBits(REL_R7_GPIO,REL_R7_PIN):GPIO_ResetBits(REL_R7_GPIO,REL_R7_PIN)
#define REL_R4_b_STATE(x) (!x)?GPIO_SetBits(REL_R8_GPIO,REL_R8_PIN):GPIO_ResetBits(REL_R8_GPIO,REL_R8_PIN)
#define REL_R5_a_STATE(x) (!x)?GPIO_SetBits(REL_R9_GPIO,REL_R9_PIN):GPIO_ResetBits(REL_R9_GPIO,REL_R9_PIN)
#define REL_R5_b_STATE(x) (!x)?GPIO_SetBits(REL_R10_GPIO,REL_R10_PIN):GPIO_ResetBits(REL_R10_GPIO,REL_R10_PIN)
#define REL_R6_a_STATE(x) (!x)?GPIO_SetBits(REL_R11_GPIO,REL_R11_PIN):GPIO_ResetBits(REL_R11_GPIO,REL_R11_PIN)
#define REL_R6_b_STATE(x) (!x)?GPIO_SetBits(REL_R12_GPIO,REL_R12_PIN):GPIO_ResetBits(REL_R12_GPIO,REL_R12_PIN)

//初始化
void OutputDriveInit(void);
	
#endif
