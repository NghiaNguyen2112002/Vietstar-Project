#include "interrupt.h"


void init_interrupt(void){
	INTCONbits.GIE = 1;  //enable global interrupt
	INTCONbits.PEIE = 1; //disasble peripheral External Interupt Enable}
}


void interrupt ISR(){
    if(TMR1IF == 1 && TMR1IE == 1){
        stop_timer1();
        TMR1IF = 0; 
        start_timer1();
        timer1_isr();
    }
}