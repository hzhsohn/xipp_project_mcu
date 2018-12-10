#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"

//S2
typedef struct _TagUpData485_S2{
	unsigned char shi;				//是否拉屎
	unsigned char niao;				//是否拉尿
	unsigned char PiGuWenDu;  //屁股的温度
	unsigned char miaibo;			//脉博
}TagUpData485_S2;

//S3
typedef struct _TagUpData485_S3{
	unsigned char water_full;			//污水是否满
	unsigned char qiya1_percent; 	//气压1	
	unsigned char qiya2_percent; 	//气压2
}TagUpData485_S3;

//S4
typedef struct _TagUpData485_S4{
	unsigned char key;
	unsigned char shuiWen;
	unsigned char shuiGuoDi; //1水位低,2水位高
}TagUpData485_S4;

//S5
typedef struct _TagUpData485_S5{
	unsigned char qiwen; //气温多少度
}TagUpData485_S5;


typedef struct _TagTimeingSetting{
		unsigned char pooDelay;				//拉屎后多少秒启动 ,单位分钟
		unsigned char xuxuDelay;			//拉屎后多少秒启动 ,单位秒
		unsigned char pooFlush;				//屎屎冲洗  ,单位秒
		unsigned char xuxuFlush;			//尿尿冲洗  单位 秒
		unsigned char pooDry;      		//屎屎烘干时间 单位 分钟
		unsigned char xuxuDry;				//尿尿烘干时间 单位 分钟
		unsigned char pooSterilize;		//屎屎消毒时间 单位 秒
		unsigned char xuxuSterilize;	//尿尿消毒时间 单位 秒
	  unsigned char crotchPressure;	//裤档气压 单位 100电压变数
		unsigned char bedPressure;   	//床垫的气压  单位 100电压变数
		unsigned char waterTemperature;//最低水温   单位摄氏度
		unsigned char airTemperature;  //最低烘干温度   单位摄氏度
		unsigned char mpuLeft; 				//左角
		unsigned char mpuRight;  			//右角
}TagTimeingSetting;


#endif
