/* 
 * File:   led7seg.h
 * Author: DELL
 *
 * Created on October 11, 2022, 5:13 PM
 */

#ifndef LED7SEG_H
#define	LED7SEG_H

#include <pic16f628a.h>
#include "main.h"

#define PORTbits_en1        PORTAbits.RA0
#define PORTbits_en2        PORTAbits.RA7

void Display(unsigned char number);
void LedEnable(unsigned char index);
void UpdateLedBuffer(unsigned char time);
void UpdateLed(unsigned char index);


#endif	/* LED7SEG_H */

