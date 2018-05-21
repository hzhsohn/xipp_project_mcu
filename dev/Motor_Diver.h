#ifndef __MOTOR_DIVER_H_
#define __MOTOR_DIVER_H_
#include "system_init.h"
#define MOTORTIME 100
#define HIGH 	1
#define LOW 	0
/*¹Ü½Å¶¨Òå*/
#define MOTOR1_A_GPIO 	GPIOB
#define MOTOR1_A_PIN  	GPIO_Pin_1
#define MOTOR1_B_GPIO 	GPIOC
#define MOTOR1_B_PIN  	GPIO_Pin_2

#define MOTOR2_A_GPIO 	GPIOB
#define MOTOR2_A_PIN  	GPIO_Pin_12
#define MOTOR2_B_GPIO 	GPIOC
#define MOTOR2_B_PIN  	GPIO_Pin_6


#define MOTOR1_A_STATE(x) (x)>0?GPIO_SetBits(MOTOR1_A_GPIO,MOTOR1_A_PIN):GPIO_ResetBits(MOTOR1_A_GPIO,MOTOR1_A_PIN)
#define MOTOR1_B_STATE(x) (x)>0?GPIO_SetBits(MOTOR1_B_GPIO,MOTOR1_B_PIN):GPIO_ResetBits(MOTOR1_B_GPIO,MOTOR1_B_PIN)

#define MOTOR2_A_STATE(x) (x)>0?GPIO_SetBits(MOTOR2_A_GPIO,MOTOR1_A_PIN):GPIO_ResetBits(MOTOR2_A_GPIO,MOTOR1_A_PIN)
#define MOTOR2_B_STATE(x) (x)>0?GPIO_SetBits(MOTOR2_B_GPIO,MOTOR1_B_PIN):GPIO_ResetBits(MOTOR2_B_GPIO,MOTOR1_B_PIN)

void Motor_Init(void);
void Motor_State(void);
void MOTOR_TIMER_ISR(void);
#endif
