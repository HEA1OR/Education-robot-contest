#include "schedule.h"
#include "encoderLED.h"

extern float angle;
float tempangle;
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
    setLightMode(4);
    open_flash('A');
    open_flash('A');
    open_flash('A');
    alongLine(0, 0, 4000, 0);
    delay(200);
  }
  // step2  花滑
  if (c == 0x89)
  {
    setLightMode(5);
    getEncoder();
    tempangle = angle;
    delay(6500);
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
    open_flash('R');
    open_flash('R');
    open_flash('A');
    //alongLine(0, 0, 400, 0);
    alongCurve(3000, 1.5, 90);
    delay(1000);
    alongCurve(3200, 1.2, 90);
    delay(1000);
    alongCurve(3600, 1, 90);
    delay(1000);
    alongCurve(3000, 1.5, 90);
    delay(200);
    getEncoder();
    subangle = angle - tempangle;
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
      }
    //Sdelay(200);
    //alongLine(0, 0, 500, 0);
    /*
    delay(200);
    getEncoder();
    tempangle = angle;
    delay(4300);
    open_flash('H');
    turn(90, 1);
    delay(200);
    open_flash('H');
    turn(90, 1);
    delay(200);
    open_flash('H');
    turn(90, 1);
    delay(200);
    open_flash('H');
    turn(84, 1);
    delay(200);*/
    /*
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
      }*/
  }

  // step3 花滑to冰壶
  if (c == 0x90)
  {
    setLightMode(4);
    //   turn(180, 1);
    delay(200);
    open_flash('G');
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 1800, 0);
    delay(200);
    open_flash('L');
    turn(88, 1);
    delay(5500);
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 1400, 0);
    delay(200);
    open_flash('K');
    turn(45, 0);
    delay(200);
    //alongLine(0, 0, 1000, 0);
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
    /*
    turn(45, 0);
    delay(200);  
    alongLine(0, 0, 1500, 0);
    delay(200);*/
    setLightMode(4);
    open_flash('A');
    turn(135, 0);
    delay(6500);
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 2000, 0);
    delay(200);
    open_flash('C');
    turn(60, 0);
  }
  // step6 冰球-car4向car1移动
  if (c == 0x93)
  {
    setLightMode(2);
    delay(5000);
    open_flash('C');
    open_flash('C');
    open_flash('C');
    open_flash('C');
    alongLine(0, 0, 4500, 0);
  }
  // step7 冰球-car4向car3移动
  if (c == 0x94)
  {
    delay(6000);
    open_flash('C');
    turn(146, 1);
    delay(200);
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
    delay(2000);
    open_flash('C');
    alongLine(0, 0, 1100, 0);
  }
  // step8 冰球-car4向car2移动（追球）
  if (c == 0x95)
  {
    delay(2000);
    open_flash('C');
    alongLine(0, 0, 1000, 0);
    delay(1500);
    open_flash('C');
    turn(85, 1);
    delay(200);
    open_flash('C');
    alongLine(0, 0, 800, 0);
    delay(200);
  }
  // step9 冰球to颁奖
  if (c == 0x96)
  {
    setLightMode(6);
    open_flash('A');
    turn(176, 1);
    delay(200);
    open_flash('H');
    open_flash('H');
    alongLine(0, 0, 2100, 0);
    delay(200);
    open_flash('H');
    turn(87, 1);
    delay(200);
    /*
    getEncoder();
    subangle = angle - initAngle_;
    if (subangle < -300)
        subangle += 360;
    else if (subangle > 300)
        subangle -= 360;
    {
      turn(subangle ,1);
      }
    else if(subangle<-0.4)
    {
      turn(fabs(subangle),0);
    }*/
    /*
    delay(200);
    alongLine(0, 0, 6000, 0);
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
    delay(200);
  }
  /*if (c == 0x95)
    {
    open_flash('A');
    }*/
  // step10 颁奖
  if (c == 0x97)
  {
    open_flash('X');
    open_flash('X');
    delay(1000);
    open_flash('O');
    open_flash('O');
    delay(2000);
    setLightMode(7);
    //alongLine(0, 0, 4500, 0);
    delay(200);
    /* 
     *  =============
     *  摇旗
     *  =============
     */
  }

    if (c == 0x98)
  {
  /*  getEncoder();
    tempangle = angle; /
  /*  turn(60,0);
    alongLine(0, 0, 1000, 0); */
    delay(2000);
    turn_test(183, 0);
    delay(2000);
    turn_test(183, 0);
    delay(2000);
  /*  getEncoder();
    subangle = angle - tempangle;
    if(subangle>=0)
    {
      turn(subangle ,1);
      }
    else
    {
      turn(fabs(subangle),0);
      } */
    delay(200);
    /* 
     *  =============
     *  摇旗
     *  =============
     */
  }

}
