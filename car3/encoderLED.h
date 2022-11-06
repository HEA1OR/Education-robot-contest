#ifndef _ENCODER_H
#define _ENCODER_H
#include <SPI.h>

void encoderLEDInit();    // 初始化
void getEncoder();        // 更新左右轮速度变量
void setLightMode(int);   // 指定nano板上LED的模式（译码法）
char SPI_SlaveReceive();  
int receive_data();
void getAngle();

#endif  
