#ifndef __AUTO_SenceAct_H_
#define __AUTO_SenceAct_H_
#include "system_init.h"
#include "mini-data.h"

//工作时间设置
typedef struct _TagTimeingSetting{
		uchar pooDelay;				//拉屎后多少秒启动 ,单位分钟
		uchar xuxuDelay;			//拉屎后多少秒启动 ,单位秒
		uchar pooFlush;				//屎屎冲洗  ,单位秒
		uchar xuxuFlush;			//尿尿冲洗  单位 秒
		uchar pooDry;      		//屎屎烘干时间 单位 分钟
		uchar xuxuDry;				//尿尿烘干时间 单位 分钟
		uchar pooSterilize;		//屎屎消毒时间 单位 秒
		uchar xuxuSterilize;	//尿尿消毒时间 单位 秒
	  uchar crotchPressure;	//裤档气压 单位 100电压变数
		uchar bedPressure;   	//床垫的气压  单位 100电压变数
		uchar waterTemperature;//最低水温   单位摄氏度
		uchar airTemperature;  //最低烘干温度   单位摄氏度
		uchar mpuLeft; 				//左角
		uchar mpuRight;  			//右角
}TagTimeingSetting;

#endif
