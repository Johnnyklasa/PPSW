#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"
#include "timer.h"
#include "servo.h"
#include "uart.h"









int main (){
	 
		KeyboardInit();
		ServoInit(50);
		UART_InitWithInt(9600);
	  
	while(1){
		switch(cOdebranyZnak){
		case '1':
			ServoGoTo(50);
			break;
		
		case 'C':
			ServoCallib();
			break;
		 default:
			 break;
	}
 cOdebranyZnak = 0;		
}
}
