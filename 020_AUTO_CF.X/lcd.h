/* 
 * File:   lcd.h
 * Author: DELL
 *
 * Created on December 9, 2022, 11:19 PM
 */

#ifndef LCD_H
#define	LCD_H

#include "main.h"

#define LCD_RS			2 		//define MCU pin connected to LCD RS
//#define LCD_RW			 	//define MCU pin connected to LCD R/W
#define LCD_E			3		//define MCU pin connected to LCD E
#define LCD_D4			4		//define MCU pin connected to LCD D4
#define LCD_D5			5		//define MCU pin connected to LCD D5
#define LCD_D6			6		//define MCU pin connected to LCD D6
#define LCD_D7			7		//define MCU pin connected to LCD D7

#define LCD_LINE0		0x00
#define LCD_LINE1		0x40


#define SET             1
#define CLR             0
#define DAT             1       // data mode
#define CMD             0       // command mode
#define READ            1       // read mode
#define WRITE           0       // write mode


#define LCD_PORT        PORTC
#define LCD_DDR         TRISC

//4_bit MSB code
#define RS(x)			( (x) ? ( LCD_PORT |= (1<<LCD_RS) ) : ( LCD_PORT &= ~(1<<LCD_RS) ) )
#define EN(x)			( (x) ? ( LCD_PORT |= (1<<LCD_E) ) : ( LCD_PORT &= ~(1<<LCD_E) ) )

#define LCD_DATA_OUT(x)         LCD_PORT &= 0x0F; LCD_PORT |= (x);
#define LCD_DATA_IN             LCD_PORT & 0x0F;
#define LCD_DIR_IN              LCD_PORT |= 0x0F;


void init_lcd(void); 
//void lcd_clear (void);
void DisplayLcdScreen(void);
void LcdPrintCharS(unsigned char x, unsigned char y, unsigned char c);
void LcdPrintFloatS(unsigned char x, unsigned char y, unsigned int num);
void LcdPrintNumS(unsigned char x, unsigned char y, unsigned int num);

void LcdPrintStringS(unsigned char x, unsigned char y, const unsigned char *string);




#endif	/* LCD_H */

