/*
 * File:   main.c
 * Author: DELL
 *
 * Created on December 9, 2022, 11:15 PM
 */

#include "main.h"

void SYS_Init(void);

void Delay_ms(unsigned char time) ;

void main(void) {
    SYS_Init();
    LcdPrintStringS(0,0, "Vietstar  Coffee");
    DisplayLcdScreen();
    Delay_ms(2000);
    
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
    ANSC0 = 0;
    ANSC1 = 0;
    ANSC2 = 0;
    ANSC3 = 0;
    ANSC6 = 0;
    ANSC7 = 0;
    TRISC = 0x00;

    INT_Init();
    TMR1_Init(10000);

    BTN_Init();
    init_lcd();
    FSM_Init();
    
    TMR1_SetTime_ms(50);           //this timer is used to refresh LCD every 50ms
    
    EEP_ReadAutoTime();
    EEP_ReadCupTotal();
}

void Delay_ms(unsigned char time) 
{
    int i,j;
    for(i=0;i<time;i++)
        for(j=0;j<1;j++);
}