#include "keyboard.h"
#include "led.h"

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
        KeyboardInit();
        while(1){
            switch (eLedState){
                case LEDSTOP:
                    if (eKeyboardRead()==BUTTON_0){
                        eLedState=LEDLEFT;

                    }
                    else if(eKeyboardRead()==BUTTON_2){
                        eLedState=LEDRIGHT;
                    }
                    else{
                        eLedState=LEDSTOP;
                    }
                    break;

                case LEDLEFT:

                    if (eKeyboardRead()==BUTTON_1){
                        eLedState=LEDSTOP;
                    }
                    else if(eKeyboardRead()==BUTTON_3){
                        eLedState=LEDBLINK;
                    }
                    else {
                        LedStepLeft();
                        eLedState=LEDLEFT;
                    }
                    break;

                case LEDRIGHT:

                    if (eKeyboardRead()==BUTTON_1){
                        eLedState=LEDSTOP;
                    }
                    else {
                        LedStepRight();
                        eLedState=LEDRIGHT;
                    }
                    break;
										
                 case LEDBLINK:
										if (ucBlinkcounter==66){
												eLedState=LEDRIGHT;
												ucBlinkcounter=0;
										}
										else {
											if (ucBlinkcounter%2==0){
												LedOn(1);
												ucBlinkcounter++;
										}
											else {
												LedOn(4);
											  ucBlinkcounter++;
										}									 										
										break;
									}
									}
        Delay(100);
    }
}



