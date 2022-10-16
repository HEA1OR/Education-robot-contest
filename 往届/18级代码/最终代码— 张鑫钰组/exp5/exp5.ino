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
 // alongLine(150); delay(5000);
//walk(99,120);
//turn(90,right);delay(1000);
 schedule();
//   digitalWrite(ledpin, HIGH);

//   alongWall(200);delay(5000);
//    turn(45,left);delay(2000);
//    turn(90,right);delay(1000);
//    alongLine(30);delay(500);
//    turn(180,left);delay(1000);
//    alongLine(30);delay(500);
//    turn(135,left);
//    delay(7000);
//   sendSignal('Y');
//   alongWall(160);delay(500);
//turn(90,right);delay(1500);
   //turn(90,right);delay(1000);
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

//D2
/*delay(3500);
turn(90,right);delay(500);
alongLine(90);
delay(10000);*/

//D3
/*delay(500);
turn(180,left);delay(500);
alongLine(25);delay(500);
turn(90,right);delay(500);
alongLine(42);delay(500);
turn(90,right);delay(500);
alongWall(50);delay(500);
turn(90,right),delay(500);
alongLine(19);*/

//D4
/*delay(2800);
alongLine(81);delay(500);
turn(90,left);delay(500);
alongLine(68);delay(500);
turn(90,right);delay(500);
alongWall(92);delay(500);
turn(90,right);delay(500);
alongWall(114);delay(500);
turn(90,right);delay(500);
alongLine(82);delay(500);
turn(180,right);
delay(100000);*/

//D5
/*delay(2500);
alongLine(77);delay(500);
turn(90,right);delay(500);
alongWall(40);delay(500);
turn(90,right);*/


//D6
/*delay(500);
alongLine(60);delay(500);
turn(45,left);delay(2000);
turn(90,left);delay(500);
alongLine(30);delay(500);
turn(90,left);delay(500);
alongLine(30);delay(500);
turn(135,left);
delay(8000);*/

//D7
//delay(500);
//alongWall(160);delay(500);
//turn(90,right);delay(7000);
//turn(90,right);delay(500);
//alongLine(90);delay(500);
//delay(20000);
/*delay(1000);
turn(90,right);*/






}
