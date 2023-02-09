/* 
 * File:   button.h
 * Author: DELL
 *
 * Created on November 11, 2022, 9:28 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "main.h"

#define NO_OF_BUTTONS                       3
#define PORT_BUTTON                         PORTA

#define DURATION_FOR_AUTO_INCREASING        200   //2s

#define BUTTON_IS_PRESSED                   0
#define BUTTON_IS_RELEASED                  1

void InitButtonReading();
void button_reading(void);

unsigned char is_button_held(unsigned char index);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_s(unsigned char index);

#endif	/* BUTTON_H */

