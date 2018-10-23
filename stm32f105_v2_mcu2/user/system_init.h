#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"


typedef struct _TagTimeingSetting{
		unsigned char pooDelay;				//��ʺ����������� ,��λ����
		unsigned char xuxuDelay;			//��ʺ����������� ,��λ��
		unsigned char pooFlush;				//ʺʺ��ϴ  ,��λ��
		unsigned char xuxuFlush;			//�����ϴ  ��λ ��
		unsigned char pooDry;      		//ʺʺ���ʱ�� ��λ ����
		unsigned char xuxuDry;				//������ʱ�� ��λ ����
		unsigned char pooSterilize;		//ʺʺ����ʱ�� ��λ ��
		unsigned char xuxuSterilize;	//��������ʱ�� ��λ ��
	  unsigned char crotchPressure;	//�㵵��ѹ ��λ 100��ѹ����
		unsigned char bedPressure;   	//�������ѹ  ��λ 100��ѹ����
		unsigned char waterTemperature;//���ˮ��   ��λ���϶�
		unsigned char airTemperature;  //��ͺ���¶�   ��λ���϶�
		unsigned char mpuLeft; 				//���
		unsigned char mpuRight;  			//�ҽ�
}TagTimeingSetting;

#endif
