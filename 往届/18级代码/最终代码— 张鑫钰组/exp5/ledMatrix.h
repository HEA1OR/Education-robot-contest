#ifndef _LEDMATRIX_H
#define _LEDMATRIX_H

#include "SoftwareSerial.h"
#include "Arduino.h"
#include "motor.h"

void ledMatrixInit();
void sendSignal(byte num);

#endif // !_LEDMATRIX_H
