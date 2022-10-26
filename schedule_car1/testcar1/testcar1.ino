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
//    led_matrix_init();
    motorInit();
//    xbee_init();
    schedule_init();
    Serial.begin(9600);
    delay(3000);
}

int nowlen = 0;
void loop(){
//    delay(3000);
    Serial.println("ok");
    walk(50, 50);
    
//    turn(90,1);
//    alongLine(0,0,5000,1);   
/*    command_execute(0x90);
    command_execute(0x91);
    command_execute(0x92);
    command_execute(0x93);
    command_execute(0x94);
    command_execute(0x95);
    command_execute(0x96);*/
//    alongLine(0,0,5000);
//    turn(90,0);
//    alongLine(0,0,5000);
//    getEncoder();
//    alongCurve(400, 2);
//    delay(3000);
//    int lastlen = nowlen;
//    nowlen = sideLength;
//    Serial.println(lastlen - nowlen);
//    schedule();
//    Serial.print("tempangle:");
//    Serial.println(angle);
//    Serial.print("templength: ");
//    Serial.println(sideLength);
//    Serial.println("");
    
}
