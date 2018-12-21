#include "mini-data.h"
#include "Stm32f1_uart3.h"
#include "stdio.h"
#include "stdlib.h"
#include "logic.h"

void recvSensorBoard0(unsigned char funcID,unsigned char* data)
{
		switch(funcID)
		{
			case 1: //Êº				
				senceBegin(ezhCleanSence1);
				break;
			case 2: //Äò				
				senceBegin(ezhCleanSence2);
				break; 
		}
}
