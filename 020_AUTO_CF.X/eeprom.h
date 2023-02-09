/* 
 * File:   eeprom.h
 * Author: DELL
 *
 * Created on January 29, 2023, 7:57 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include "main.h"
#include "global.h"

#define TIME_AUTO_ADDRESS_L         0x00
#define TIME_AUTO_ADDRESS_H         0x01

#define CUP_TOTAL_ADDRESS_L         0x02
#define CUP_TOTAL_ADDRESS_H         0x03

void EEP_SaveAutoTime(void);
void EEP_SaveCupTotal(void);

void EEP_ReadAutoTime(void);
void EEP_ReadCupTotal(void);


#endif	/* EEPROM_H */

