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
    alongLine(0, 0, 4000, 0);
    delay(200);
    turn(180,0);
    delay(200);
  }
  // step2  花滑
  if (c == 0x89)
  {
    getEncoder();
    tempangle = angle;
    delay(1000); 
    alongCurve(3600, 1, 90);
    delay(1000);
    alongCurve(3200, 1.2, 90);
    delay(1000);
    alongCurve(3200, 1.2, 90);
    delay(1000);
    alongCurve(3600, 1, 90);
    delay(1000);
    getEncoder();
    subangle = angle - tempangle;
    if(subangle>0&&subangle<90)
    {
      turn(subangle ,1);
      }
    else if(subangle<0&&subangle>-90)
    {
      turn(fabs(subangle),0);
      }
  }    

  // step3 花滑to冰壶
  if (c == 0x90)
  {
    turn(90, 0);
    delay(500);
    alongLine(0, 0, 2000, 0);
    delay(500);
    turn(180, 1);
  }
  // step4 冰壶
  if (c == 0x91)
  {
    alongLine(0, 2, 6000, 0);
  }
  // step5 冰壶to冰球
  if (c == 0x92)
  {
    turn(90, 0);
    delay(500);
    alongLine(0, 0, 7500, 0);
    delay(500);
    turn(120, 0);
  }
  // step6 冰球-car2从3到1
  if (c == 0x93)
  {
    alongLine(0, 0, 3600, 0);
    delay(500);
    turn(120, 0);
    delay(500);
  }
  // step7 冰球-car2从1到3
  if (c == 0x94)
  {
    alongLine(0, 0, 3600, 0);
    delay(500);
    turn(60, 1);
  }
  // step8 冰球-car2直行+射门
  if (c == 0x95)
  {
    alongLine(0, 0, 1500, 0);
    delay(500);
    turn(60, 1);
    alongLine(0, 0, 2000, 0);
  }
  // step9 冰球to颁奖
  if (c == 0x96)
  {
    turn(30, 1);
    delay(500);
    alongLine(0, 0, 4000, 0);
    delay(500);
    turn(180, 1);
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
