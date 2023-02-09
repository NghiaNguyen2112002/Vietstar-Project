/* 
 * File:   output.h
 * Author: DELL
 *
 * Created on January 1, 2023, 8:57 PM
 */

#ifndef OUTPUT_H
#define	OUTPUT_H

#include "main.h"

#define MOTOR_OUT_IO                   PORTAbits.RA5

void MTR_Set(unsigned char state);

#endif	/* OUTPUT_H */

