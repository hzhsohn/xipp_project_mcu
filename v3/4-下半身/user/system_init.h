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


#define _unit1(x) 							RELAY1_STATE(x)			//��������  ���η���
#define _unit2(x) 							RELAY2_STATE(x)			//��������  ���η���
#define _unit3(x) 							RELAY3_STATE(x)			//��й����  ���η���
#define _unit4(x) 		 					RELAY4_STATE(x)			//��й����  ���η���
#define _unit5(x) 							RELAY5_STATE(x)			//��ˮ��1  ���շ�����
#define _unit6(x) 							RELAY6_STATE(x)			//��ˮ��2  ���շ��ų嶷
#define _unit7(x) 							RELAY7_STATE(x)			//��ˮ��3  ���շ��ų�PP
#define _unit8(x) 				 			RELAY8_STATE(x) 		//ɱ����
#define _unit9(x) 							RELAY9_STATE(x)			//������ˮ
#define _unit10(x) 				 			RELAY10_STATE(x)		//������
#define _unit11(x)							RELAY11_STATE(x) 		//����ˮ��
#define _unit12(x) 	 						RELAY12_STATE(x)		//��������
#define _unit13(x) 							RELAY13_STATE(x)		//ˮ������  16A
#define _unit14(x) 	 						RELAY14_STATE(x)		//Ԥ��  220V
#define _unit15(x) 							RELAY15_STATE(x)		//������  220V



#endif
