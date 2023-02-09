#include "button.h"

//RA        0       1           2           3          
//          inc     mode        dec         START
unsigned char   buttonInputMask[NO_OF_BUTTONS] = {0x01, 0x02, 0x04, 0x08};

static unsigned char buttonBuffer[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};

static unsigned char debounceButtonBuffer1[NO_OF_BUTTONS];
static unsigned char debounceButtonBuffer2[NO_OF_BUTTONS];

static unsigned char flagForButtonPress[NO_OF_BUTTONS];
static unsigned char flagForButtonPress_s[NO_OF_BUTTONS];
static unsigned int counterForButtonPress[NO_OF_BUTTONS];


void BTN_Init(void){
//    select digital input
    ANSA0 = 0;
    ANSA1 = 0;
    ANSA2 = 0;
    TRIS_BUTTON = 0x0F;
    PORT_BUTTON = 0xFF;
}

///reading invoked every 10ms
void BTN_Reading(void){
    unsigned char i;
    for(i = 0; i < NO_OF_BUTTONS; i++){
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = PORT_BUTTON & buttonInputMask[i];
        
        if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i]){
            buttonBuffer[i] = debounceButtonBuffer1[i];
            if(buttonBuffer[i] == BUTTON_IS_PRESSED){
                if(counterForButtonPress[i] < DURATION_FOR_AUTO_INCREASING){
                    counterForButtonPress[i]++;
                }
                else flagForButtonPress_s[i] = 1;
            }
            else{
//              releasing button after press => pressed flag = 1
                flagForButtonPress[i] = counterForButtonPress[i] && (!flagForButtonPress_s[i]);
                counterForButtonPress[i] = 0;
                flagForButtonPress_s[i] = 0;
            }
        }
    }
}



unsigned char BTN_IsHeld(unsigned char index){
    if(index >= NO_OF_BUTTONS) return 0;
    
    return counterForButtonPress[index] > 0;
}

unsigned char BTN_IsPressed(unsigned char index){
    unsigned char result = flagForButtonPress[index];
    if(index >= NO_OF_BUTTONS) return 0;
    
    flagForButtonPress[index] = 0;
    return result;
}

unsigned char BTN_IsPressed_s(unsigned char index){
    if(index >= NO_OF_BUTTONS) return 0;
    return flagForButtonPress_s[index]; 
}

unsigned char BTN_IsPressed_ms(unsigned char index, unsigned int milisec){
    if(index >= NO_OF_BUTTONS) return 0;
    return counterForButtonPress[index] > milisec / 10;
            
}

