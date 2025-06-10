#include "led.h"
#include "keyboard.h"
#include "timer.h"
#include "timer_interrupts.h"


void Automat(){
	enum LedState{LEDRIGHT, LEDSTOP, LEDLEFT};
	enum LedState eLedState = LEDSTOP;
		switch (eLedState){
		case LEDRIGHT:
			LedStepRight();
			if(eKeyboardRead()==BUTTON_1){
				eLedState=LEDSTOP;
			}
			else{
				eLedState = LEDRIGHT; }
			break;
		case LEDLEFT:
			LedStepLeft();
			if(eKeyboardRead()==BUTTON_1){
				eLedState = LEDSTOP; }
			else{
				eLedState = LEDLEFT; }
			break;
		 case LEDSTOP:
				if(eKeyboardRead()==BUTTON_0){
						eLedState= LEDLEFT;}
				else if(eKeyboardRead()==BUTTON_2){
						eLedState = LEDRIGHT;}
				else{
						eLedState = LEDSTOP; }
				break;
			default:
			break; }	
}






int main(){
	unsigned int uiMainLoopCounter;
	LedInit();
	KeyboardInit();
	Timer0InterruptInit(20000,&Automat);
	
	while(1){
		uiMainLoopCounter++;
	}
}













