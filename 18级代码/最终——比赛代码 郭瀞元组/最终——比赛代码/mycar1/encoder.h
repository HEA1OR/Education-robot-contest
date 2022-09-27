

#ifndef _ENCODER_H
#define _ENCODER_H

#include "Arduino.h"
#define left_round 26              //  26
#define right_round 26            //  26
#define EPS 1e-14


//这里声名的三个函数会被声名在encoder.cpp中

void encoderInit();
void blinkLeft();     
void blinkRight();
#endif   
