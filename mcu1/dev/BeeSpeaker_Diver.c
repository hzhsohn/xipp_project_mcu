#include "BeeSpeaker_Diver.h"
/*--------------------------------------------------
//
//-------------------------------------------------*/
void BeeSpeak_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/* ±÷” πƒ‹*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_MyStruct.GPIO_Pin = BEESPECKER_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(BEESPECKER_GPIO, &GPIO_MyStruct);
	BEESPECKER_STATE(LOW);
}



/*--------------------------------------------------
//
//-------------------------------------------------*/
void LED_TIMER_ISR(void)
{

}
