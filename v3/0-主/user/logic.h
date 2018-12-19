#ifndef _LOGIC_PROTOCOL_H__

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _TzhDoCmd{
	unsigned char bid; //板号
	unsigned char fid; //功能
	int second;
	char buf[10];	
	int buflen;
}TzhDoCmd;
	
//
void sendLogic(void);
void recvLogic(int a,int b,unsigned char* data);
void addLogicCmd(unsigned char b,unsigned char f,int doSecond,unsigned char*data,int dataLen);
int getCmdCount(void);
//紧急停止
void stopSend(void);
	
//部分获取传感器数据
void dev_status(void);
	
//
void s1_000(int b,unsigned char*data);
void s2_000(int b,unsigned char*data);
void s3_000(int b,unsigned char*data);
void s4_000(int b,unsigned char*data);
void s5_000(int b,unsigned char*data);


#ifdef __cplusplus
}
#endif
#define _LOGIC_PROTOCOL_H__
#endif
