#include "schedule.h"
#include "encoderLED.h"

extern float angle;
volatile float count = 0;
float delta;
float initAngle_, subangle;
int command = 0;

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
  pinMode(mpin, OUTPUT);
  digitalWrite(mpin, LOW);
  close_flash();
  //  open_flash('A');
  getEncoder();

  delta = angle - 180;
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
// car1
void command_execute(byte c)
{

  //    Serial.print("c: ");
  //    Serial.println(c);
  // step1  入场
  if (c == 0x88)
  {
    setLightMode(1);
    open_flash('A');
    open_flash('A');
    open_flash('A');
    alongLine(0, 0, 4000, 0);
    delay(200);
    //open_flash('A');
    //turn(180, 1);
    //delay(200);
    getEncoder();
    initAngle_ = angle;
  }
  // step2  花滑
  if (c == 0x89)
  {
    setLightMode(3);
    open_flash('L');
    open_flash('L');
    open_flash('L');
    alongLine(0, 0, 4000, 0);
    delay(200);
    open_flash('A');
    open_flash('A');
    open_flash('A');
    open_flash('A');
    for (int i=1;i<=12;i++)
    {
      turn(89.5, 0);
      delay(600);
    }
    /*
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    alongLine(0, 0, 11000, 0);
    delay(200);
    open_flash('A');
    turn(91, 0);
    delay(200);
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('A');
    alongLine(0, 0, 9000, 0);
    delay(200);
    open_flash('A');
    turn(88, 0);
    delay(200);
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    alongLine(0, 0, 11000, 0);
     delay(200);
     open_flash('A');
     turn(88, 0);
     delay(200);
     open_flash('L');
     open_flash('L');
     alongLine(0, 0, 3000, 0);
     delay(500);*/
     getEncoder();
     subangle = angle - initAngle_;
     if (subangle < -90)
       subangle += 360;
     else if (subangle > 90)
       subangle -= 360;
     if (subangle > 1)
     {
       turn(subangle, 1);
      }
    else if(subangle<-1)
    {
      turn(fabs(subangle),0);
    }
    /*
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    */
  }

  // step3 花滑to冰壶
  if (c == 0x90)
  {
    setLightMode(1);
    open_flash('A');
    turn(90, 0);
    open_flash('L');
    delay(200);
    alongLine(0, 0, 800, 0);
    delay(200);
    turn(90, 0);
    delay(200);
    alongLine(0, 0, 3000, 0);
    delay(200);
    turn(88, 0);
    delay(200);
    open_flash('C');
    /*
    alongLine(0, 0, 2200, 0);
    */
  }
  // step4 冰壶
  if (c == 0x91)
  {
    setLightMode(0);
    open_flash('C');
    open_flash('C');
    open_flash('C');
    alongLine(0, 0, 3300, 0);
    setLightMode(1);
  }
  // step5 冰壶to冰球
  if (c == 0x92)
  {
    setLightMode(1);
    open_flash('A');
    turn(90, 1);
    delay(200);
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 4000, 0);
    delay(200);
    open_flash('A');
    turn(90, 1);
    delay(200);
    open_flash('G');
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 2200, 0);
    delay(200);
    open_flash('A');
    open_flash('A');
    turn(180, 1);
  }
  // step6 冰球-car1接球
  if (c == 0x93)
  {
    open_flash('M');
    setLightMode(0);
    delay(5000);    // 等球跑一会
    open_flash('M');
    open_flash('M');
    alongLine(0, 0, 2000, 0);
    delay(1600);
    open_flash('I');
    open_flash('I');
    open_flash('M');
    turn(60, 0);
  }
  // step7 冰球-car1不动
  if (c == 0x94)
  {
    delay(1000);
  }
  // step8 冰球-car1不动
  if (c == 0x95)
  {
    delay(1000);
  }
  // step9 冰球to颁奖
  if (c == 0x96)
  {
    setLightMode(6);
    open_flash('A');
    open_flash('A');
    turn(120, 0);
    delay(200);
    open_flash('H');
    open_flash('H');
    alongLine(0, 0, 2300, 0);
    delay(200);
    open_flash('A');
    turn(90, 1);
  }
  /*if (c == 0x95)
    {
    open_flash('A');
    }*/
  // step10 颁奖
  if (c == 0x97)
  {
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('A');
    setLightMode(6);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
  }

}
