/* 
 * File:   fsm.h
 * Author: DELL
 *
 * Created on December 11, 2022, 4:18 PM
 */

#ifndef FSM_H
#define	FSM_H

#include "main.h"
#include "button.h"
#include "lcd.h"
#include "global.h"
#include "output.h"
#include "eeprom.h"

enum OPERATION_MODE      {INIT, MANUAL, AUTO, ADJUST_TIME, INCREASE, DECREASE, START_AUTO, DELETE_ALL};
                            
               
void FSM_Init(void);
void FSM_ModeControl(void);
 

#endif	/* FSM_H */

