#include "watchdog.h"


void watchdoy_delay(int ms)
{
		int i=0;
		int n=0;
		for(i=0;i<ms;i++)
		{
			for(n=0;n<1000;n++);
		}
}
