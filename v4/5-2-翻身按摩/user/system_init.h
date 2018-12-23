#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"
#include "OutputDrive.h"

typedef struct _TagTimeRun
{
	int is_run_fan_sheng;
	int guan_qiya_percent[14];//电压采样值
}TagTimeRun;

#endif
