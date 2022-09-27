#pragma once
#ifndef _ENCODER_H
#define _ENCODER_H

#include "Arduino.h"
#define left_round 26
#define right_round 26
#define EPS 1e-14


void encoderInit();
void blinkLeft();
void blinkRight();
#endif // !_ENCODER_H
