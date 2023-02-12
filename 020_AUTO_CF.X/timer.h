/* 
 * File:   timer.h
 * Author: DELL
 *
 * Created on October 11, 2022, 7:30 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#include "main.h"

extern unsigned char flag_timer1; 

void TMR0_Init(unsigned char count);
void TMR1_Init(unsigned int count);

void TMR1_Start(void);

void TMR1_Stop(void);

void TMR1_Isr(void);

void TMR1_SetTime_ms(unsigned int time);
#endif	/* TIMER_H */

