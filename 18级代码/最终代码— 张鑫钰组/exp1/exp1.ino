// Visual Micro is in vMicro>General>Tutorial Mode
//
/*
    Name:       dancing.ino
    Created:  2018/10/7 11:11:00
    Author:     LiuYang
*/
// Define User Types below here or use a .h file
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
//  flash(5);
  schedule();
 
// sendSignal('S');
//standBy();

//delay(10000);
//  standBy();
//  delay(2000);
// turn(45,left);
// flash(3);
// delay(3000);
// standBy();
 // sendSignal('D');
 //standBy();

// delay(1000); 
//turn(135,left);
// alongWall(100);
 //delay(1000);   
 // turn(135,left);
 //standBy();

//  Serial.print(countLeft);
//   Serial.print("  ");
//  Serial.println(countRight);
  
// sendSignal('1');
//flash(3000);

//alongLine(150);delay(5000);
// alongWall(100);
// walk(105,91);
// delay(3000);

}
