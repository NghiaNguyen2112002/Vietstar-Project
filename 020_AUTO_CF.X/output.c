#include "output.h"


void MTR_Set(unsigned char state){
    MOTOR_OUT_IO = state == 0 ? 0 : 1;
}