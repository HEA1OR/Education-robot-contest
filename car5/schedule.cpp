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
  initAngle_ = angle;
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
    delay(500);
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
      turn(89.6, 0);
      delay(200);
    }
    /*
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
    }*/
    /*
    setLightMode(3);
    open_flash('L');
    open_flash('L');
    open_flash('L');
    alongLine(0, 0, 4500, 0);
    delay(500);
    open_flash('A');
    turn(89.5, 0);
    delay(500);
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
    delay(500);
    open_flash('A');
    turn(89.5, 0);
    delay(500);
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('L');
    open_flash('A');
    alongLine(0, 0, 9000, 0);
    delay(500);
    open_flash('A');
    turn(89.5, 0);
    delay(500);
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
    delay(500);
    open_flash('A');
    turn(92, 0);
    delay(500);
    open_flash('L');
    open_flash('L');
    open_flash('A');
    alongLine(0, 0, 3500, 0);
    delay(500);
    */
    /*
    turn(180, 1);
    delay(500);
    turn(180, 1);
    delay(500);
    turn(180, 1);
    delay(500);
    turn(180, 1);
    */
  }

  // step3 花滑to冰壶
  if (c == 0x90)
  {/*
    turn(180, 1);
    delay(200);
    alongLine(0, 0, 1200, 0);
    delay(200);
    turn(45, 0);
    delay(200);
    */
    setLightMode(4);
    open_flash('A');
    open_flash('K');
    turn(180, 1);
    delay(200);
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 5000, 0);
    delay(200);
    open_flash('A');
    open_flash('K');
    turn(45, 0);
    delay(500);
    //alongLine(0, 0, 1000, 0);
    //delay(200);
  }
  // step4 冰壶
  if (c == 0x91)
  {
    setLightMode(4);
    delay(7500);
    open_flash('K');
    open_flash('K');
    alongLine(0, 0, 2000, 0);
  }
  // step5 冰壶to冰球
  if (c == 0x92)
  {
    setLightMode(4);
    open_flash('A');
    turn(45, 1);
    delay(500);
    alongLine(0, 0, 500, 0);
    delay(500);
    open_flash('A');
    turn(88, 1);
    delay(500);
    open_flash('G');
    open_flash('C');
    alongLine(0, 0, 2000, 0);
    delay(500);
  }
  // step6 冰球-car5向car1移动
  if (c == 0x93)
  {
    setLightMode(2);
    delay(5000);
    open_flash('C');
    open_flash('C');
    alongLine(0, 0, 2000, 0);
  }
  // step7 冰球-car5向car3移动
  if (c == 0x94)
  {
    delay(6000);
    open_flash('C');
    turn(87, 1);
    delay(500);
    /*
    getEncoder();
    subangle = angle - initAngle_;
    if (subangle < -300)
        subangle += 360;
    else if (subangle > 300)
        subangle -= 360;
    if(subangle>0.4)
    {
      turn(subangle ,1);
      }
    else if(subangle<-0.4)
    {
      turn(fabs(subangle),0);
    }*/
    delay(2400);
    open_flash('C');
    open_flash('C');
    alongLine(0, 0, 1000, 0);
  }
  // step8 冰球-car5向car2移动（追球）
  if (c == 0x95)
  {
    delay(2000);
    open_flash('C');
    alongLine(0, 0, 1000, 0);
    delay(1500);
    open_flash('C');
    turn(88, 1);
    delay(200);
    open_flash('C');
    alongLine(0, 0, 800, 0);
  }
  // step9 冰球to颁奖
  if (c == 0x96)
  {
    setLightMode(6);
    //turn(180, 1);
    //delay(200);
    //alongLine(0, 0, 500, 0);
    open_flash('A');
    turn(180, 1);
    delay(500);
    open_flash('H');
    open_flash('H');
    open_flash('H');
    open_flash('H');
    open_flash('H');
    open_flash('H');
    alongLine(0, 0, 5000, 0);
    delay(500);
    turn(90, 1);
    delay(500);
    /*
    getEncoder();
    subangle = angle - initAngle_;
    if (subangle < -300)
        subangle += 360;
    else if (subangle > 300)
        subangle -= 360;
    if(subangle>0.4)
    {
      turn(subangle ,1);
      }
    else if(subangle<-0.4)
    {
      turn(fabs(subangle),0);
    }*/
    /*
    delay(200);    
    turn(90, 1);
    delay(200);
    alongLine(0, 0, 3000, 0);
    delay(200);
    turn(180, 1);
    delay(200);
    getEncoder();
    subangle = angle - initAngle_;
    if (subangle < -300)
        subangle += 360;
    else if (subangle > 300)
        subangle -= 360;
    if(subangle>0.4)
    {
      turn(subangle ,1);
      }
    else if(subangle<-0.4)
    {
      turn(fabs(subangle),0);
    }*/
    delay(500);
  }    

  /*if (c == 0x95)
    {
    open_flash('A');
    }*/
  // step10 颁奖
  if (c == 0x97)
  {
    open_flash('Y');
    open_flash('Y');
    delay(1000);
    open_flash('P');
    open_flash('P');
    delay(2000);
    setLightMode(7);
    //alongLine(0, 0, 3000, 0);
    delay(500);
    /* 
     *  =============
     *  摇旗
     *  =============
     */
  }

}
