#include <LPC21xx.H>

#include "led.h"

#define LED0_bm 0x00010000 
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

enum eStepDirections {LEFT,RIGHT};

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
