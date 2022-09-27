// Visual Micro is in vMicro>General>Tutorial Mode
//
/*
    Name:       dancing.ino
    Created:  2018/10/7 11:11:00
    Author:     LiuYang
*/

// Define User Types below here or use a .h file
//

//E2

#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>
#include "schedule.h"
#include "xbee.h"

extern Servo motorL, motorR;
extern int countLeft, countRight;

//PIN
//jy61 - uno:
//TX     RXD
//VCC    5V//GND    GND
//
//uno - nano:
//D10   10
//D11   11
//D12   12
//D13   13
//
//nano:
//right motor   8
//left motor    7
//right encoder 3
//left encoder  2
void setup()
{
  scheduleInit();
  Serial.begin(9600);

}

// Add the main program code into the continuous loop() function
void loop()
{
 // alongWall(120);
 // delay(5000);
//walk(100,100);

 schedule();

 //flash(3);
 
        //digitalWrite(ledpin, HIGH);
//  walk(100,100);
//  Serial.print(countLeft);
//   Serial.print("  ");
//  Serial.println(countRight);
 //   sendSignal('c');
 
  //turn(90,left);
//    alongWall(150);delay(5000);
//    turn(45,left);delay(2000);
//    turn(180,left);delay(500);
//    alongLine(150);delay(5000);
//    turn(90,left);delay(500);
//    alongLine(30);delay(500);
//    turn(135,left);
//    delay(700);
//   sendSignal('Y');
//   alongWall(160);delay(500);
//   turn(90,right);delay(1500);
//   turn(180,right);delay(500);
//   alongLine(85);delay(500);
//
///*sendSignal('X');
//    alongWall(60);delay(500);
//    turn(45,left);delay(2000);
//    turn(90,left);delay(500);
//    alongLine(30);delay(500);
//    turn(90,left);delay(500);
//    alongLine(30);delay(500);
//    turn(135,left);
//    delay(1000);
//    sendSignal('Y');
//   alongWall(160);delay(500);
//   turn(90,right);delay(1500);
//   turn(90,right);delay(1300);
//   alongLine(95);delay(500);
//   delay(10000);*/
//D1
/*delay(8500);
turn(90,left);
delay(400);
alongLine(60);
delay(50);
turn(90,right);
delay(50);
alongWall(130);
*/




}
