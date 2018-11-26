#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"


#define _unit1(x) 							RELAY1_STATE(x)			//吹气阀关  球形阀门
#define _unit2(x) 							RELAY2_STATE(x)			//吹气阀开  球形阀门
#define _unit3(x) 							RELAY3_STATE(x)			//排泄阀关  球形阀门
#define _unit4(x) 		 					RELAY4_STATE(x)			//排泄阀开  球形阀门
#define _unit5(x) 							RELAY5_STATE(x)			//冲水阀1  常闭阀门尿
#define _unit6(x) 							RELAY6_STATE(x)			//冲水阀2  常闭阀门冲斗
#define _unit7(x) 							RELAY7_STATE(x)			//冲水阀3  常闭阀门冲PP
#define _unit8(x) 				 			RELAY8_STATE(x) 		//杀菌器
#define _unit9(x) 							RELAY9_STATE(x)			//净化抽水
#define _unit10(x) 				 			RELAY10_STATE(x)		//吹气泵
#define _unit11(x)							RELAY11_STATE(x) 		//主抽水机
#define _unit12(x) 	 						RELAY12_STATE(x)		//气加热器
#define _unit13(x) 							RELAY13_STATE(x)		//水加热器  16A
#define _unit14(x) 	 						RELAY14_STATE(x)		//预留  220V
#define _unit15(x) 							RELAY15_STATE(x)		//抽吸机  220V



#endif
