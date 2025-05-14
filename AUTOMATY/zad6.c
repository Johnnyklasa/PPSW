#include <LPC21xx.H> 

#include "keyboard.h"

#define LED0_bm 0x10000 

#define LED1_bm 0x20000

#define LED2_bm 0x40000

#define LED3_bm 0x80000

#define S0_bm 0x10

#define S1_bm 0x40

#define S2_bm 0x20

#define S3_bm 0x80





enum eKeyboardState {RELASED, BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3};

enum eStepDirections {LEFT,RIGHT};



void Delay(int iDelayInMS){


int iLoopCounter;

iDelayInMS=iDelayInMS*12000;

for(iLoopCounter=0; iLoopCounter< iDelayInMS; iLoopCounter++)

{

}

}



void LedInit()

{

	IO1DIR = IO1DIR|(LED0_bm|LED1_bm|LED2_bm|LED3_bm);

	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;

	IO1SET = LED0_bm;

}


void LedOn(unsigned char ucLedIndeks){

	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;

	switch(ucLedIndeks){

		case(0):

			IO1SET = LED0_bm;

			break;

		case(1):

			IO1SET = LED1_bm;

			break;

		case(2):

			IO1SET = LED2_bm;

			break;

		case(3):

			IO1SET = LED3_bm;

			break;

		default:

			break;

}

}




enum eKeyboardState eKeyboardRead(){

if((IO0PIN & S0_bm)==0){

return BUTTON_0;

}

else if ((IO0PIN & S1_bm)==0){


return BUTTON_1;

}

else if ((IO0PIN & S2_bm)==0){



return BUTTON_2;

}

else if ((IO0PIN & S3_bm)==0){

return BUTTON_3;

}

else{

return RELASED;

}

}


void KeyboardInit(){


IO0DIR= IO0DIR & (~(S0_bm|S1_bm|S2_bm|S3_bm));

}




void LedStep(enum eStepDirections eDirection){

static unsigned char sucLedNumber=0; 

switch(eDirection){

case LEFT: 

sucLedNumber++;

break;

case RIGHT:

sucLedNumber--;

break;

default: 
break;

}

LedOn(sucLedNumber%4);

}


void LedStepLeft(void){

LedStep(LEFT);

}


void LedStepRight(void){

LedStep(RIGHT);

}
enum eLedState {LedLeft,LedRight,LedStop};
enum eLedState eLedState=LedStop;
//static int iStepCounter=0;


int main(){

		LedInit();
		KeyboardInit();
		while(1){
			switch (eLedState){
				case LedStop:
					if (eKeyboardRead()==BUTTON_0){
						eLedState=LedLeft;
						
					}
					else if(eKeyboardRead()==BUTTON_2){
						eLedState=LedRight;
					}
					else{
						eLedState=LedStop;
					}
					break;
					
				case LedLeft:
					LedStepLeft();
					if (eKeyboardRead()==BUTTON_1){
						eLedState=LedStop;
					}
					else {
						eLedState=LedLeft;
					}	
					break;
					
					case LedRight:
						LedStepRight();
						if (eKeyboardRead()==BUTTON_1){
							eLedState=LedStop;						
						}
						else {
							eLedState=LedRight;				
						}			
		}
		Delay(100);
	}
}
