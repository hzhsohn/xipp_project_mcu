#include "watchdog.h"


void watchdoy_delay(int ms)
{
		int i=0;
		for(i=0;i<ms;i++)
		{
			int n=0;
			for(n=0;n<72*50;n++)
			__asm("nop");
		}
}
