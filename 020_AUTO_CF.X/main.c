/*
 * File:   main.c
 * Author: DELL
 *
 * Created on December 9, 2022, 11:15 PM
 */

#include "main.h"

void SYS_Init(void);

void main(void) {
    SYS_Init();
    

    while(1){
        FSM_ModeControl();
        
        if(flag_timer1){
            flag_timer1 = 0;
            DisplayLcdScreen();
            
            if(_countAuto >= 5){
                _countAuto -= 5;
            }
            if(_counterDelay >= 1){
                _counterDelay -= 1;
            }
        }
    }
    
    return;
}


void SYS_Init(void){
    
    OSCCONbits.IRCF = 0b1101;   //set 4MHz internal osc
    
    INT_Init();
    TMR1_Init(10000);

    BTN_Init();
    init_lcd();
    FSM_Init();
    
    TMR1_SetTime_ms(50);           //this timer is used to refresh LCD every 50ms
    
    EEP_ReadAutoTime();
    EEP_ReadCupTotal();
}