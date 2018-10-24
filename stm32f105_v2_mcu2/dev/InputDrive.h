#ifndef __Sensor_H_
#define __Sensor_H_

#include "system_init.h"

//¾»»¯ÒºµÍ¼ì²â
#define SENSOR1_GPIO 	                	GPIOE
#define SENSOR1_PIN  			      	    	GPIO_Pin_5


#define SENSOR1_STATE() 								GPIO_ReadInputDataBit(SENSOR1_GPIO,SENSOR1_PIN)

void InputDriveInit(void);

#endif
