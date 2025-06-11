#include "led1.h"
#include "timer_interrupts.h"
#include "keyboard1.h"

void Automat()
{
	
	typedef enum {eLED_LEFT, eLED_RIGHT, eSTAND_STILL} eAutomatState;
	static eAutomatState eCurrentState = eSTAND_STILL;

	switch (eCurrentState) {
	 case eSTAND_STILL:  
		if(eKeyboardRead() == BUTTON_0){
		eCurrentState = eLED_LEFT;
		}	
		else if (eKeyboardRead() == BUTTON_2){
		eCurrentState = eLED_RIGHT;
		}
		break;
		
	 case eLED_LEFT:  
		if (eKeyboardRead() == BUTTON_1) {
     eCurrentState = eSTAND_STILL; 
     } 
		 else {
      LedStepLeft();
     }
     break;
		 
	 case eLED_RIGHT:  
		if (eKeyboardRead() == BUTTON_1) {
     eCurrentState = eSTAND_STILL; 
     } 
		 else {
      LedStepRight();
     }
     break;
 }
}

int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	Timer0Interrupts_Init(2, &Automat);

	while(1){
	 	iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
	}
}
