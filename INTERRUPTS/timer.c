#include <LPC21xx.H>
#include "timer.h"
#define Timer0_ON_bm (1<<0)
#define Timer0_RESET_bm (1<<1)

void InitTimer0(){
	T0TCR = Timer0_ON_bm;
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR |= Timer0_RESET_bm;
	T0TCR = T0TCR&(~Timer0_RESET_bm);
	while (T0TC<=(uiTime*15)){}
}




