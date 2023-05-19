#include "schedule.h"
#include "encoderLED.h"

extern float angle;
volatile float count = 0;
float delta;
float tempangle;
float subangle;
float initAngle_;

void schedule_init()
{
//  encoderInit();
//  motorInit();
//  ultrasonic_init();
//  compassInit();
//  xbee_init();
 led_matrix_init();
  pinMode(screwPin, OUTPUT);
//  digitalWrite(ledpin, LOW); 
  close_flash();
//  open_flash('A');
  getEncoder();
  
  delta=angle-180;
}

//void flash(int delayTime, int times)
//{
//  int i;
//  for (i = 0; i < times; i++)
//  {
//    digitalWrite(ledpin, HIGH);
//    Serial.println("high");
//    delay(delayTime);
//    digitalWrite(ledpin, LOW);
//    Serial.println("Low");
//    delay(delayTime);  
//  }
//}
void schedule()
{
  byte c = getCommand();
  command_execute(c);
}
// car2
void command_execute(byte c)
{
//    Serial.print("c: ");
//    Serial.println(c);
  // step1  入场
  if (c == 0x88)
  {
    alongLine(0, 0, 4200, 0);
    delay(200);
  }
  // step2  花滑
  if (c == 0x89)
  {
    getEncoder();
    tempangle = angle;
    turn(180,0);
    delay(200);
    //delay(1400); 
    alongCurve(3600, 1, 90);
    delay(1000);
    alongCurve(3200, 1.2, 90);
    delay(1000);
    alongCurve(3200, 1.2, 90);
    delay(1000);
    alongCurve(3600, 1, 90);
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
    getEncoder();
    tempangle = angle;
    delay(200);
    turn(90, 1);
    delay(200);
    turn(90, 1);
    delay(200);
    turn(90, 1);
    delay(200);
    turn(90, 1);
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
  }    

  // step3 花滑to冰壶
  if (c == 0x90)
  {
    turn(90, 0);
    delay(200);
    alongLine(0, 0, 800, 0);
    delay(200);
    turn(90, 1);
    delay(200);
    alongLine(0, 0, 800, 0);
    delay(200);
    turn(90, 1);
    delay(200);
  }
  // step4 冰壶
  if (c == 0x91)
  {
    alongLine(0, 0, 6300, 0);
    delay(200);
  }
  // step5 冰壶to冰球
  if (c == 0x92)
  {
    turn(90, 0);
    delay(2500);
    alongLine(0, 0, 4000, 0);
    delay(200);
    turn(90, 0);
    delay(200);
    alongLine(0, 0, 4100, 0);
    delay(200);
    turn(90, 0);
    delay(200);
  }
  // step6 冰球-car2从3到1
  if (c == 0x93)
  {
    alongLine(0, 0, 7500, 0);
    delay(200);
    turn(165, 0);
    delay(200);
  }
  // step7 冰球-car2从1到3
  if (c == 0x94)
  {
    alongLine(0, 0, 6400, 0);
    delay(200);
    turn(70, 1);
    delay(200);
  }
  // step8 冰球-car2直行+射门
  if (c == 0x95)
  {
    alongLine(0, 0, 2000, 0);
    delay(200);
    turn(45, 1);
    delay(200);
    alongLine(0, 0, 3800, 0);
    delay(200);
  }
  // step9 冰球to颁奖
  if (c == 0x96)
  {
    turn(40, 1);
    delay(200);
    alongLine(0, 0, 4000, 0);
    delay(200);
    turn(180, 1);
    delay(200);
  }
  /*if (c == 0x95)
    {
    open_flash('A');
    }*/
  // step10 颁奖
  if (c == 0x97)
  {
    turn(180, 1);
    delay(500);
    turn(180, 1);
    delay(500);
    turn(180, 1);
    delay(500);
    turn(180, 1);
    delay(500);
    turn(180, 1);
    delay(500);
    turn(180, 1);
    delay(500);
    turn(180, 1);
    delay(500);
    turn(180, 1);
    delay(500);
  }
}
