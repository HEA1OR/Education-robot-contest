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
    led_matrix_init();
    motorInit();
    xbee_init();
    schedule_init();
    Serial.begin(9600);
    Serial.println("start");
    delay(3000);
}

int nowlen = 0;
void loop(){
//    schedule();
      turn(90, 1);
      turn(90, 1);
      turn(90, 0);
      turn(90, 0);
      delay(5000);
//    delay(3000);
//    Serial.println("ok");
//    alongLine(500, 0);
//    alongCurve(400, 2);
//    delay(3000);
//    turn(180, 1);
//    delay(3000);
//    walk(50, 0);
//    delay(3000);
//    turn(90, 1);
//    getEncoder();
//    int lastlen = nowlen;
//    nowlen = sideLength;
//    Serial.println(lastlen - nowlen);
//    Serial.print("aangle:");
//    Serial.println(angle);
//    Serial.print("length: ");
//    Serial.println(sideLength);
//    Serial.println("");
    
}
