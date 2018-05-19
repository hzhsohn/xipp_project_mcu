#ifndef __BEESPEAKER_DIVER_H_
#define __BEESPEAKER_DIVER_H_
#include "system_init.h"
#define HIGH 	1
#define LOW 	0
#define BEESPECKER_GPIO 	GPIOC
#define BEESPECKER_PIN  	GPIO_Pin_13
#define BEESPECKER_STATE(x) (x)>0?GPIO_SetBits(BEESPECKER_GPIO,BEESPECKER_PIN):GPIO_ResetBits(BEESPECKER_GPIO,BEESPECKER_PIN)
void BeeSpeak_Init(void);

void BEE_TIMER_ISR(void);
#endif
