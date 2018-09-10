#ifndef __AUTO_SenceAct_H_
#define __AUTO_SenceAct_H_
#include "system_init.h"
#include "mini-data.h"

//����ʱ������
typedef struct _TagTimeingSetting{
		uchar pooDelay;				//��ʺ����������� ,��λ����
		uchar xuxuDelay;			//��ʺ����������� ,��λ��
		uchar pooFlush;				//ʺʺ��ϴ  ,��λ��
		uchar xuxuFlush;			//�����ϴ  ��λ ��
		uchar pooDry;      		//ʺʺ���ʱ�� ��λ ����
		uchar xuxuDry;				//������ʱ�� ��λ ����
		uchar pooSterilize;		//ʺʺ����ʱ�� ��λ ��
		uchar xuxuSterilize;	//��������ʱ�� ��λ ��
	  uchar crotchPressure;	//�㵵��ѹ ��λ 100��ѹ����
		uchar bedPressure;   	//�������ѹ  ��λ 100��ѹ����
		uchar waterTemperature;//���ˮ��   ��λ���϶�
		uchar airTemperature;  //��ͺ���¶�   ��λ���϶�
		uchar mpuLeft; 				//���
		uchar mpuRight;  			//�ҽ�
}TagTimeingSetting;

#endif
