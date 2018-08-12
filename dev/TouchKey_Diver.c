#include "TouchKey_Diver.h"
u8_t nTouchKey=0xFF;
u8_t nTouchKeyCnt=0;

Func_Staus bButton1=_Disable;
Func_Staus bButton2=_Disable;
Func_Staus bButton3=_Disable;
Func_Staus bButton4=_Disable;
Func_Staus bButton5=_Disable;
Func_Staus bButton6=_Disable;
Func_Staus bButton7=_Disable;
Func_Staus bButton8=_Disable;

#define TOUCHKEY_NONE_VALUE                     0xFF
#define TOUCHKEY_TURNON_VALUE										0xFE

#define TOUCHKEY_BUTTON1_VALUE									0xFD
#define TOUCHKEY_BUTTON2_VALUE									0xFB
#define TOUCHKEY_BUTTON3_VALUE									0xF7
#define TOUCHKEY_BUTTON4_VALUE									0xEF
#define TOUCHKEY_BUTTON5_VALUE									0xDF
#define TOUCHKEY_BUTTON6_VALUE									0xBF
#define TOUCHKEY_BUTTON7_VALUE									0x7F

/*--------------------------------------------------
//
//-------------------------------------------------*/
void TouchKey_Init(void)
{
	GPIO_InitTypeDef GPIO_MyStruct;
	/* ±÷” πƒ‹*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_1_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_1_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_2_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_2_GPIO, &GPIO_MyStruct);

	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_3_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_3_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_4_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_4_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_5_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_5_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_6_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_6_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_7_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_7_GPIO, &GPIO_MyStruct);
	
	GPIO_MyStruct.GPIO_Pin = TOUCHKEY_8_PIN;
  GPIO_MyStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_MyStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(TOUCHKEY_8_GPIO, &GPIO_MyStruct);
	
}
/*--------------------------------------------------
//

//-------------------------------------------------*/
u8_t TouchKey_Collect(void)
{
  u8_t nKeyBuff=0xfe;
	if (TOUCHKEY_8_STATE()!=RESET)
	{
		nKeyBuff=nKeyBuff|0x01;
	}
	nKeyBuff=nKeyBuff<<1;
	
	if (TOUCHKEY_7_STATE()!=RESET)
	{
		nKeyBuff=nKeyBuff|0x01;
	}
	nKeyBuff=nKeyBuff<<1;

	if (TOUCHKEY_6_STATE()!=RESET)
	{
		nKeyBuff=nKeyBuff|0x01;
	}
	nKeyBuff=nKeyBuff<<1;

	if (TOUCHKEY_5_STATE()!=RESET)
	{
		nKeyBuff=nKeyBuff|0x01;
	}
	nKeyBuff=nKeyBuff<<1;
	//
	if (TOUCHKEY_4_STATE()!=RESET)
	{
		nKeyBuff=nKeyBuff|0x01;
	}
	nKeyBuff=nKeyBuff<<1;
	
	if (TOUCHKEY_3_STATE()!=RESET)
	{
		nKeyBuff=nKeyBuff|0x01;
	}
	nKeyBuff=nKeyBuff<<1;
	
	if (TOUCHKEY_2_STATE()!=RESET)
	{
		nKeyBuff=nKeyBuff|0x01;
	}
	nKeyBuff=nKeyBuff<<1;
	
	if (TOUCHKEY_1_STATE()!=RESET)
	{
		nKeyBuff=nKeyBuff|0x01;
	}
	nKeyBuff=nKeyBuff<<1;
	
	return nKeyBuff;
}
/*--------------------------------------------------
//
//-------------------------------------------------*/
void TouchKey_Scan(void)
{
	u8_t nKeyBuff;
	nKeyBuff=TouchKey_Collect();
	if (nKeyBuff==0xff)
	{
		switch (nTouchKey)
		{
			case TOUCHKEY_NONE_VALUE:
				nTouchKeyCnt=0;
				break;
			case TOUCHKEY_BUTTON1_VALUE:
				if (nTouchKeyCnt>2){
					if (nTouchKeyCnt<=TOUCHKEY_SHORTDOWN_10MS)
					{
						bButton1 = _Enable;
					}
				}
				nTouchKeyCnt=0;
				break;
			case TOUCHKEY_BUTTON2_VALUE:
				if (nTouchKeyCnt>2){
					if (nTouchKeyCnt<=TOUCHKEY_SHORTDOWN_10MS)
					{
						bButton2 = _Enable;
					}
				}
				nTouchKeyCnt=0;
				break;
			case TOUCHKEY_BUTTON3_VALUE:
				if (nTouchKeyCnt>2){
					if (nTouchKeyCnt<=TOUCHKEY_SHORTDOWN_10MS)
					{
						bButton3 = _Enable;
					}
				}
				nTouchKeyCnt=0;
				break;
				
				case TOUCHKEY_BUTTON4_VALUE:
				if (nTouchKeyCnt>2){
					if (nTouchKeyCnt<=TOUCHKEY_SHORTDOWN_10MS)
					{
						bButton4 = _Enable;
					}
				}
				nTouchKeyCnt=0;
				break;
				
				case TOUCHKEY_BUTTON5_VALUE:
				if (nTouchKeyCnt>2){
					if (nTouchKeyCnt<=TOUCHKEY_SHORTDOWN_10MS)
					{
						bButton5 = _Enable;
					}
				}
				nTouchKeyCnt=0;
				break;
				
				case TOUCHKEY_BUTTON6_VALUE:
				if (nTouchKeyCnt>2){
					if (nTouchKeyCnt<=TOUCHKEY_SHORTDOWN_10MS)
					{
						bButton6 = _Enable;
					}
				}
				nTouchKeyCnt=0;
				break;
				
				case TOUCHKEY_BUTTON7_VALUE:
				if (nTouchKeyCnt>2){
					if (nTouchKeyCnt<=TOUCHKEY_SHORTDOWN_10MS)
					{
						bButton7 = _Enable;
					}
				}
				nTouchKeyCnt=0;
				break;
				
				case TOUCHKEY_BUTTON8_VALUE:
				if (nTouchKeyCnt>2){
					if (nTouchKeyCnt<=TOUCHKEY_SHORTDOWN_10MS)
					{
						bButton8 = _Enable;
					}
				}
				nTouchKeyCnt=0;
				break;
		}
	}
	else
	{
		if (nTouchKey!=nKeyBuff)
		{
			nTouchKey=nKeyBuff;
			nTouchKeyCnt=0;
		}
	}
	//-------------------------------------

}
/*--------------------------------------------------
//
//-------------------------------------------------*/
void TOUCHKEY_TIMER_ISR(void)
{
	if(bButton1==_Disable && 
		 bButton2==_Disable && 
		 bButton3==_Disable && 
		 bButton4==_Disable && 
		 bButton5==_Disable &&
		 bButton6==_Disable &&
		 bButton7==_Disable &&
		 bButton8==_Disable )
	{
		if (
						(TOUCHKEY_1_STATE()==RESET)
					||(TOUCHKEY_2_STATE()==RESET)
					||(TOUCHKEY_3_STATE()==RESET)
					||(TOUCHKEY_4_STATE()==RESET)
					||(TOUCHKEY_5_STATE()==RESET)
					||(TOUCHKEY_6_STATE()==RESET)
					||(TOUCHKEY_7_STATE()==RESET)
					||(TOUCHKEY_8_STATE()==RESET)
					)
			{
					nTouchKeyCnt++;
					if (nTouchKeyCnt>=200)
					{
						nTouchKeyCnt=200;
					}
			}
	}
}
