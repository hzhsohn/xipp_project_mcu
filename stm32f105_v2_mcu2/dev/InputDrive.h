#ifndef __Sensor_H_
#define __Sensor_H_

#include "system_init.h"

//¾»»¯ÒºµÍ¼ì²â
#define SENSOR1_GPIO 	                	GPIOE
#define SENSOR1_PIN  			      	    	GPIO_Pin_5

//ÂíÍ°·­¸Ç
#define SENSOR2_GPIO 	                	GPIOE
#define SENSOR2_PIN  			      	    	GPIO_Pin_4
#define SENSOR3_GPIO 	                	GPIOA
#define SENSOR3_PIN  			      	    	GPIO_Pin_15

//ÂíÍ°ÍÆ³ö
#define SENSOR4_GPIO 	                	GPIOA
#define SENSOR4_PIN  			      	    	GPIO_Pin_4
#define SENSOR5_GPIO 	                	GPIOB
#define SENSOR5_PIN  			      	    	GPIO_Pin_6

#define SENSOR1_STATE() 								GPIO_ReadInputDataBit(SENSOR1_GPIO,SENSOR1_PIN)
#define SENSOR2_STATE() 								GPIO_ReadInputDataBit(SENSOR2_GPIO,SENSOR2_PIN)
#define SENSOR3_STATE() 								GPIO_ReadInputDataBit(SENSOR3_GPIO,SENSOR3_PIN)
#define SENSOR4_STATE() 								GPIO_ReadInputDataBit(SENSOR4_GPIO,SENSOR4_PIN)
#define SENSOR5_STATE() 								GPIO_ReadInputDataBit(SENSOR5_GPIO,SENSOR5_PIN)

void InputDriveInit(void);

#endif
