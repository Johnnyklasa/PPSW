#include "keyboard.h"
#include "led.h"
#include "timer.h"

enum eLedState {LEDLEFT,LEDRIGHT,LEDSTOP,LEDBLINK};
enum eLedState eLedState=LEDSTOP;
unsigned char ucBlinkcounter=0;

void Delay(int iDelayInMS){


int iLoopCounter;

iDelayInMS=iDelayInMS*9000;

for(iLoopCounter=0; iLoopCounter< iDelayInMS; iLoopCounter++){}

}


int main(){

        LedInit();
				InitTimer0Match0(10000);
        while(1){
					WaitOnTimer0Match0();
					LedStepLeft();
					
					
				}
}
