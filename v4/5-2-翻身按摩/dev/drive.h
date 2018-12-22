/****************************************copyright (C)*******************************************************
***-------------文件信息------------------------------------------------------------------------------------
***	文件		:	drive.h
*** 版本		:	v1.0		
***	创建时间	:	2012/08/06		 
***	创建人		:	林木泉
***	描述		:	本文件为dirve目录向外部提供方法及数据的总接口，drive目录下驱动的编写者为每一个驱动
***					编写一个.c和.h，.c文件尽量封装好，将方法和数据声明在对应.h文件。最后在drive目录添
***					包含如你驱动的.h。而用户只需包含drive.h文件，并配合help文档的说明就可以调用驱动
**************************************************************************************************************/
#ifndef __DRVIE_H__
#define __DRVIE_H__


//-------------------------------------一些公用的定义------------------------------------------------------//
typedef unsigned char  	uchar;
typedef unsigned int 	  uint;
typedef unsigned char 	BYTE;
typedef unsigned char 	BOOL; 
typedef unsigned char  	uint8;                   /* defined for unsigned 8-bits integer variable 	无符号8位整型变量  */
typedef signed   char  	int8;                    /* defined for signed 8-bits integer variable		有符号8位整型变量  */
typedef unsigned short 	uint16;                  /* defined for unsigned 16-bits integer variable 	无符号16位整型变量 */
typedef signed   short 	int16;                   /* defined for signed 16-bits integer variable 		有符号16位整型变量 */
typedef unsigned int   	uint32;                  /* defined for unsigned 32-bits integer variable 	无符号32位整型变量 */
typedef signed   int   	int32;                   /* defined for signed 32-bits integer variable 		有符号32位整型变量 */
typedef float          	fp32;                    /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
typedef double         	fp64;                    /* double precision floating point variable (64bits) 双精度浮点数（64位长度） */

typedef unsigned char  	u8;


//-------------------------------------共用头文件包含------------------------------------------------------//
#include	<stdio.h>
#include	<stdlib.h>
#include 	<math.h>
#include	<string.h>




#endif
