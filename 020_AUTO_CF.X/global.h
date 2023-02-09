/* 
 * File:   global.h
 * Author: DELL
 *
 * Created on December 11, 2022, 4:32 PM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H
//#include <stdio.h>
#include "main.h"

#define MANUAL_SCREEN_0                 "Vietstar  Coffee"
#define MANUAL_SCREEN_1                 "    _ MANUAL _  "

#define AUTO_SCREEN_0                   "AUTO :         s"
#define AUTO_SCREEN_1                   "CUP  :          "

#define AUTO_START_SCREEN_0             " |            | "
#define AUTO_START_SCREEN_1             "     [STOP]     "

#define ADJUST_TIME_SCREEN_0            "               s"
#define ADJUST_TIME_SCREEN_1            "[+]   [OK]   [-]"
    
#define DELETE_SCREEN_0                 " Delete All ?   "
#define DELETE_SCREEN_1                 "[N]   [OK]   [N]"

#define MAX_TIME_AUTO                   9900        //99s
extern unsigned int _timeAuto;
extern unsigned int _countAuto;

extern char _counterDelay;
extern unsigned int _cupTotal;



#endif	/* GLOBAL_H */

