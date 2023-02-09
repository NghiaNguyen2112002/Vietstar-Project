/*
 * File:   main.c
 * Author: DELL
 *
 * Created on October 11, 2022, 3:27 PM
 */
#include "main.h"

enum MODE_FSM {
    INIT, ADJUSTING_AUTO_0, ADJUSTING_AUTO_1,
    BREWING_0, BREWING_1, AUTO_CLEANING
};
enum MODE_FSM mode;

unsigned int MAX_COUNTER_AUTO_0, MAX_COUNTER_AUTO_1;
unsigned char addressEEPROM_AUTO_0 = 0x00;
unsigned char addressEEPROM_AUTO_1 = 0x01;


unsigned char pumpState = 0; //0: turn off,  1: turn on
unsigned char brewing_counter, cleaning_counter;


void InitSystem(void);

void Delay_ms(unsigned int delay);

void RelayOn(unsigned char flag);

unsigned char ReadEEPROM(unsigned char address);
void WriteEEPROM(unsigned char address, unsigned char data);

void interrupt ISR() {
    if (TMR1IF == 1 && TMR1IE == 1) {
        stop_timer1();
        TMR1IF = 0;
        start_timer1();
        timer1_isr();
        button_reading();
    }

    if (INTCONbits.INTF == 1) {
        INTCONbits.INTF = 0;
        brewing_counter++;
    }
}

void main(void) {
    InitSystem();

    while (1) {
        switch (mode) {
            case INIT:
                BIT_RELAY = 0;
                brewing_counter = 0;                

                if (is_button_pressed(AUTO_0_BUTTON)) {
                    mode = BREWING_0;
                } else if (is_button_pressed(AUTO_1_BUTTON)) {
                    mode = BREWING_1;
                } else if (is_button_pressed_s(AUTO_0_BUTTON)) {
                    mode = ADJUSTING_AUTO_0;
                } else if (is_button_pressed_s(AUTO_1_BUTTON)) {
                    mode = ADJUSTING_AUTO_1;
                } else if (is_button_pressed(AUTO_CLEANING_BUTTON)) {
                    SetTimer1_ms(10000); //10s
                    BIT_RELAY = 1;
                    cleaning_counter = CLEANING_TIMES;
                    mode = AUTO_CLEANING;
                }
                break;
            case ADJUSTING_AUTO_0:
                BIT_RELAY = 1;
                if (is_button_pressed(AUTO_0_BUTTON)) {
                    MAX_COUNTER_AUTO_0 = brewing_counter;
                    WriteEEPROM(addressEEPROM_AUTO_0, MAX_COUNTER_AUTO_0);
                    mode = INIT;
                }
                break;
            case ADJUSTING_AUTO_1:
                BIT_RELAY = 1;
                if (is_button_pressed(AUTO_1_BUTTON)) {
                    MAX_COUNTER_AUTO_1 = brewing_counter;
                    WriteEEPROM(addressEEPROM_AUTO_1, MAX_COUNTER_AUTO_1);
                    mode = INIT;
                }
                break;
            case BREWING_0:
                BIT_RELAY = 1;
                if(brewing_counter > MAX_COUNTER_AUTO_0) mode = INIT;
                if (is_button_pressed(AUTO_0_BUTTON)) mode = INIT;

                break;
            case BREWING_1:
                BIT_RELAY = 1;
                if (brewing_counter > MAX_COUNTER_AUTO_1) mode = INIT;
                if (is_button_pressed(AUTO_1_BUTTON)) mode = INIT;

                break;
            case AUTO_CLEANING:
                if (flag_timer1) {
                    if (BIT_RELAY == 0) {
                        SetTimer1_ms(10000); //10s
                        BIT_RELAY = 1;
                    } else {
                        cleaning_counter--;
                        SetTimer1_ms(2000); //2s
                        BIT_RELAY = 0;
                    }
                }
                if (cleaning_counter == 0) mode = INIT;
                if (is_button_pressed(AUTO_CLEANING_BUTTON)) {
                    mode = INIT;
                }
                break;
            default:
                mode = INIT;
                break;
        }
        Delay_ms(3);
    }
    return;
}

void InitSystem(void) {
    CMCON = 0x07;

    TRIS_BUTTON = 0b00110100;
    PORT_BUTTON = 0xFF;

    TRISB = 0x01;
    PORTB = 0x00;
    
    brewing_counter = 0;
    cleaning_counter = CLEANING_TIMES;

    mode = INIT;

    OPTION_REGbits.nRBPU = 0;   //portB weak pullup
    OPTION_REGbits.INTEDG = 1;  //interrupt on rising edge

    INTCONbits.INTE = 1;        //enable external interrupt RB0
    
    MAX_COUNTER_AUTO_0 = ReadEEPROM(addressEEPROM_AUTO_0);
    MAX_COUNTER_AUTO_1 = ReadEEPROM(addressEEPROM_AUTO_1);
    RelayOn(0);

    init_timer1(TIMER1_TIME); //timer1 10ms   
    SetTimer1_ms(1000);

}

void Delay_ms(unsigned int delay) {
    unsigned int i, j;
    for (i = 0; i < delay; i++) {
        for (j = 0; j < 141; j++);
    }
}

void RelayOn(unsigned char flag) {
    if (flag == 0) BIT_RELAY = 0;
    else BIT_RELAY = 1;
}

unsigned char ReadEEPROM(unsigned char address) {
    EEADR = address;
    EECON1bits.RD = 1; //enable read
    return EEDATA;
}

void WriteEEPROM(unsigned char address, unsigned char data) {
    EEADR = address;
    EEDATA = data;
    EECON1bits.WREN = 1; //allow write cycles
    INTCONbits.GIE = 0; //disable interrupt
    EECON2 = 0x55; //Required sequence for write to internal EEPROM
    EECON2 = 0xAA; //Required sequence for write to internal EEPROM   
    EECON1bits.WR = 1; //enable write
    INTCONbits.GIE = 1; //enable interrupt

    while (PIR1bits.EEIF == 0);
    PIR1bits.EEIF = 0;
}