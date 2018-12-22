#ifndef _LOGIC_PROTOCOL_H__

#ifdef __cplusplus
extern "C"{
#endif

/*
//-----------当前清洗小场景
	ezhCleanSenceNone没执行,
	ezhCleanSence1自动化小便																					
	ezhCleanSence2自动化大便 
	ezhCleanSence3护卫
	ezhCleanSence4冲洗
	ezhCleanSence5烘干
	ezhCleanSence6除菌
	ezhCleanSence7按摩
	ezhCleanSence8保暖
	ezhCleanSence9小便
	ezhCleanSence10大便
*/
typedef enum _EzhCleanSence{
	ezhCleanSenceNone=0x00,
	ezhCleanSence1,
	ezhCleanSence2,
	ezhCleanSence3,
	ezhCleanSence4,
	ezhCleanSence5,
	ezhCleanSence6,
	ezhCleanSence7,
	ezhCleanSence8,
	ezhCleanSence9,
	ezhCleanSence10
}EzhCleanSence;

////////////////////////////////////////////////////////////////
//场景延时
void urgentSenceInterrupt(void);
void senceBegin(EzhCleanSence n);
void senceDelayToValue(int*nCalca,int*ppxxStep,int jmpValue,int delay_ms);
void senceDelayToNext(int*nCalca,int*ppxxStep,int delay_ms);
void senceNext(int*nCalca,int*ppxxStep);
void senceDone(void);

//循环
void LitteSenceRun(void);

//
void litteSenceRunAutoXuXu(void);
void litteSenceRunAutoPooPoo(void);
void litteSenceRunXuXu(void);
void litteSenceRunPooPoo(void);
void litteSenceRunHuWai(void);
void litteSenceRunChongXi(void);
void litteSenceRunHongGan(void);
void litteSenceRunChuQun(void);
void litteSenceRunAnMo(void);
void litteSenceRunBaoNang(void);

#ifdef __cplusplus
}
#endif
#define _LOGIC_PROTOCOL_H__
#endif
