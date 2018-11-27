#ifndef _LOGIC_PROTOCOL_H__

#ifdef __cplusplus
extern "C"{
#endif

void recvLogic(int a,int b,unsigned char* data);
	
//部分获取传感器数据
void s1_001(unsigned char*data);
void s2_001(unsigned char*data);
void s3_001(unsigned char*data);
void s4_001(unsigned char*data);
void s5_001(unsigned char*data);

//	
void s1_002(unsigned char*data);
void s2_002(unsigned char*data);
void s3_002(unsigned char*data);
void s4_002(unsigned char*data);
void s5_002(unsigned char*data);

#ifdef __cplusplus
}
#endif
#define _LOGIC_PROTOCOL_H__
#endif
