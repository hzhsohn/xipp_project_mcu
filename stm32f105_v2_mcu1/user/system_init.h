#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"


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
