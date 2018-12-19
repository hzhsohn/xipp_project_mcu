#ifndef __Sensor_H_
#define __Sensor_H_

#include "system_init.h"

//污水满
#define SENSOR1_GPIO 	                	GPIOE
#define SENSOR1_PIN  			      	    	GPIO_Pin_5

//限位
#define SENSOR4_GPIO 	                	GPIOE         //污水桶盖开限位A
#define SENSOR4_PIN  			      	    	GPIO_Pin_3

#define SENSOR5_GPIO 	                	GPIOE         //污水桶盖开限位B
#define SENSOR5_PIN  			      	    	GPIO_Pin_4

//#define SENSOR6_GPIO 	                	GPIOA         //污水桶盖关限位C
//#define SENSOR6_PIN  			      	    	GPIO_Pin_15

#define SENSOR7_GPIO 	                	GPIOD         //污水桶进限位D
#define SENSOR7_PIN  			      	    	GPIO_Pin_6

#define SENSOR8_GPIO 	                	GPIOA         //污水桶出限位E
#define SENSOR8_PIN  			      	    	GPIO_Pin_4


#define SENSOR1_STATE() 								GPIO_ReadInputDataBit(SENSOR1_GPIO,SENSOR1_PIN)

#define SENSOR4_STATE() 								!GPIO_ReadInputDataBit(SENSOR4_GPIO,SENSOR4_PIN)
#define SENSOR5_STATE() 								!GPIO_ReadInputDataBit(SENSOR5_GPIO,SENSOR5_PIN)
//#define SENSOR6_STATE() 								!GPIO_ReadInputDataBit(SENSOR6_GPIO,SENSOR6_PIN)
#define SENSOR7_STATE() 								!GPIO_ReadInputDataBit(SENSOR7_GPIO,SENSOR7_PIN)
#define SENSOR8_STATE() 								!GPIO_ReadInputDataBit(SENSOR8_GPIO,SENSOR8_PIN)

void InputDriveInit(void);

#endif
