#include "led7seg.h"

//time scan each led is 2 ms
//RB:   7 6 5 4    3 2 1 0
//led:  0 f b a    g d e c
//5621BS

unsigned char LEDDisplay[11] = {0x08, 0x5E, 0x41, 0x42, 
                                0x16, 0x22, 0x20, 0x4E, 
                                0x00, 0x02, 0x77};

unsigned char LEDBuffer[2] = {1, 2};



void Display(unsigned char number){
    if(number >= 0 && number <= 10){
        PORTB = LEDDisplay[number];
    }
}

void LedEnable(unsigned char index){
    if(index == 0){
        PORTbits_en1 = 1;
        PORTbits_en2 = 0;    
    }
    else if(index == 1){
        PORTbits_en1 = 0;
        PORTbits_en2 = 1;    
    }
}

void UpdateLedBuffer(unsigned char time){
    if(time >= 0 && time <= 99){
        LEDBuffer[0] = time / 10;
        LEDBuffer[1] = time % 10;
    }
}
void UpdateLed(unsigned char index){
    LedEnable(index);
    Display( LEDBuffer[index] );
}

