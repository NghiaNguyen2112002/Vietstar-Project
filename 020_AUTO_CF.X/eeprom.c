#include "eeprom.h"


//
//unsigned char EEP_Read(unsigned char address){
//    EEADRL = address;
//    
//    EECON1bits.EEPGD = 0;
//    EECON1bits.CFGS = 0;
//    EECON1bits.RD = 1; //enable read
//    
//    return EEDATL;
//}
//void EEP_Write(unsigned char address, unsigned char data){
//    EEADRL = address;
//    EEDATL = data;
//    
//    EECON1bits.CFGS = 0;
//    EECON1bits.EEPGD = 0;  
//    EECON1bits.WREN = 1;    //allow write cycles
//    
//    INTCONbits.GIE = 0;     //disable interrupt
//    EECON2=0x55; //Required sequence for write to internal EEPROM
//    EECON2=0xAA; //Required sequence for write to internal EEPROM   
//    EECON1bits.WR = 1;      //enable write
//    INTCONbits.GIE = 1;     //enable interrupt
//    
//    EECON1bits.WREN = 0;
//    while(PIR2bits.EEIF == 0);
//    PIR2bits.EEIF = 0;
//}


void EEP_SaveAutoTime(void){
    eeprom_write(TIME_AUTO_ADDRESS_L, _timeAuto);
    eeprom_write(TIME_AUTO_ADDRESS_H, _timeAuto >> 8);
}

void EEP_SaveCupTotal(void){
    eeprom_write(CUP_TOTAL_ADDRESS_L, _cupTotal);
    eeprom_write(CUP_TOTAL_ADDRESS_H, _cupTotal >> 8);
}

void EEP_ReadAutoTime(void){
    _timeAuto = eeprom_read(TIME_AUTO_ADDRESS_L) | eeprom_read(TIME_AUTO_ADDRESS_H) << 8;
    if(_timeAuto > MAX_TIME_AUTO) _timeAuto = MAX_TIME_AUTO;
}

void EEP_ReadCupTotal(void){
    _cupTotal = eeprom_read(CUP_TOTAL_ADDRESS_L) | eeprom_read(CUP_TOTAL_ADDRESS_H) << 8;
}
