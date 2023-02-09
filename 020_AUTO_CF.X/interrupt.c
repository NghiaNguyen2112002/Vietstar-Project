#include "interrupt.h"

void INT_Init(void){
	INTCONbits.GIE = 1;  //enable global interrupt
	INTCONbits.PEIE = 1; //disasble peripheral External Interupt Enable
}

void __interrupt() isr(void){
    if(TMR1IF == 1 && TMR1IE == 1){
        TMR1_Stop();
        TMR1IF = 0; 
        TMR1_Start();
        TMR1_Isr();
    }
}
