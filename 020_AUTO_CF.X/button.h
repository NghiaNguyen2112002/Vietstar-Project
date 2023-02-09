/* 
 * File:   button.h
 * Author: DELL
 *
 * Created on November 11, 2022, 9:28 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "main.h"

#define NO_OF_BUTTONS                       4

#define TRIS_BUTTON                         TRISA
#define PORT_BUTTON                         PORTA

#define DURATION_FOR_AUTO_INCREASING        200   //2s

#define BUTTON_IS_PRESSED                   0
#define BUTTON_IS_RELEASED                  1

#define INC_BUTTON                          0
#define MODE_BUTTON                         1
#define DEC_BUTTON                          2
#define START_BUTTON                        3


void BTN_Init(void);
void BTN_Reading(void);

unsigned char BTN_IsHeld(unsigned char index);
unsigned char BTN_IsPressed(unsigned char index);
unsigned char BTN_IsPressed_s(unsigned char index);
unsigned char BTN_IsPressed_ms(unsigned char index, unsigned int milisec);

#endif	/* BUTTON_H */

