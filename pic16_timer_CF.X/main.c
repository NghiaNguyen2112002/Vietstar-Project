/*
 * File:   main.c
 * Author: DELL
 *
 * Created on October 11, 2022, 3:27 PM
 */
#include "main.h"

enum MODE_FSM {INIT, ADJUSTING, AUTO_BREWING, AUTO_CLEANING};
enum MODE_FSM mode;

unsigned char   addressEEPROMused = 0x00;
unsigned char   TIME;

unsigned char   index = 0;
unsigned char   pumpState = 0;          //0: turn off,  1: turn on

unsigned char   RUN_button_counter = 0;
unsigned char   cleaning_counter;
void InitSystem(void);

void Delay_ms(unsigned int delay);

void RelayOn(unsigned char flag);

unsigned char ReadEEPROM(unsigned char address);
void WriteEEPROM(unsigned char address, unsigned char data);

void interrupt timer1(){
    if(TMR1IF == 1 && TMR1IE == 1){
        stop_timer1();
        TMR1IF = 0; 
        start_timer1();
        timer1_isr();
        button_reading();
        if(index > 1) index = 0;
        UpdateLed(index++);
    }
}
void main(void) {
    InitSystem();
    unsigned char counter = 0;

    while(1){

        switch(mode){
        case INIT:
            if(!is_button_pressed(RUN)) mode = ADJUSTING;
        break;
        case ADJUSTING:
            //ADJUST TIME
            UpdateLedBuffer(TIME);
            RelayOn(0);
            if(is_button_held(UP)){
                TIME++;
                if(TIME < 0 || TIME > 99) TIME = 0;

                UpdateLedBuffer(TIME);
                WriteEEPROM(addressEEPROMused, TIME);
                Delay_ms(100);
            }
            else if(is_button_held(DOWN)){               
                TIME--;
                if(TIME < 0 || TIME > 99) TIME = 0;

                UpdateLedBuffer(TIME);
                WriteEEPROM(addressEEPROMused, TIME);
                Delay_ms(100);
            }
            else if(is_button_pressed(RUN)){
                //buton still pressed
                while(is_button_held(RUN)){
                    if(is_button_pressed_s(RUN)){
                        pumpState = 0;
                        cleaning_counter = CLEANING_TIMES;
                        mode = AUTO_CLEANING;   
                        break;
                    }
                    else {
                        SetTimer1_ms(1000);
                        counter = 0;
                        mode = AUTO_BREWING;
                    }
                }
            }
        break;
        case AUTO_BREWING:
            RelayOn(1);
            UpdateLedBuffer(counter);
       
            if(flag_timer1){
                counter++;
                flag_timer1 = 0;
            }
            if(counter >= TIME) mode = INIT;
            if(is_button_pressed(RUN)) mode = INIT;
        break;
        case AUTO_CLEANING:
            UpdateLedBuffer(cleaning_counter);
            if(flag_timer1){
                //turn on pump
                if(pumpState == 0){
                    //pump is off
                    pumpState = 1;
                    
                    RelayOn(1); //turn on pump
                    SetTimer1_ms(10000); //pump on in 10000ms
                }
                else {
                    //pump is on
                    pumpState = 0;
                    cleaning_counter--;
                    RelayOn(0);
                    SetTimer1_ms(2000); //pump off in 2000ms
                }
            }
            if(cleaning_counter == 0) mode = INIT;
            if(is_button_pressed(RUN)) mode = INIT;
            break;
        default: 
             break;
        }
        
        Delay_ms(3);
    }
    return;
}

void InitSystem(void){
    CMCON = 0x07;
    
    TRIS_BUTTON = 0b00110100;
    TRIS_LED    = 0b00000000;
    
    PORT_BUTTON = 0xFF;
    PORT_LED = 0xFF;
    
    cleaning_counter = CLEANING_TIMES;
    mode = INIT;
    RelayOn(0);
    
    init_timer1(TIMER1_TIME);       //timer1 10ms   
    SetTimer1_ms(1000);
    
    TIME = ReadEEPROM(addressEEPROMused);
    if(TIME < 0 || TIME > 99) TIME = 0;
    
    UpdateLedBuffer(TIME);
}


void Delay_ms(unsigned int delay){
    unsigned int i, j;
    for(i = 0; i < delay; i++){
        for(j = 0; j < 141; j++);
    }
}

void RelayOn(unsigned char flag){
    if(flag == 0) BIT_RELAY = 0;
    else BIT_RELAY = 1;
}

unsigned char ReadEEPROM(unsigned char address){
    EEADR = address;
    EECON1bits.RD = 1; //enable read
    return EEDATA;
}
void WriteEEPROM(unsigned char address, unsigned char data){
    EEADR = address;
    EEDATA = data;
    EECON1bits.WREN = 1;    //allow write cycles
    INTCONbits.GIE = 0;     //disable interrupt
    EECON2=0x55; //Required sequence for write to internal EEPROM
    EECON2=0xAA; //Required sequence for write to internal EEPROM   
    EECON1bits.WR = 1;      //enable write
    INTCONbits.GIE = 1;     //enable interrupt
    
    while(PIR1bits.EEIF == 0);
    PIR1bits.EEIF = 0;
}