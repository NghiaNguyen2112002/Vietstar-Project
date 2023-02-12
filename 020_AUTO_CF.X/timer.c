#include "timer.h"

unsigned char flag_timer1 = 0;

unsigned int timer1_value = 0;
unsigned int timer1_cnt = 0;
unsigned int timer1_MUL = 1;


void TMR1_Init(unsigned int count){

    T1CONbits.TMR1ON = 0;
    timer1_value = 65535 - count;
    TMR1 = timer1_value;

    T1CONbits.TMR1CS = 0;           //internal clock = 4 Mhz / 4
    
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1CKPS1 = 0;
    
    TMR1IF = 0;
    TMR1IE = 1;
    T1CONbits.TMR1ON = 1;
}

void TMR1_Start(void)
{
    TMR1 = timer1_value;
	T1CONbits.TMR1ON = 1;
}

void TMR1_Stop(void)
{
	T1CONbits.TMR1ON = 0;
}


void TMR1_Isr(void)
{
	timer1_cnt ++;
	if (timer1_cnt >= timer1_MUL)
	{
		timer1_cnt = 0;
		flag_timer1 = 1;
	}
    
    // Noi goi nhung ham doi hoi toc do nhanh va uu tien cao hon ham main
    BTN_Reading();

}

void TMR1_SetTime_ms(unsigned int time)
{
	timer1_MUL = time/10;
	timer1_cnt = 0;
	flag_timer1 = 0;
}