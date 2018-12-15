#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"


typedef struct _TagUpData485{
	unsigned char key;
	unsigned char shuiWen;
	unsigned char shuiGuoDi; //1水位低,2水位高
}TagUpData485;

typedef struct _TagTimeRun{
	int juint1Time;
	int juint2Time;
	int juint3Time;
	int juint4Time;
	int juint5Time;
}TagTimeRun;

#define _junit1(x) 							RELAY1_STATE(x)			//抽水机
#define _junit2(x) 							RELAY2_STATE(x)			//水加热
#define _junit3(x) 							RELAY3_STATE(x)			//大便斗冲水阀
#define _junit4(x) 		 					RELAY4_STATE(x)			//清洁冲水阀关
#define _junit5(x) 							RELAY5_STATE(x)			//小便斗冲水阀

#define _unit6(x) 							RELAY6_STATE(x)		
#define _unit7(x) 							RELAY7_STATE(x)	
#define _unit8(x) 				 			RELAY8_STATE(x) 	
#define _unit9(x) 							RELAY9_STATE(x)		
#define _unit10(x) 				 			RELAY10_STATE(x)	
#define _unit11(x)							RELAY11_STATE(x) 		
#define _unit12(x) 	 						RELAY12_STATE(x)	
#define _unit13(x) 							RELAY13_STATE(x)	
#define _unit14(x) 	 						RELAY14_STATE(x)	
#define _unit15(x) 							RELAY15_STATE(x)	

#endif
