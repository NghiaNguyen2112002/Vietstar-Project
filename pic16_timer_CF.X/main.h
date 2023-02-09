/* 
 * File:   main.h
 * Author: DELL
 *
 * Created on October 11, 2022, 3:28 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include <pic16f628a.h>
#include "led7seg.h"
#include "timer.h"
#include "button.h"

#define     TIMER1_TIME         10000  //10ms

#define     CLEANING_TIMES      10      //10 times

#define     UP                  0
#define     DOWN                1
#define     RUN                 2

#define     MAX_BUTTON          3
#define     TRIS_BUTTON         TRISA
#define     PORT_BUTTON         PORTA

#define     TRIS_LED            TRISB
#define     PORT_LED            PORTB

#define     BIT_RELAY           PORTAbits.RA3
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ      4000000


#endif	/* MAIN_H */

