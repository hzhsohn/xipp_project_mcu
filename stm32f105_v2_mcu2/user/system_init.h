#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"


typedef struct _TagTimeingSetting{
		unsigned char a;
		unsigned char b;
}TagTimeingSetting;

#define _unit16(x) 							RELAY1_STATE(x)			//按摩保暖电源
#define _unit17(x) 							RELAY2_STATE(x)			//左充气  常闭阀门
#define _unit18(x) 							RELAY3_STATE(x)			//左放气  常闭阀门
#define _unit19(x) 		 					RELAY4_STATE(x)			//右充气  常闭阀门
#define _unit20(x) 							RELAY5_STATE(x)			//右放气  常闭阀门
#define _unit21(x) 							RELAY6_STATE(x)			//背囊充  常闭阀门
#define _unit22(x) 							RELAY7_STATE(x)			//背囊放  常闭阀门
#define _unit23(x) 				 			RELAY8_STATE(x) 		//床垫充气  常闭阀门
#define _unit24(x) 							RELAY9_STATE(x)			//放气  常闭阀门
#define _unit25(x) 				 			RELAY10_STATE(x)		//充气关  球形阀门
#define _unit26(x)							RELAY11_STATE(x) 		//充气开  球形阀门
#define _unit27(x) 	 						RELAY12_STATE(x)		//预留
#define _unit10(x) 	 						RELAY13_STATE(x)		//充气

#endif
