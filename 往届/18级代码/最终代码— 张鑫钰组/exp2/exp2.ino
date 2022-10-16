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


void loop()
{
  //alongLine(150);
 // turn(90,right);
  //delay(5000);
 // alongWall(100);
  //sendSignal('e');
  //sendSignal('K');

// sendSignal('K');
 // delay(5000);
// alongWall(150);
 schedule();

//   flash(6);

//  walk(0,0);    //标准速度
 
  //sendSignal('2');
  
 // alongWall(150);delay(5000);

/*
  //*************************行程**************************
//  delay(2000);   //1、启航
//  alongWall(145);  
//  
//  delay(500);     //2护航
//  turn(45,left);  
//  delay(500);
//  alongLine(25);
//  delay(500);
//  alongWall(60);
//
//  
//  standBy();  //3巡逻，1、3车绕周
//  delay(500);
//
//
//  delay(1200);      //4侦察
//   turn(90,right);
//  delay(100);
//  alongLine(78);
//  standBy();
//  
//  
//  delay(500);     //5补给
//  alongLine(68);   
//  delay(2400);
//  turn(90,right);
//  delay(200);
//  alongWall(40);
//  delay(500);
//  turn(90,right);
//  
//  delay(8000);  //6演习
//  alongLine(60);
//  delay(500);
//  turn(45,left);
//  delay(2000);
//  turn(90,right);
//  delay(2000);
//  turn(45,left);
//  
//  delay(500);    //7谢幕
//  alongWall(110);
//  delay(1000);
//  turn(90,right);
//  delay(3000);
//  alongWall(36);
//  delay(1000);
//  turn(90,right);
//  delay(2000);
//  alongLine(75);
//  delay(150000);
*/

 //*************************行程结束**************************


//schedule();

// alongLine(50);
// delay(1500);  
// alongWall(50);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              alongWall(200);
// turn(90,right);      
//  delay(500);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
//  turn(45,left);



/*
   alongLine(60); 
   delay(1000);

   turn(90,right);
    delay(1000);

   alongLine(60); 
   delay(1000);
   
   turn(90,right);
   delay(1000);

   alongLine(60); 
   delay(1000);
   
   turn(90,right);
   delay(1000);

   turn(90,right);
    delay(1000);
   
*/

}
