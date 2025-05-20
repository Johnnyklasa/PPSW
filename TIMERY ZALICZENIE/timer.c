#include <LPC21xx.H>
#include "timer.h"
#define Timer0_ON_bm (1<<0)
#define Timer0_RESET_bm (1<<1)
#define Timer_interrupt_bm (1<<0)
#define Timer_Reset_mr_bm (1<<1)
#define Timer_Flag_bm (1<<0)

void InitTimer0(){
	T0TCR = Timer0_ON_bm;
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0MR0=(iDelayTime*15);
	T0MCR= (Timer_interrupt_bm|Timer_Reset_mr_bm);
	T0TCR |= Timer0_RESET_bm;
	T0TCR &= (~Timer0_RESET_bm);
	InitTimer0();
}


void WaitOnTimer0(unsigned int uiTime){
	T0TCR |= Timer0_RESET_bm;
	T0TCR = T0TCR&(~Timer0_RESET_bm);
	while (T0TC<=(uiTime*15)){}
}

void WaitOnTimer0Match0(){
	while ((T0IR&Timer_Flag_bm)==0){}
	T0IR=Timer_Flag_bm;		
}




