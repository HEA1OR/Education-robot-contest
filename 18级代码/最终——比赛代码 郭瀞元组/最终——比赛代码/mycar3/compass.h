#ifndef _COMPASS_H
#define _COMPASS_H

#include <SPI.h>  //用于网络通信的一个头文件库
#include "Wire.h" //用于i2C 和 spi  通信用的
#include "Servo.h" //舵机函数
#include "SoftwareSerial.h" //将其他数字引脚模拟为串口通信引脚
#include "Arduino.h"

//这块被注释掉的define是什么意思？没懂

//#define address 0x1E //0011110b, I2C 7bit address of HMC5883
//
//#define Xoffset -38
//#define Yoffset -502

void compassInit();

//void compassCalibration();

void get_angle(void);

#endif   // !_COMPASS_H
