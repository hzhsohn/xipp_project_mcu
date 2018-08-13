#ifndef __RELAY_DIVER_H_
#define __RELAY_DIVER_H_
#include "system_init.h"
#define HIGH 	1
#define LOW 	0
/*¹Ü½Å¶¨Ò

#define _unit1(x) 							RELAY1_STATE(!x)		//Ð¡±ã×ª»»
#define _unit2(x) 							RELAY2_STATE(!x)		//´ó±ã×ª»»
#define _unit3(x) 							RELAY3_STATE(!x)		//´²Æø×ª»»
#define _unit4(x) 		 					RELAY4_STATE(!x)		//¿ã×ÓÆø×ª»ú
#define _unit5(x) 							RELAY5_STATE(!x)		//¼ÓÈÈÆø×ª»»
#define _unit6(x) 							RELAY6_STATE(!x)		//Æø¼ÓÈÈ
#define _unit7(x) 							RELAY7_STATE(!x)		//³éÎü»ú
#define _unit8(x) 				 			RELAY8_STATE(!x) 		//³éË®»ú
#define _unit9(x) 							RELAY9_STATE(!x)		//É±¾ú·¢ÉúÆ÷
#define _unit10(x) 				 			RELAY10_STATE(!x)		//´µÆø
#define _unit11(x)							RELAY11_STATE(!x) 	//Ë®¼ÓÈÈ
#define _unit12(x) 	 						RELAY12_STATE(!x)		//¾»»¯»ú
#define _unit13(x) 							RELAY13_STATE(!x)		//É±¾úÆø×ª»»
å*/
#define RELAY1_GPIO 	GPIOD
#define RELAY1_PIN  	GPIO_Pin_13

#define RELAY2_GPIO 	GPIOD
#define RELAY2_PIN  	GPIO_Pin_11

#define RELAY3_GPIO 	GPIOB
#define RELAY3_PIN  	GPIO_Pin_13

#define RELAY4_GPIO 	GPIOB
#define RELAY4_PIN  	GPIO_Pin_12

#define RELAY5_GPIO 	GPIOC
#define RELAY5_PIN  	GPIO_Pin_7
                                                                            
#define RELAY6_GPIO 	GPIOD
#define RELAY6_PIN  	GPIO_Pin_12

#define RELAY7_GPIO 	GPIOC
#define RELAY7_PIN  	GPIO_Pin_9

#define RELAY8_GPIO 	GPIOC
#define RELAY8_PIN  	GPIO_Pin_8

#define RELAY9_GPIO 	GPIOD
#define RELAY9_PIN  	GPIO_Pin_14

#define RELAY10_GPIO 	GPIOD
#define RELAY10_PIN  	GPIO_Pin_10

#define RELAY11_GPIO 	GPIOA
#define RELAY11_PIN  	GPIO_Pin_8

#define RELAY12_GPIO 	GPIOB
#define RELAY12_PIN  	GPIO_Pin_15

#define RELAY13_GPIO 	GPIOB
#define RELAY13_PIN  	GPIO_Pin_14


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


//--------------------------------------------------------------------------------------------
#define LED1_OFF 		GPIO_ResetBits(GPIOE , GPIO_Pin_13)
#define LED1_ON 		GPIO_SetBits(GPIOE , GPIO_Pin_13)
#define LED1_RE 		GPIO_WriteBit(GPIOE , GPIO_Pin_13,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_13)));

#define LED2_OFF 		GPIO_ResetBits(GPIOE , GPIO_Pin_14)
#define LED2_ON 		GPIO_SetBits(GPIOE , GPIO_Pin_14)
#define LED2_RE 		GPIO_WriteBit(GPIOE , GPIO_Pin_14,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_14)));

#define LED3_OFF 		GPIO_ResetBits(GPIOE , GPIO_Pin_15)
#define LED3_ON 		GPIO_SetBits(GPIOE , GPIO_Pin_15)
#define LED3_RE 		GPIO_WriteBit(GPIOE , GPIO_Pin_15,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_15)));

//
void POWER_Configuration(void);
void VOLUME_Configuration(void);
void LED_Configuration(void);
void Relay_Init(void);

//¼ÌµçÆ÷Êä³ö²âÊÔ
void RelayTest(void);//
	
#endif
