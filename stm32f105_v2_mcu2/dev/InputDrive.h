#ifndef __Sensor_H_
#define __Sensor_H_

#include "system_init.h"

//污水桶满
#define SENSOR1_GPIO 	                	GPIOE
#define SENSOR1_PIN  			      	    	GPIO_Pin_5
//清水低
#define SENSOR2_GPIO 	                	GPIOA
#define SENSOR2_PIN  			      	    	GPIO_Pin_4
//污水桶到位
#define SENSOR3_GPIO 	                	GPIOD
#define SENSOR3_PIN  			      	    	GPIO_Pin_6
//大便
#define SENSOR4_GPIO 	                	GPIOE
#define SENSOR4_PIN  			      	    	GPIO_Pin_4
//小便
#define SENSOR5_GPIO 	                	GPIOE
#define SENSOR5_PIN  			      	    	GPIO_Pin_6


#define SENSOR1_STATE() 								GPIO_ReadInputDataBit(SENSOR1_GPIO,SENSOR1_PIN)
#define SENSOR2_STATE() 								GPIO_ReadInputDataBit(SENSOR2_GPIO,SENSOR2_PIN)
#define SENSOR3_STATE() 								GPIO_ReadInputDataBit(SENSOR3_GPIO,SENSOR3_PIN)
#define SENSOR4_STATE() 								GPIO_ReadInputDataBit(SENSOR4_GPIO,SENSOR4_PIN)
#define SENSOR5_STATE() 								GPIO_ReadInputDataBit(SENSOR5_GPIO,SENSOR5_PIN)

void InputDriveInit(void);

#endif
