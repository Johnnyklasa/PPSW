#include <LPC21xx.H>

#include "keyboard.h"

#define S0_bm 0x0000000010
#define S1_bm 0x0000000040
#define S2_bm 0x0000000020
#define S3_bm 0x0000000080

void KeyboardInit(){
	
	IO0DIR= IO0DIR & (~(S0_bm|S1_bm|S2_bm|S3_bm));
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

