#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"

#define _unit1(x) 							RELAY1_STATE(x)			//
#define _unit2(x) 							RELAY2_STATE(x)			//
#define _unit3(x) 							RELAY3_STATE(x)			//
#define _unit4(x) 		 					RELAY4_STATE(x)			//

#define _junit1(x) 							RELAY5_STATE(x)			//
#define _junit2(x) 							RELAY6_STATE(x)			//
#define _junit3(x) 							RELAY7_STATE(x)			//
#define _junit4(x) 				 			RELAY8_STATE(x) 		//
#define _junit5(x) 							RELAY9_STATE(x)			//
#define _junit6(x) 				 			RELAY10_STATE(x)		//

#define _unit11(x)							RELAY11_STATE(x) 		//
#define _unit12(x) 	 						RELAY12_STATE(x)		//
#define _unit13(x) 							RELAY13_STATE(x)		//
#define _unit14(x) 	 						RELAY14_STATE(x)		//
#define _unit15(x) 							RELAY15_STATE(x)		//



#endif
