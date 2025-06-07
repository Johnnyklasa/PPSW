#include <LPC21xx.H>



#define mCOUNTER_ENABLE (1<<1)
#define m_Counter_Reset (1<<2)

#define mINTERRUPT_ON_MR0 (1<<1)
#define mRESET_ON_MR0 (1<<2)
#define MR0_INTERRUPT (1<<1)

//VIC
#define VIC_CHANNEL_NUMBER 5 
#define VECTORCLR_ENABLE (1<<5)

void (*ptrTimer0InterruptFunction) (void);

__irq void Timer0IRQHANDLER(){
	T0IR=MR0_INTERRUPT;
	ptrTimer0InterruptFunction();
	VICVectAddr=0x0;
}

void Timer0InterruptInit(unsigned int uiPeriod, void (*ptrInterruptFunction) (void)){
	VICIntEnable |= (1<<VIC_CHANNEL_NUMBER);
	VICVectCntl1 = (VECTORCLR_ENABLE|VIC_CHANNEL_NUMBER);
	VICVectAddr1= (unsigned long)Timer0IRQHANDLER;
 ptrTimer0InterruptFunction=  ptrInterruptFunction;//ustawiamy zeby ptrtimer wkazywal na funkcje wskazana w deklaracji
	
	T0MR0 = 15 * uiPeriod;                 	      
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0);

     

	T0TCR |=  mCOUNTER_ENABLE;
	
}

//wrzucamy do wskaznika funkcje a potem do funcji init dajemy adres tej funkcji na ktora wskazuje wskaznik

void Led1On(void){
	IO1PIN = ((1<<13)|1);
	IO1SET = (1<<13);
}
	


int main(){
	
	unsigned int ucMianLoopCounter;
	Timer0InterruptInit(1000000,&Led1On);
	while(1){
		ucMianLoopCounter++;
	}
}
	
	
	
	
	
	
	








