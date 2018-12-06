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
//提交的数据
static TagUpData485 ud485={0};

typedef struct _TagTimeRun{
	int jiaoPanTime;
	int JiaReTime1;
	int JiaReWenDu1;
	int JiaReTime2;
	int JiaReWenDu2;
	int curJiaReWenDu;
}TagTimeRun;
static TagTimeRun g_run={0};

#define _unit1(x) 											RELAY1_STATE(x)			//搅拌
#define _unit2(x) 											RELAY2_STATE(x)			//风机1
#define _unit3(x) 											RELAY3_STATE(x)			//风机2
#define _unit4(x) 						 					RELAY4_STATE(x)			//加热1
#define _unit5(x) 											RELAY5_STATE(x)			//加热2
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
