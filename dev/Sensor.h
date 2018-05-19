#ifndef __Sensor_H_
#define __Sensor_H_

#include "system_init.h"

#define SENSOR1_GPIO 	                	GPIOC
#define SENSOR1_PIN  			      	    	GPIO_Pin_12
#define SENSOR2_GPIO 	                	GPIOA
#define SENSOR2_PIN  			      	    	GPIO_Pin_4
#define SENSOR3_GPIO 	                	GPIOB
#define SENSOR3_PIN  			      	    	GPIO_Pin_8
#define SENSOR4_GPIO 	                	GPIOC
#define SENSOR4_PIN  			      	    	GPIO_Pin_0
#define SENSOR5_GPIO 	                	GPIOC
#define SENSOR5_PIN  			      	    	GPIO_Pin_1
#define SENSOR6_GPIO 	                	GPIOC
#define SENSOR6_PIN  			      	    	GPIO_Pin_2
#define SENSOR1_STATE() 								GPIO_ReadInputDataBit(SENSOR1_GPIO,SENSOR1_PIN)
#define SENSOR2_STATE() 								GPIO_ReadInputDataBit(SENSOR2_GPIO,SENSOR2_PIN)
#define SENSOR3_STATE() 								GPIO_ReadInputDataBit(SENSOR3_GPIO,SENSOR3_PIN)
#define SENSOR4_STATE() 								GPIO_ReadInputDataBit(SENSOR4_GPIO,SENSOR4_PIN)
#define SENSOR5_STATE() 								GPIO_ReadInputDataBit(SENSOR5_GPIO,SENSOR5_PIN)
#define SENSOR6_STATE() 								GPIO_ReadInputDataBit(SENSOR6_GPIO,SENSOR6_PIN)

void Sensor_Init(void);

#endif
