
/*
ezhCleanSence1 平躺模式
ezhCleanSence2 全涨模式
ezhCleanSence3 转圈圈模式
*/
typedef enum _EzhCleanSence{
	ezhCleanSenceNone=0x00,
	ezhCleanSence1,
	ezhCleanSence2,
	ezhCleanSence3
}EzhCleanSence;

////////////////////////////////////////////////////////////////
void senceBegin(EzhCleanSence n);
void senceDelayToValue(int*nCalca,int*ppxxStep,int jmpValue,int delay_ms);
void senceDelayToNext(int*nCalca,int*ppxxStep,int delay_ms);
void senceNext(int*nCalca,int*ppxxStep);
void senceDone(void);

//
void LitteSenceRun(void);

//
void litteGiaoGiaoZhu(void);
void litteAllFull(void);
void litteQuengQueng(void);

