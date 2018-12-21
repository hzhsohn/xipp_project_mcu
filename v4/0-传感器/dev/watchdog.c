#include "watchdog.h"

#include "stm32f10x_wwdg.h"
#include "stm32f10x_iwdg.h"

//��ʼ���������Ź�
//prer����Ƶ����0~7(ֻ�е� 3 λ��Ч����
//��Ƶ����=4*2^prer.�����ֵֻ���� 256��
//rlr����װ�ؼĴ���ֵ���� 11 λ��Ч��
//ʱ�����(��ţ���Tout=((4*2^prer��*rlr��/40 (ms����
void wdinit(int prer,int rlr)
{
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //��ʹ�ܶԼĴ��� I д����
  IWDG_SetPrescaler(prer); //������ IWDG Ԥ��Ƶֵ������ IWDG Ԥ��Ƶֵ
  IWDG_SetReload(rlr);//������ IWDG ��װ��ֵ
  IWDG_ReloadCounter(); //�۰��� IWDG ��װ�ؼĴ�����ֵ��װ�� IWDG ������
  IWDG_Enable();//��ʹ�� IWDG
}

void watchdog_init(void)
{
	wdinit(4,625); 
}
void watchdog_action(void)
{
	IWDG_ReloadCounter();//reload
}
