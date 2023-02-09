#include "timer.h"

unsigned int timer1_value = 0;
unsigned char flag_timer1 = 0;

unsigned int timer1_cnt = 0;
unsigned int time1_MUL = 1;
void init_timer1(unsigned int count){

    T1CONbits.TMR1ON = 0;
    timer1_value = 65535 - count;
    TMR1 = timer1_value;

    T1CONbits.TMR1CS = 0;           //internal clock = 4 Mhz / 4

    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1CKPS1 = 0;
    
    TMR1IF = 0;
    TMR1IE = 1;
    GIE = 1;
    PEIE = 1;
    T1CONbits.TMR1ON = 1;
}

void start_timer1(void)
{
    TMR1 = timer1_value;
	T1CONbits.TMR1ON = 1;
}

void stop_timer1(void)
{
	T1CONbits.TMR1ON = 0;
}
void timer1_isr(void)
{
	timer1_cnt ++;
	if (timer1_cnt >= time1_MUL)
	{
		timer1_cnt = 0;
		flag_timer1 = 1;
	}
    // Noi goi nhung ham doi hoi toc do nhanh va uu tien cao hon ham main
}

void SetTimer1_ms(int time)
{
	time1_MUL = time/10;
	timer1_cnt = 0;
	flag_timer1 = 0;
}