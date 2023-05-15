#include "encoderLED.h"
#include "Arduino.h"
#include "led_matrix.h"
#include "motor.h"
#include "xbee.h"
#include "schedule.h"

// 用到的全局变量
extern float angle;
extern long int sideLength;
//extern float leftLength, rightLength;
 
void setup(){
    encoderLEDInit();
    led_matrix_init();
    motorInit();
    xbee_init();
    schedule_init();
    Serial.begin(9600);    delay(3000);
}
/*
======================== CAR2 ================================
*/
int nowlen = 0;
void loop(){
//    alongLine(0, 0, 5000, 0);
//    turn(90,0);
    schedule();
  // walk(50, 50);
//    setLightMode(7);
//    delay(5000);
//    setLightMode(0);
/*
    float subangle, tempangle;
    getEncoder();
    tempangle = angle;
    turn(30, 1);
    delay(200);
    getEncoder();
    subangle = angle - tempangle;
    if (subangle < -90)
        subangle += 360;
    else if (subangle > 90)
        subangle -= 360;
    if(subangle>0.4)
    {
      turn(subangle ,1);
      }
    else if(subangle<-0.4)
    {
      turn(fabs(subangle),0);
    }
*/
/*
    command_execute(0x88);
    command_execute(0x89);
    command_execute(0x90);
    command_execute(0x91);
    command_execute(0x92);
    command_execute(0x93);
    command_execute(0x94);
    command_execute(0x95);
    command_execute(0x96); 
    command_execute(0x97);
    */
}
