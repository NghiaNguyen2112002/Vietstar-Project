/*
 * File:   main.c
 * Author: DELL
 *
 * Created on December 9, 2022, 11:15 PM
 */

#include "main.h"
void init_system(void);


void interrupt ISR(){
    if(TMR1IF == 1 && TMR1IE == 1){
        stop_timer1();
        TMR1IF = 0; 
        start_timer1();
        timer1_isr();
    }
}

void main(void) {
    init_system();
    
 
//    LcdPrintNumS(0, 0, 12345);
//    LcdPrintCharS(0, 1, 'a');
                
    LcdPrintStringS(0, 0, "xin chao ban nha");
    LcdPrintStringS(1, 0, "Tui ten la Nghia");
    while(1){
        if(flag_timer1){
            flag_timer1 = 0;
            DisplayLcdScreen();
        }
    }
    
    return;
}


void init_system(void){
    CMCON = 0x07;               //turn off comparasion mode => PA can be used
    PCONbits.OSCF = 1;          //set 4MHz internal osc
        
    LCD_DDR  = 0x00;
    init_lcd();

    init_interrupt();
    init_timer1(10000);          //timer1 10ms
    
    SetTimer1_ms(50);           //this timer is used to refresh LCD every 50ms
    
}