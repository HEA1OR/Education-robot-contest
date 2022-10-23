#include "encoder&LED.h"
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
    //led_matrix_init();
    motorInit();
    //xbee_init();
    schedule_init();
    Serial.begin(9600);
    delay(3000);
}

int nowlen = 0;
void loop(){
//    delay(3000);
//    getEncoder();    
    Serial.println("ok");
//    schedule();
    command_execute(0x90);
    command_execute(0x91);
    command_execute(0x92);
    command_execute(0x93);
    command_execute(0x94);
    command_execute(0x95);
    command_execute(0x96);
//    turn(90,0);
//    walk(50,50);
//    turn(90, 1);
//    turn(4,0);
//    alongLine(0, 0, 3000);

//    getEncoder();
//    turn(270,0);
//     alongLine(0,0,5000, 1);
//    alongCurve(400, 0.2, 90, 3);
//    alongLine(500, 0);
//    delay(3000);
//    turn(180, 1);
//    delay(3000);
//    walk(50, 50);
//    delay(3000);
//    turn(90, 1);
//    getEncoder();
//    int lastlen = nowlen;
//    nowlen = sideLength;
//    Serial.println(lastlen - nowlen);
//    schedule();
    
    Serial.print("aangle:");
    Serial.println(angle);
    Serial.print("length: ");
    Serial.println(sideLength);
    Serial.println("");
    
}
