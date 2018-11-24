#ifndef __MOTOR_DIVER_H_
#include "system_init.h"

void sceMotor1_do(void);
void sceMotor2_do(void);
void sceMotorDemo_do(void);



/*管脚定义*/
#define MOTOR1_A_GPIO 	GPIOB
#define MOTOR1_A_PIN  	GPIO_Pin_1
#define MOTOR1_B_GPIO 	GPIOB
#define MOTOR1_B_PIN  	GPIO_Pin_2
#define MOTOR1_C_GPIO 	GPIOE//GPIOE
#define MOTOR1_C_PIN  	GPIO_Pin_7//GPIO_Pin_7
//#define MOTOR1_D_GPIO 	GPIOE
//#define MOTOR1_D_PIN  	GPIO_Pin_8

#define MOTOR2_A_GPIO 	GPIOE
#define MOTOR2_A_PIN  	GPIO_Pin_9
#define MOTOR2_B_GPIO 	GPIOE
#define MOTOR2_B_PIN  	GPIO_Pin_10
#define MOTOR2_C_GPIO 	GPIOE
#define MOTOR2_C_PIN  	GPIO_Pin_11
#define MOTOR2_D_GPIO 	GPIOE
#define MOTOR2_D_PIN  	GPIO_Pin_12

#define MOTOR1_A_STATE(x) (x)?GPIO_SetBits(MOTOR1_A_GPIO,MOTOR1_A_PIN):GPIO_ResetBits(MOTOR1_A_GPIO,MOTOR1_A_PIN)
#define MOTOR1_B_STATE(x) (!x)?GPIO_SetBits(MOTOR1_B_GPIO,MOTOR1_B_PIN):GPIO_ResetBits(MOTOR1_B_GPIO,MOTOR1_B_PIN)
#define MOTOR1_C_STATE(x) (!x)?GPIO_SetBits(MOTOR1_C_GPIO,MOTOR1_C_PIN):GPIO_ResetBits(MOTOR1_C_GPIO,MOTOR1_C_PIN)
#define MOTOR1_D_STATE(x) //(x)?GPIO_SetBits(MOTOR1_D_GPIO,MOTOR1_D_PIN):GPIO_ResetBits(MOTOR1_D_GPIO,MOTOR1_D_PIN)

#define MOTOR2_A_STATE(x) (x)>0?GPIO_SetBits(MOTOR2_A_GPIO,MOTOR2_A_PIN):GPIO_ResetBits(MOTOR2_A_GPIO,MOTOR2_A_PIN)
#define MOTOR2_B_STATE(x) (x)>0?GPIO_SetBits(MOTOR2_B_GPIO,MOTOR2_B_PIN):GPIO_ResetBits(MOTOR2_B_GPIO,MOTOR2_B_PIN)
#define MOTOR2_C_STATE(x) (x)>0?GPIO_SetBits(MOTOR2_C_GPIO,MOTOR2_C_PIN):GPIO_ResetBits(MOTOR2_C_GPIO,MOTOR2_C_PIN)
#define MOTOR2_D_STATE(x) (x)>0?GPIO_SetBits(MOTOR2_D_GPIO,MOTOR2_D_PIN):GPIO_ResetBits(MOTOR2_D_GPIO,MOTOR2_D_PIN)

//输入
#define MOTOR1_L_LIMIT_GPIO 	GPIOA
#define MOTOR1_L_LIMIT_PIN  	GPIO_Pin_1
#define MOTOR1_R_LIMIT_GPIO 	GPIOA
#define MOTOR1_R_LIMIT_PIN  	GPIO_Pin_0

#define MOTOR2_L_LIMIT_GPIO 	GPIOD
#define MOTOR2_L_LIMIT_PIN  	GPIO_Pin_8
#define MOTOR2_R_LIMIT_GPIO 	GPIOD
#define MOTOR2_R_LIMIT_PIN  	GPIO_Pin_9

#define MOTOR1_L_LIMIT_STATE() 							GPIO_ReadInputDataBit(MOTOR1_L_LIMIT_GPIO,MOTOR1_L_LIMIT_PIN)
#define MOTOR1_R_LIMIT_STATE() 							GPIO_ReadInputDataBit(MOTOR1_R_LIMIT_GPIO,MOTOR1_R_LIMIT_PIN)
#define MOTOR2_L_LIMIT_STATE() 							GPIO_ReadInputDataBit(MOTOR2_L_LIMIT_GPIO,MOTOR2_L_LIMIT_PIN)
#define MOTOR2_R_LIMIT_STATE() 							GPIO_ReadInputDataBit(MOTOR2_R_LIMIT_GPIO,MOTOR2_R_LIMIT_PIN)

void Motor_Init(void);

void Motor1_do_intpr_cmd(int p_or_n);
void Motor2_do_intpr_cmd(int p_or_n);

void Motor1_do(int p_or_n);
void Motor2_do(int p_or_n);

void Motor_demo(void);
void Motor_demo_up(void);
void Motor_demo_down(void);

void Mon2blockTurnLeft(void);
void Mon2blockTurnRight(void);

#define __MOTOR_DIVER_H_
#endif

