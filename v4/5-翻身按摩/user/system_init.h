#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"

typedef struct _TagUpData485{
	unsigned char shi;				//是否拉屎
	unsigned char niao;				//是否拉尿
	unsigned char PiGuWenDu;  //屁股的温度
	unsigned char miaibo;			//脉博
}TagUpData485;

typedef struct _TagTimeRun{
	int JiaReTime1;//加热
	int JiaReWenDu1;//加热
	int curJiaReWenDu;//当前发热垫温度
	
	int AnmoTime;//按摩时间
	
	int guan_qiya_percent;//充气
	
	int piai_wu_kai;//排污开
	int piai_wu_guan;//排污开
	
	int xiaobian_famen;//小便阀门
}TagTimeRun;

#define _unit1(x) 											RELAY1_STATE(x)			//
#define _unit2(x) 											RELAY2_STATE(x)			//
#define _unit3(x) 											RELAY3_STATE(x)			//
#define _unit4(x) 						 					RELAY4_STATE(x)			//
#define _unit5(x) 											RELAY5_STATE(x)			//
#define _unit6(x) 											RELAY6_STATE(x)			//
#define _unit7(x) 											RELAY7_STATE(x)			//
#define _unit8(x) 				 							RELAY8_STATE(x) 		//
#define _unit9(x) 											RELAY9_STATE(x)			//
#define _unit10(x) 				 							RELAY10_STATE(x)		//
#define _unit11(x)											RELAY11_STATE(x) 		//
#define _unit12(x) 	 										RELAY12_STATE(x)		//
#define _unit13(x) 											RELAY13_STATE(x)		//
#define _unit14(x) 	 										RELAY14_STATE(x)		//
#define _unit15(x) 											RELAY15_STATE(x)		//

#endif
