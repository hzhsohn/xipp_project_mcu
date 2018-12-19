#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"

typedef struct _TagUpData485{
	unsigned char water_full;			//污水是否满
	unsigned char qiya1_percent; 	//气压1	
	unsigned char qiya2_percent; 	//气压2
}TagUpData485;

typedef struct _TagTimeRun{
	int juint1Time;
	int juint2Time;
	int juint3Time;
	int juint4Time;
	int juint5Time;
	int juint6Time;
}TagTimeRun;

#define _unit1(x) 							RELAY1_STATE(x)			//桶盖上下-
#define _unit2(x) 							RELAY2_STATE(x)			//桶盖上下+
#define _unit3(x) 							RELAY3_STATE(x)			//桶进出-
#define _unit4(x) 		 					RELAY4_STATE(x)			//桶进出+

#define _junit1(x) 							RELAY5_STATE(x)			//真空泵
#define _junit2(x) 							RELAY6_STATE(x)			//抽外桶负压阀
#define _junit3(x) 							RELAY7_STATE(x)			//抽内桶负压阀
#define _junit4(x) 				 			RELAY8_STATE(x) 		//气囊放气阀
#define _junit5(x) 							RELAY9_STATE(x)			//进气阀
#define _junit6(x) 				 			RELAY10_STATE(x)		//净化放气

#define _unit11(x)							RELAY11_STATE(x) 		//
#define _unit12(x) 	 						RELAY12_STATE(x)		//
#define _unit13(x) 							RELAY13_STATE(x)		//
#define _unit14(x) 	 						RELAY14_STATE(x)		//
#define _unit15(x) 							RELAY15_STATE(x)		//



#endif
