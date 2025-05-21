#include <LPC21xx.H>
#include "timer.h"

#define TIMER_ON_bm (1<<0)
#define TIMER_RESET_bm (1<<1)
#define TIMER_INTERRUPT_bm (1<<0)
#define TIMER_MR_RESET_bm (1<<1)
#define TIMER_FLAG_bm (1<<0)

void InitTimer0(){
	T0TCR = TIMER_ON_bm; // Wlaczanie timera
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0MR0 = (iDelayTime * 15); // Ustawia czas, po którym timer resetuje
	T0MCR = (TIMER_INTERRUPT_bm | TIMER_MR_RESET_bm); // Ustawia mozliwosc przerwania i resetu
	T0TCR |= TIMER_RESET_bm; // Resetuje timer
	T0TCR &= (~TIMER_RESET_bm); // Wylacza reset
	
	InitTimer0(); // Wlacza timer
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR |= TIMER_RESET_bm; 
	T0TCR &= (~TIMER_RESET_bm); 
	while (T0TC <= (uiTime * 15)){} // Czeka az licznik timera osiagnie wartosc
}

void WaitOnTimer0Match0(){
	while ((T0IR & TIMER_FLAG_bm) == 0){} // Czeka, az pojawi sie flaga przerwania
	T0IR = TIMER_FLAG_bm;	// Resetuje flage
}


