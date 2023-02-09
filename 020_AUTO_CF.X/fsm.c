#include "fsm.h"


unsigned char index_lcd;
enum OPERATION_MODE mode;

unsigned char flagPressAdjust;

void FSM_Init(void){
    index_lcd = 0;
    mode = INIT;
    flagPressAdjust = 0;
}

void FSM_ModeControl(void){
    switch(mode){
        case INIT:               
            LcdPrintStringS(0, 0, MANUAL_SCREEN_0);
            LcdPrintStringS(1, 0, MANUAL_SCREEN_1);
//                "Vietstar  Coffee" 
//                "    _ MANUAL _  "
            MTR_Set(0);
            mode = MANUAL;
            break;
        case MANUAL:
            if(BTN_IsHeld(START_BUTTON)) MTR_Set(1);
            else MTR_Set(0);
            
            if(BTN_IsPressed(MODE_BUTTON)){
                LcdPrintStringS(0, 0, AUTO_SCREEN_0);
                LcdPrintStringS(1, 0, AUTO_SCREEN_1);
//                    "AUTO :         s"
//                    "CUP  :          "
                LcdPrintFloatS(0, 8, _timeAuto);
                LcdPrintNumS(1, 8, _cupTotal);
                MTR_Set(0);
                
                mode = AUTO;
            }
            break;
        case AUTO:
            if(BTN_IsHeld(START_BUTTON)) {
                LcdPrintStringS(0, 0, AUTO_START_SCREEN_0);
                LcdPrintStringS(1, 0, AUTO_START_SCREEN_1);
//                    " |            | "
//                    "     [STOP]     "
                _countAuto = _timeAuto;
                MTR_Set(1);
                
                mode = START_AUTO;
            }
            else if(BTN_IsPressed(MODE_BUTTON)){
                LcdPrintStringS(0, 0, MANUAL_SCREEN_0);
                LcdPrintStringS(1, 0, MANUAL_SCREEN_1);
    //                "Vietstar  Coffee" 
    //                "    _ MANUAL _  "
                MTR_Set(0);
                mode = MANUAL;
            }
            else if(BTN_IsPressed_s(MODE_BUTTON)){
                LcdPrintStringS(0, 0, ADJUST_TIME_SCREEN_0);
                LcdPrintStringS(1, 0, ADJUST_TIME_SCREEN_1);      
//                    "               s"
//                    "[+]   [OK]   [-]"
                LcdPrintFloatS(0, 8, _timeAuto);
                
                mode = ADJUST_TIME;
            }
            else if(BTN_IsPressed_s(DEC_BUTTON) && BTN_IsPressed_s(INC_BUTTON)){
                LcdPrintStringS(0, 0, DELETE_SCREEN_0);
                LcdPrintStringS(1, 0, DELETE_SCREEN_1);      
//                    " Delete All ?   "
//                    "[N]   [OK]   [N]"
                mode = DELETE_ALL;
            }
            break;
        case ADJUST_TIME:
            if(BTN_IsHeld(INC_BUTTON)) {
                flagPressAdjust = 0;
                mode = INCREASE;
            }
            else if(BTN_IsHeld(DEC_BUTTON)) {
                flagPressAdjust = 0;
                mode = DECREASE;
            }     
            else if(BTN_IsPressed(MODE_BUTTON)) {
                
//              save _timeAuto
                EEP_SaveAutoTime();
                
                LcdPrintStringS(0, 0, AUTO_SCREEN_0);
                LcdPrintStringS(1, 0, AUTO_SCREEN_1);
//                    "AUTO :         s"
//                    "CUP  :          "
                LcdPrintFloatS(0, 8, _timeAuto);
                LcdPrintNumS(1, 8, _cupTotal);
                MTR_Set(0);
                
                mode = AUTO;
            }
            break;
        case INCREASE:
            if(BTN_IsPressed_ms(INC_BUTTON, 500) && _counterDelay <= 0){
//              button is held in 500ms
                _counterDelay = 6;
                _timeAuto = _timeAuto + 100 > MAX_TIME_AUTO ? MAX_TIME_AUTO : _timeAuto + 100;
                LcdPrintFloatS(0, 8, _timeAuto);
                flagPressAdjust = 1;
            }
            else if(!BTN_IsHeld(INC_BUTTON)) { 
                if(flagPressAdjust == 0){
                _timeAuto = _timeAuto + 10 > MAX_TIME_AUTO ? MAX_TIME_AUTO : _timeAuto + 10;
                }
                LcdPrintFloatS(0, 8, _timeAuto);
                mode = ADJUST_TIME;
            }    
            break;
        case DECREASE:
            if(BTN_IsPressed_ms(DEC_BUTTON, 500) && _counterDelay <= 0){
//              button is held in 500ms
                _counterDelay = 6;
                _timeAuto = _timeAuto >= 100 ? _timeAuto - 100 : 0;
                LcdPrintFloatS(0, 8, _timeAuto);
                flagPressAdjust = 1;
            }
            else if(!BTN_IsHeld(DEC_BUTTON)) {
                if(flagPressAdjust == 0){
                    _timeAuto = _timeAuto >= 10 ? _timeAuto - 10 : 0;
                }
                LcdPrintFloatS(0, 8, _timeAuto);
                mode = ADJUST_TIME;
            }
            break;
        case START_AUTO:
//                        2 -> 14
            index_lcd = (_timeAuto - _countAuto) * 12 / _timeAuto + 2;
            LcdPrintCharS(0, index_lcd, 0xFF);
            
            if(_countAuto == 0) {
                _cupTotal++;
//              save _cupTotal
                EEP_SaveCupTotal();
            }
            
            if(_countAuto < 5 || BTN_IsPressed(MODE_BUTTON)){
                LcdPrintStringS(0, 0, AUTO_SCREEN_0);
                LcdPrintStringS(1, 0, AUTO_SCREEN_1);
//                       "AUTO :         s"
//                       "CUP  :          "
                LcdPrintFloatS(0, 8, _timeAuto);
                LcdPrintNumS(1, 8, _cupTotal);
                MTR_Set(0);
                
                mode = AUTO;    
            }
            break;
        case DELETE_ALL:
            if(BTN_IsPressed(DEC_BUTTON) || BTN_IsPressed(INC_BUTTON)){
                mode = INIT;
            }
            else if(BTN_IsPressed(MODE_BUTTON)){
                _timeAuto = _cupTotal = 0;
                
//              save _timeAuto _cupTotal
                EEP_SaveAutoTime();
                EEP_SaveCupTotal();
                        
                mode = INIT;
            }
            break;
        default:
            mode = INIT;
            break;
    }
}
