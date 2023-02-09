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


void init_timer1(unsigned int count);

void start_timer1(void);

void stop_timer1(void);
void timer1_isr(void);

void SetTimer1_ms(int time);
#endif	/* TIMER_H */

