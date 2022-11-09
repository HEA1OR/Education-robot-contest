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
    Serial.begin(9600);
    delay(3000);
}
/*
======================== CAR1 ================================
*/
int nowlen = 0;
void loop(){
//    Serial.println("ok");
//    schedule();
//    turn(90, 0);
//   walk(50, 50);
    command_execute(0x89);
    command_execute(0x90);
    command_execute(0x91);
    command_execute(0x92);
    command_execute(0x93);
    command_execute(0x94);
    command_execute(0x95);
    command_execute(0x96);
    command_execute(0x97);

    
   
}
