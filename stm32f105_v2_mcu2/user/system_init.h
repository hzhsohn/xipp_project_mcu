#ifndef __SYSTEM_INIT_H_
#define __SYSTEM_INIT_H_
#include "stm32f10x_conf.h"
#include "global.h"


typedef struct _TagTimeingSetting{
		unsigned char a;
		unsigned char b;
}TagTimeingSetting;

#define _unit16(x) 							RELAY1_STATE(x)			//��Ħ��ů��Դ
#define _unit17(x) 							RELAY2_STATE(x)			//�����  ���շ���
#define _unit18(x) 							RELAY3_STATE(x)			//�����  ���շ���
#define _unit19(x) 		 					RELAY4_STATE(x)			//�ҳ���  ���շ���
#define _unit20(x) 							RELAY5_STATE(x)			//�ҷ���  ���շ���
#define _unit21(x) 							RELAY6_STATE(x)			//���ҳ�  ���շ���
#define _unit22(x) 							RELAY7_STATE(x)			//���ҷ�  ���շ���
#define _unit23(x) 				 			RELAY8_STATE(x) 		//�������  ���շ���
#define _unit24(x) 							RELAY9_STATE(x)			//����  ���շ���
#define _unit25(x) 				 			RELAY10_STATE(x)		//������  ���η���
#define _unit26(x)							RELAY11_STATE(x) 		//������  ���η���
#define _unit27(x) 	 						RELAY12_STATE(x)		//Ԥ��
#define _unit10(x) 	 						RELAY13_STATE(x)		//����

#endif
