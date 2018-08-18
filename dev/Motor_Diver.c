#include "watchdog.h"
#include "Motor_Diver.h"


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



void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/*Ê±ÖÓÊ¹ÄÜ*/
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
		GPIO_MyStruct.GPIO_Pin = MOTOR1_D_PIN;
		GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(MOTOR1_D_GPIO, &GPIO_MyStruct);
		MOTOR1_D_STATE(0);
		
	
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

	//ÊäÈë
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


void sceMotor1_do(void)
{				
		static int dododyes=90;
		static int nCalca=0;
	
		monLimitState1L=MOTOR1_L_LIMIT_STATE();
		monLimitState1R=MOTOR1_R_LIMIT_STATE();
	  if(xiii<xiiiLimit)
		{
						xiii++;
						if(1==motor1_p_or_n && 1==monLimitState1L)
						{
									switch(Motor1_do_step)
									{
										case 1:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½							
											MOTOR1_A_STATE(1);
											MOTOR1_B_STATE(0);
											MOTOR1_C_STATE(0);
											MOTOR1_D_STATE(0);
										case 2:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 3:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½							
											MOTOR1_A_STATE(1);
											MOTOR1_B_STATE(1);
											MOTOR1_C_STATE(0);
											MOTOR1_D_STATE(0);
											break;
										case 4:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 5:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
											MOTOR1_A_STATE(0);
											MOTOR1_B_STATE(1);
											MOTOR1_C_STATE(0);
											MOTOR1_D_STATE(0);						
											break;
										case 6:
											if(nCalca>1000)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 7:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
											MOTOR1_A_STATE(0);
											MOTOR1_B_STATE(1);
											MOTOR1_C_STATE(1);
											MOTOR1_D_STATE(0);						
											break;
										case 8:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 9:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
											MOTOR1_A_STATE(0);
											MOTOR1_B_STATE(0);
											MOTOR1_C_STATE(1);
											MOTOR1_D_STATE(0);
											break;
										case 10:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 11:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
											MOTOR1_A_STATE(0);
											MOTOR1_B_STATE(0);
											MOTOR1_C_STATE(1);
											MOTOR1_D_STATE(1);
											break;
										case 12:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 13:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
											MOTOR1_A_STATE(0);
											MOTOR1_B_STATE(0);
											MOTOR1_C_STATE(0);
											MOTOR1_D_STATE(1);
											break;
										case 14:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 15:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
											MOTOR1_A_STATE(1);
											MOTOR1_B_STATE(0);
											MOTOR1_C_STATE(0);
											MOTOR1_D_STATE(1);
											break;
										case 16:
											Motor1_do_step=1;
											break;
									}

						}
						else if(2==motor1_p_or_n && 1==monLimitState1R)
						{
									switch(Motor1_do_step)
									{
										case 1:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½							
				MOTOR1_A_STATE(1);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(1);
										case 2:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 3:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½							
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(1);
											break;
										case 4:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 5:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(1);
				MOTOR1_D_STATE(1);				
											break;
										case 6:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 7:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(1);
				MOTOR1_D_STATE(0);				
											break;
										case 8:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 9:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(1);
				MOTOR1_C_STATE(1);
				MOTOR1_D_STATE(0);
											break;
										case 10:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 11:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(1);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(0);
											break;
										case 12:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 13:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
				MOTOR1_A_STATE(1);
				MOTOR1_B_STATE(1);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(0);
											break;
										case 14:
											if(nCalca>dododyes)
											{ nCalca=0; Motor1_do_step++; }
											else
											{ nCalca++; }
											break;
										case 15:
											nCalca=0;
											Motor1_do_step++;	//ÏÂÒ»²½
				MOTOR1_A_STATE(1);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(0);
											break;
										case 16:
											Motor1_do_step=1;
											break;
									}
						}
	}
	else
	{
				//¹ØµôÏßÈ¦Ì×µÄÈÎºÎÍ¨µçÐÐÎª
				MOTOR1_A_STATE(0);
				MOTOR1_B_STATE(0);
				MOTOR1_C_STATE(0);
				MOTOR1_D_STATE(0);
	}
}

void sceMotor2_do(void)
{
	static int dododyes=90;
	static int nCalca=0;
	
	monLimitState2L=MOTOR2_L_LIMIT_STATE();
	monLimitState2R=MOTOR2_R_LIMIT_STATE();
	if(xiii2<xiiiLimit)
	{
			xiii2++;
			if(1==motor2_p_or_n && 1==monLimitState2L)
			{
						switch(Motor2_do_step)
						{
							case 1:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?							
								MOTOR2_A_STATE(1);
								MOTOR2_B_STATE(0);
								MOTOR2_C_STATE(0);
								MOTOR2_D_STATE(0);
							case 2:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 3:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?							
								MOTOR2_A_STATE(1);
								MOTOR2_B_STATE(1);
								MOTOR2_C_STATE(0);
								MOTOR2_D_STATE(0);
								break;
							case 4:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 5:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(0);
								MOTOR2_B_STATE(1);
								MOTOR2_C_STATE(0);
								MOTOR2_D_STATE(0);						
								break;
							case 6:
								if(nCalca>1000)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 7:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(0);
								MOTOR2_B_STATE(1);
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
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(0);
								MOTOR2_B_STATE(0);
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
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(0);
								MOTOR2_B_STATE(0);
								MOTOR2_C_STATE(1);
								MOTOR2_D_STATE(1);
								break;
							case 12:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 13:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
								MOTOR2_A_STATE(0);
								MOTOR2_B_STATE(0);
								MOTOR2_C_STATE(0);
								MOTOR2_D_STATE(1);
								break;
							case 14:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 15:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?
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
			else if(2==motor2_p_or_n && 1==monLimitState2R)
			{
						switch(Motor2_do_step)
						{
							case 1:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?							
	MOTOR2_A_STATE(1);
	MOTOR2_B_STATE(0);
	MOTOR2_C_STATE(0);
	MOTOR2_D_STATE(1);
							case 2:
								if(nCalca>dododyes)
								{ nCalca=0; Motor2_do_step++; }
								else
								{ nCalca++; }
								break;
							case 3:
								nCalca=0;
								Motor2_do_step++;	//??ò?2?							
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
								Motor2_do_step++;	//??ò?2?
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
								Motor2_do_step++;	//??ò?2?
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
								Motor2_do_step++;	//??ò?2?
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
								Motor2_do_step++;	//??ò?2?
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
								Motor2_do_step++;	//??ò?2?
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
								Motor2_do_step++;	//??ò?2?
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
	}
	else
	{
				//¹ØµôÏßÈ¦Ì×µÄÈÎºÎÍ¨µçÐÐÎª
				MOTOR2_A_STATE(0);
				MOTOR2_B_STATE(0);
				MOTOR2_C_STATE(0);
				MOTOR2_D_STATE(0);
	}
}

void Motor1_do(int p_or_n)
{
	motor1_p_or_n=p_or_n;
	Motor1_do_step=1;
	xiii=0;
}
void Motor2_do(int p_or_n)
{
	motor2_p_or_n=p_or_n;
  Motor2_do_step=1;
	xiii2=0;
}
void Motor_demo(void)
{
	
}

