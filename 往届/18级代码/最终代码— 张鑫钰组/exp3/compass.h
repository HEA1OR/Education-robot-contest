#ifndef _COMPASS_H
#define _COMPASS_H

#include <SPI.h>
#include "Wire.h"
#include "Servo.h"
#include "SoftwareSerial.h"
#include "Arduino.h"
#include "JY901.h"

//#define address 0x1E //0011110b, I2C 7bit address of HMC5883
//
//#define Xoffset -38
//#define Yoffset -502

void compassInit();
//void compassCalibration();
void get_angle(void);

#endif // !_COMPASS_H
