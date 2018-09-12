#include "watchdog.h"
#include "Motor_Diver.h"
#include "STM32_Delay.h"

extern int xiiiLimit;
extern int xiii;
extern int xiii2;
extern int Motor1_do_step;
extern int Motor2_do_step;
extern int motor1_p_or_n;
extern int motor2_p_or_n;
extern int monLimitState1L;
extern int monLimitState1R;
extern int monLimitState2L;
extern int monLimitState2R;
//
int motor_demo_do=0;
int current_demo_step=0;

void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/* ±÷” πƒ‹*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	/*MOTOR1*/
	GPIO_MyStruct.GPIO_Pin = MOTOR1_A_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR1_A_GPIO, &GPIO_MyStruct);
	MOTOR1_A_STATE(0);
	GPIO_MyStruct.GPIO_Pin = MOTOR1_B_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR1_B_GPIO, &GPIO_MyStruct);
	MOTOR1_B_STATE(0);
	
		GPIO_MyStruct.GPIO_Pin = MOTOR1_C_PIN;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(MOTOR1_C_GPIO, &GPIO_MyStruct);
		MOTOR1_C_STATE(0);
	
	/*
		GPIO_MyStruct.GPIO_Pin = MOTOR1_D_PIN;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(MOTOR1_D_GPIO, &GPIO_MyStruct);
		MOTOR1_D_STATE(0);
		*/
	
	/*MOTOR2*/
	GPIO_MyStruct.GPIO_Pin = MOTOR2_A_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR2_A_GPIO, &GPIO_MyStruct);
	MOTOR2_A_STATE(0);
	GPIO_MyStruct.GPIO_Pin = MOTOR2_B_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR2_B_GPIO, &GPIO_MyStruct);
	MOTOR2_B_STATE(0);

		GPIO_MyStruct.GPIO_Pin = MOTOR2_C_PIN;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(MOTOR2_C_GPIO, &GPIO_MyStruct);
		MOTOR2_C_STATE(0);
		GPIO_MyStruct.GPIO_Pin = MOTOR2_D_PIN;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(MOTOR2_B_GPIO, &GPIO_MyStruct);
		MOTOR2_D_STATE(0);

	// ‰»Î
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_MyStruct.GPIO_Pin = MOTOR1_L_LIMIT_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(MOTOR1_L_LIMIT_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = MOTOR1_R_LIMIT_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(MOTOR1_R_LIMIT_GPIO, &GPIO_MyStruct);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_MyStruct.GPIO_Pin = MOTOR2_L_LIMIT_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(MOTOR2_L_LIMIT_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = MOTOR2_R_LIMIT_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(MOTOR2_R_LIMIT_GPIO, &GPIO_MyStruct);
}

void Mon2blockTurnLeft(void)
{
			int dododyesLeft=8000;
			int nCalca=0;
			int Motor2_block_step=1;
			for(Motor2_block_step=1;Motor2_block_step<=16;)
			{
					switch(Motor2_block_step)
					{
						case 1:
							nCalca=0;
							Motor2_block_step++;				
							MOTOR2_A_STATE(1);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(0);
							break;
						case 2:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_block_step++; }
							else
							{ nCalca++; }
							break;
						case 3:
							nCalca=0;
							Motor2_block_step++;						
							MOTOR2_A_STATE(1);
							MOTOR2_B_STATE(1);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(0);
							break;
						case 4:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_block_step++; }
							else
							{ nCalca++; }
							break;
						case 5:
							nCalca=0;
							Motor2_block_step++;	
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(1);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(0);						
							break;
						case 6:
							if(nCalca>1000)
							{ nCalca=0; Motor2_block_step++; }
							else
							{ nCalca++; }
							break;
						case 7:
							nCalca=0;
							Motor2_block_step++;
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(1);
							MOTOR2_C_STATE(1);
							MOTOR2_D_STATE(0);						
							break;
						case 8:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_block_step++; }
							else
							{ nCalca++; }
							break;
						case 9:
							nCalca=0;
							Motor2_block_step++;
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(1);
							MOTOR2_D_STATE(0);
							break;
						case 10:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_block_step++; }
							else
							{ nCalca++; }
							break;
						case 11:
							nCalca=0;
							Motor2_block_step++;
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(1);
							MOTOR2_D_STATE(1);
							break;
						case 12:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_block_step++; }
							else
							{ nCalca++; }
							break;
						case 13:
							nCalca=0;
							Motor2_block_step++;
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(1);
							break;
						case 14:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_block_step++; }
							else
							{ nCalca++; }
							break;
						case 15:
							nCalca=0;
							Motor2_block_step++;
							MOTOR2_A_STATE(1);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(1);
							break;
						case 16:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_block_step++; }
							else
							{ nCalca++; }
							break;
					}
		}
}
void Mon2blockTurnRight(void)
{	
			int dododyes=8000;
			int nCalca=0;
			int Motor2_block_step=1;

			for(Motor2_block_step=1;Motor2_block_step<=16;)
			{
						switch(Motor2_block_step)
						{
							case 1:
								nCalca=0;
								Motor2_block_step++;						
			MOTOR2_A_STATE(1);
			MOTOR2_B_STATE(0);
			MOTOR2_C_STATE(0);
			MOTOR2_D_STATE(1);
								break;
							case 2:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_block_step++; }
								else
								{ nCalca++; }
								break;
							case 3:
								nCalca=0;
								Motor2_block_step++;				
			MOTOR2_A_STATE(0);
			MOTOR2_B_STATE(0);
			MOTOR2_C_STATE(0);
			MOTOR2_D_STATE(1);
								break;
							case 4:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_block_step++; }
								else
								{ nCalca++; }
								break;
							case 5:
								nCalca=0;
								Motor2_block_step++;
			MOTOR2_A_STATE(0);
			MOTOR2_B_STATE(0);
			MOTOR2_C_STATE(1);
			MOTOR2_D_STATE(1);				
								break;
							case 6:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_block_step++; }
								else
								{ nCalca++; }
								break;
							case 7:
								nCalca=0;
								Motor2_block_step++;
			MOTOR2_A_STATE(0);
			MOTOR2_B_STATE(0);
			MOTOR2_C_STATE(1);
			MOTOR2_D_STATE(0);				
								break;
							case 8:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_block_step++; }
								else
								{ nCalca++; }
								break;
							case 9:
								nCalca=0;
								Motor2_block_step++;
			MOTOR2_A_STATE(0);
			MOTOR2_B_STATE(1);
			MOTOR2_C_STATE(1);
			MOTOR2_D_STATE(0);
								break;
							case 10:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_block_step++; }
								else
								{ nCalca++; }
								break;
							case 11:
								nCalca=0;
								Motor2_block_step++;
			MOTOR2_A_STATE(0);
			MOTOR2_B_STATE(1);
			MOTOR2_C_STATE(0);
			MOTOR2_D_STATE(0);
								break;
							case 12:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_block_step++; }
								else
								{ nCalca++; }
								break;
							case 13:
								nCalca=0;
								Motor2_block_step++;
			MOTOR2_A_STATE(1);
			MOTOR2_B_STATE(1);
			MOTOR2_C_STATE(0);
			MOTOR2_D_STATE(0);
								break;
							case 14:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_block_step++; }
								else
								{ nCalca++; }
								break;
							case 15:
								nCalca=0;
								Motor2_block_step++;
			MOTOR2_A_STATE(1);
			MOTOR2_B_STATE(0);
			MOTOR2_C_STATE(0);
			MOTOR2_D_STATE(0);
								break;
							case 16:
								if(nCalca>dododyes)
							{ nCalca=0; Motor2_block_step++; }
							else
							{ nCalca++; }
								break;
						}
		}
}

void sceMotor1_do(void)
{
		monLimitState1L=MOTOR1_L_LIMIT_STATE();
		monLimitState1R=MOTOR1_R_LIMIT_STATE();

		if(1==motor1_p_or_n && 1==monLimitState1L)
		{
				if(xiii<xiiiLimit)
				{
						xiii++;
						MOTOR1_B_STATE(1);
						MOTOR1_C_STATE(1);
				}
				else
				{
						MOTOR1_C_STATE(0);
						motor1_p_or_n=0;
				}
		}
		else if(2==motor1_p_or_n && 1==monLimitState1R)
		{
				if(xiii<xiiiLimit)
				{
						xiii++;
						MOTOR1_B_STATE(0);
						MOTOR1_C_STATE(1);
				}
				else
				{
						MOTOR1_C_STATE(0);
						motor1_p_or_n=0;
				}
		}
		else if(3==motor1_p_or_n && 1==monLimitState1L)
		{
						MOTOR1_B_STATE(1);
						MOTOR1_C_STATE(1);
		}
		else if(4==motor1_p_or_n && 1==monLimitState1R)
		{
						MOTOR1_B_STATE(0);
						MOTOR1_C_STATE(1);
		}
		else
		{
					//πÿµÙœﬂ»¶Ã◊µƒ»Œ∫ŒÕ®µÁ––Œ™
					MOTOR1_C_STATE(0);
					motor1_p_or_n=0;
		}
}

void sceMotor2_do(void)
{
		static int dododyesLeft=10;
		static int dododyes=10;
		static int nCalca=0;

		monLimitState2L=MOTOR2_L_LIMIT_STATE();
		monLimitState2R=MOTOR2_R_LIMIT_STATE();

		if(1==motor2_p_or_n && 1==monLimitState2L)
		{
				if(xiii2<xiiiLimit)
				{
					xiii2++;
					switch(Motor2_do_step)
					{
						case 1:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?							
							MOTOR2_A_STATE(1);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(0);
							break;
						case 2:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 3:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?							
							MOTOR2_A_STATE(1);
							MOTOR2_B_STATE(1);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(0);
							break;
						case 4:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 5:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(1);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(0);						
							break;
						case 6:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 7:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(1);
							MOTOR2_C_STATE(1);
							MOTOR2_D_STATE(0);						
							break;
						case 8:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 9:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(1);
							MOTOR2_D_STATE(0);
							break;
						case 10:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 11:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(1);
							MOTOR2_D_STATE(1);
							break;
						case 12:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 13:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(1);
							break;
						case 14:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 15:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
							MOTOR2_A_STATE(1);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(1);
							break;
						case 16:
							Motor2_do_step=1;
							break;
					}
				}
				else
				{motor2_p_or_n=0;}
		}
		else if(2==motor2_p_or_n && 1==monLimitState2R)
		{
				if(xiii2<xiiiLimit)
				{
						xiii2++;
					switch(Motor2_do_step)
					{
						case 1:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?							
MOTOR2_A_STATE(1);
MOTOR2_B_STATE(0);
MOTOR2_C_STATE(0);
MOTOR2_D_STATE(1);
							break;
						case 2:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 3:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?							
MOTOR2_A_STATE(0);
MOTOR2_B_STATE(0);
MOTOR2_C_STATE(0);
MOTOR2_D_STATE(1);
							break;
						case 4:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 5:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
MOTOR2_A_STATE(0);
MOTOR2_B_STATE(0);
MOTOR2_C_STATE(1);
MOTOR2_D_STATE(1);				
							break;
						case 6:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 7:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
MOTOR2_A_STATE(0);
MOTOR2_B_STATE(0);
MOTOR2_C_STATE(1);
MOTOR2_D_STATE(0);				
							break;
						case 8:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 9:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
MOTOR2_A_STATE(0);
MOTOR2_B_STATE(1);
MOTOR2_C_STATE(1);
MOTOR2_D_STATE(0);
							break;
						case 10:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 11:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
MOTOR2_A_STATE(0);
MOTOR2_B_STATE(1);
MOTOR2_C_STATE(0);
MOTOR2_D_STATE(0);
							break;
						case 12:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 13:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
MOTOR2_A_STATE(1);
MOTOR2_B_STATE(1);
MOTOR2_C_STATE(0);
MOTOR2_D_STATE(0);
							break;
						case 14:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 15:
							nCalca=0;
							Motor2_do_step++;	//??Ú?2?
MOTOR2_A_STATE(1);
MOTOR2_B_STATE(0);
MOTOR2_C_STATE(0);
MOTOR2_D_STATE(0);
							break;
						case 16:
							Motor2_do_step=1;
							break;
					}
				}
				else
				{motor2_p_or_n=0;}
		}
		else if(3==motor2_p_or_n && 1==monLimitState2L)
		{
					switch(Motor2_do_step)
					{
						case 1:
							nCalca=0;
							Motor2_do_step++;
							MOTOR2_A_STATE(1);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(0);
							break;
						case 2:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 3:
							nCalca=0;
							Motor2_do_step++;
							MOTOR2_A_STATE(1);
							MOTOR2_B_STATE(1);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(0);
							break;
						case 4:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 5:
							nCalca=0;
							Motor2_do_step++;
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(1);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(0);						
							break;
						case 6:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 7:
							nCalca=0;
							Motor2_do_step++;
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(1);
							MOTOR2_C_STATE(1);
							MOTOR2_D_STATE(0);						
							break;
						case 8:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 9:
							nCalca=0;
							Motor2_do_step++;
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(1);
							MOTOR2_D_STATE(0);
							break;
						case 10:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 11:
							nCalca=0;
							Motor2_do_step++;
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(1);
							MOTOR2_D_STATE(1);
							break;
						case 12:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 13:
							nCalca=0;
							Motor2_do_step++;
							MOTOR2_A_STATE(0);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(1);
							break;
						case 14:
							if(nCalca>dododyesLeft)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 15:
							nCalca=0;
							Motor2_do_step++;
							MOTOR2_A_STATE(1);
							MOTOR2_B_STATE(0);
							MOTOR2_C_STATE(0);
							MOTOR2_D_STATE(1);
							break;
						case 16:
							Motor2_do_step=1;
							break;
					}
		}
		else if(4==motor2_p_or_n && 1==monLimitState2R)
		{
					switch(Motor2_do_step)
					{
						case 1:
							nCalca=0;
							Motor2_do_step++;						
MOTOR2_A_STATE(1);
MOTOR2_B_STATE(0);
MOTOR2_C_STATE(0);
MOTOR2_D_STATE(1);
							break;
						case 2:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 3:
							nCalca=0;
							Motor2_do_step++;				
MOTOR2_A_STATE(0);
MOTOR2_B_STATE(0);
MOTOR2_C_STATE(0);
MOTOR2_D_STATE(1);
							break;
						case 4:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 5:
							nCalca=0;
							Motor2_do_step++;
MOTOR2_A_STATE(0);
MOTOR2_B_STATE(0);
MOTOR2_C_STATE(1);
MOTOR2_D_STATE(1);				
							break;
						case 6:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 7:
							nCalca=0;
							Motor2_do_step++;
MOTOR2_A_STATE(0);
MOTOR2_B_STATE(0);
MOTOR2_C_STATE(1);
MOTOR2_D_STATE(0);				
							break;
						case 8:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 9:
							nCalca=0;
							Motor2_do_step++;
MOTOR2_A_STATE(0);
MOTOR2_B_STATE(1);
MOTOR2_C_STATE(1);
MOTOR2_D_STATE(0);
							break;
						case 10:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 11:
							nCalca=0;
							Motor2_do_step++;
MOTOR2_A_STATE(0);
MOTOR2_B_STATE(1);
MOTOR2_C_STATE(0);
MOTOR2_D_STATE(0);
							break;
						case 12:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 13:
							nCalca=0;
							Motor2_do_step++;
MOTOR2_A_STATE(1);
MOTOR2_B_STATE(1);
MOTOR2_C_STATE(0);
MOTOR2_D_STATE(0);
							break;
						case 14:
							if(nCalca>dododyes)
							{ nCalca=0; Motor2_do_step++; }
							else
							{ nCalca++; }
							break;
						case 15:
							nCalca=0;
							Motor2_do_step++;
MOTOR2_A_STATE(1);
MOTOR2_B_STATE(0);
MOTOR2_C_STATE(0);
MOTOR2_D_STATE(0);
							break;
						case 16:
							Motor2_do_step=1;
							break;
					}
		}
		else
		{
					//πÿµÙœﬂ»¶Ã◊µƒ»Œ∫ŒÕ®µÁ––Œ™
					MOTOR2_A_STATE(0);
					MOTOR2_B_STATE(0);
					MOTOR2_C_STATE(0);
					MOTOR2_D_STATE(0);
					motor2_p_or_n=0;
		}
}

void sceMotorDemo_do(void)
{
		if(1==motor_demo_do)
		{
					monLimitState1L=MOTOR1_L_LIMIT_STATE();
					monLimitState1R=MOTOR1_R_LIMIT_STATE();
					monLimitState2L=MOTOR2_L_LIMIT_STATE();
					monLimitState2R=MOTOR2_R_LIMIT_STATE();
					switch(current_demo_step)
					{
						case 1:
							if(0==monLimitState1L)
							{
								int i=0;
								current_demo_step=2;
								for(i=0;i<100;i++)
								{
									STM32_Delay_ms(20);
								}
							}
							else
							{
								Motor1_do(3);
							}
							break;
						case 2:
							if(0==monLimitState2L)
							{
								int i=0;
								current_demo_step=3;
								for(i=0;i<100;i++)
								{
									STM32_Delay_ms(20);
								}
							}
							else
							{
								Motor2_do(3);
							}
							break;
						case 3:
							if(0==monLimitState2R)
							{
								int i=0;
								current_demo_step=4;
								for(i=0;i<100;i++)
								{
									STM32_Delay_ms(20);
								}
							}
							else
							{
								Motor2_do(4);
							}
							break;
						case 4:
						{
							int i=0;
							Motor2_do(0);//Õ£÷πµÁª˙
							
							//◊Ë»˚”““∆µΩ∞Î≥Ã
							for(i=0;i<100;i++)
							{
								Mon2blockTurnLeft();
							}
							current_demo_step=5;
						}
							break;
						case 5:
							if(0==monLimitState1R)
							{
								motor_demo_do=0;
								current_demo_step=0;
							}
							else
							{
								Motor1_do(4);
							}
						break;
					}
		}
		else if(2==motor_demo_do)
		{
					monLimitState1L=MOTOR1_L_LIMIT_STATE();
					monLimitState1R=MOTOR1_R_LIMIT_STATE();
					monLimitState2L=MOTOR2_L_LIMIT_STATE();
					monLimitState2R=MOTOR2_R_LIMIT_STATE();
					switch(current_demo_step)
					{
						case 1:
							if(0==monLimitState1L)
							{
								current_demo_step=2;
							}
							else
							{
								Motor1_do(3);
							}
							break;
						case 2:
							motor_demo_do=0;
							current_demo_step=0;
						break;
					}
		}
		else if(3==motor_demo_do)
		{
					monLimitState1L=MOTOR1_L_LIMIT_STATE();
					monLimitState1R=MOTOR1_R_LIMIT_STATE();
					monLimitState2L=MOTOR2_L_LIMIT_STATE();
					monLimitState2R=MOTOR2_R_LIMIT_STATE();
					switch(current_demo_step)
					{
						case 1:
							if(0==monLimitState1R)
							{
								current_demo_step=2;
							}
							else
							{
								Motor1_do(4);
							}
						break;
						case 2:
							motor_demo_do=0;
							current_demo_step=0;
							break;
					}
		}
}

void Motor1_do_intpr_cmd(int p_or_n)
{
			Motor1_do(p_or_n);
			motor_demo_do=0;
			current_demo_step=0;
}

void Motor2_do_intpr_cmd(int p_or_n)
{
			Motor2_do(p_or_n);
			motor_demo_do=0;
			current_demo_step=0;
}

/*
0Õ£÷π
1,2 ≤ΩΩ¯“ª∂Œ
3,4 “ª÷±µΩºÏ≤‚Œª
*/
void Motor1_do(int p_or_n)
{
		if(motor1_p_or_n==p_or_n)
		{return;}
		motor1_p_or_n=p_or_n;
		Motor1_do_step=1;
		xiii=0;
}
void Motor2_do(int p_or_n)
{
		if(motor2_p_or_n==p_or_n)
		{return;}
		motor2_p_or_n=p_or_n;
		Motor2_do_step=1;
		xiii2=0;
}
void Motor_demo(void)
{
		motor_demo_do=1;
		current_demo_step=1;
}

void Motor_demo_up(void)
{
		motor_demo_do=2;
		current_demo_step=1;
}

void Motor_demo_down(void)
{
		motor_demo_do=3;
		current_demo_step=1;
}
