#include "lcd.h"

int current_row, current_col;

unsigned char LcdScreen[2][16] = {
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

void lcd_delay(unsigned char time) 
{
    int i,j;
    for(i=0;i<time;i++)
        for(j=0;j<1;j++);
}

void v_timer0(unsigned long time)
{
    int i,j;
    for(i=0;i<time;i++)
        for(j=0;j<160;j++);
}

unsigned long lcd_power_of(int A, int x) 
{
    char i;
    unsigned long temp = 1;
    for(i = 0; i < x; i++)
            temp *= A;
    return temp;
}

void lcd_send_command(unsigned char cmd)	//Sends Command to LCD
{
	LCD_PORT    &= 0x0f;
	LCD_PORT    |= (cmd&0xf0);
	LCD_PORT    |= (1 << LCD_E);
	v_timer0(1);

	LCD_PORT    &=~ (1 <<LCD_E);
	v_timer0(1);

	LCD_PORT    &= 0x0f;
	LCD_PORT    |= (cmd<<4);
	LCD_PORT    |= (1 <<LCD_E);
	v_timer0(1);

	LCD_PORT    &=~ (1 <<LCD_E);
	v_timer0(1);
}

void init_lcd(void) 
{
    LCD_DDR  = 0x00;
    v_timer0(25);//Wait more than 15ms after Vcc = 4.5V
    //turn on enable pin
    LCD_PORT&=0x0f;
	LCD_PORT&=0xf8;

    //---------one------
    LCD_DATA_OUT(0x03<<4)
	EN(SET);
    v_timer0(1);
	EN(CLR);
    v_timer0(1);

    //---------two------
    LCD_DATA_OUT(0x03<<4)
	EN(SET);
    v_timer0(1);
	EN(CLR);
    v_timer0(1);

        //---------three------
    LCD_DATA_OUT(0x03<<4)
	EN(SET);
    v_timer0(1);
	EN(CLR);
    v_timer0(1);

        //---------four------
    LCD_DATA_OUT(0x02<<4)
	EN(SET);
    v_timer0(1);
	EN(CLR);
    v_timer0(1);
        //--------4 bit--dual line---------------
	lcd_send_command(0x28);
        //-----increment address, invisible cursor shift------
	lcd_send_command(0x0c);	
}

void lcd_write_4bits(unsigned char dat) 
{	
	//RW(WRITE);
    LCD_DATA_OUT(dat);
	EN(SET);
    lcd_delay(1);
	EN(CLR);
    lcd_delay(1);
}
void lcd_write_cmd(unsigned char cmd)
{
	RS(CMD);
    lcd_delay(1);
	lcd_write_4bits(cmd);
	lcd_write_4bits(cmd<<4);
}

void lcd_write_data(unsigned char data) 
{
	RS(DAT);
    lcd_delay(1);
	lcd_write_4bits(data);
    lcd_write_4bits(data<<4);
    RS(CMD);
}

void lcd_set_cursor (unsigned char row, unsigned char column)
{
    unsigned char address;

    switch(row)
    {
       case 0: address = 0x80; break; //Starting address of 1st line
       case 1: address = 0xC0; break; //Starting address of 2nd line
    }
    address = address + column;
    lcd_write_cmd(address);               /* Set DDRAM address counter to 0     */											  
}

//void lcd_clear (void)
//{
//    lcd_write_cmd(0x01);                  /* Display clear                      */
//    lcd_set_cursor (0, 0);
//}

void lcd_print_char (char c)
{ 
    lcd_write_data (c);
}

void DisplayLcdScreen(void)
{
     unsigned char i;
    lcd_set_cursor (0,0);
    for (i = 0; i<16; i++)
        lcd_print_char(LcdScreen[0][i]);
    lcd_set_cursor (1,0);
    for (i = 0; i<16; i++)
        lcd_print_char(LcdScreen[1][i]);
}

void lcd_print_charS(unsigned char c)
{
    LcdScreen[current_row][ current_col] = c;
    current_col ++;
}

void LcdPrintCharS(unsigned char x, unsigned char y, unsigned char c)
{
    current_row = x%2;
    current_col = y%16;
    LcdScreen[current_row][ current_col] = c;
}

void LcdPrintFloatS(unsigned char x, unsigned char y, unsigned int num)
{
    unsigned char integerPart, decimalPlaces;
    current_row = x%2;
    current_col = y%16;

    integerPart = num / 100;
    decimalPlaces = (num % 100 ) / 10;
           
    if(integerPart >= 10) lcd_print_charS(integerPart / 10 + '0');
    
    lcd_print_charS(integerPart % 10 + '0');
    lcd_print_charS('.');
    lcd_print_charS(decimalPlaces + '0');
    lcd_print_charS(' ');
}


void LcdPrintNumS(unsigned char x, unsigned char y, unsigned int num)
{
    char num_flag = 0;
    char i;
    current_row = x%2;
    current_col = y%16;
    
    if(num == 0){
        lcd_print_charS('0');
        return;
    }
    for(i = 10; i > 0; i--) 
    {
        if((num / lcd_power_of(10, i-1)) != 0) 
        {
            num_flag = 1;
            lcd_print_charS(num/lcd_power_of(10, i-1) + '0');
        }
        else 
        {
            if(num_flag != 0)
                lcd_print_charS('0');
        }
        num %= lcd_power_of(10, i-1);
    }
}

void LcdPrintStringS(unsigned char x, unsigned char y, const unsigned char *string)
{
    current_row = x%2;
    current_col = y%16;
    while (*string)  {
        lcd_print_charS (*string++);
    }
}
