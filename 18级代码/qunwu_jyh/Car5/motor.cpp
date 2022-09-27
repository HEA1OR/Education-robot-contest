#include "motor.h"

Servo motorL, motorR;
extern int countLeft, countRight;
extern float distance_cm;
extern float angle;
float temp_angle,e,temp,aim_angle;

void motorInit() {
  motorL.attach(pinL);
  motorR.attach(pinR);
  motorL.writeMicroseconds(1500);
  motorR.writeMicroseconds(1500);
}

void walk(int left_speed, int right_speed)
{
  motorL.writeMicroseconds(1500+left_speed);
  motorR.writeMicroseconds(1500-right_speed);
}

//walk along the wall to set distance
void alongWall(float setDistance)
{
  float last, now, deviation;
  float distanceLeft = 0, distanceRight = 0, actualDistance = 0;
  countLeft = 0;
  countRight = 0;
  getDistance();
  last = distance_cm;
  while (setDistance > actualDistance) {
    getDistance();
    now = distance_cm;
    distanceLeft = left_round * countLeft / 60;  //单位：cm
    distanceRight = right_round * countRight / 60;
//    Serial.print("leftdistance:");
//    Serial.println(distanceLeft);
//    Serial.print("rightdistance");
//    Serial.println(distanceRight);
    actualDistance = (distanceLeft + distanceRight) / 2;
    deviation = now - last;   
//    Serial.println(deviation);
    if(deviation<=0.1 &&deviation>=-0.1)
    {
      //walk(100,110);
      walk(95,110);
    }
    else if(deviation<-0.1&&deviation>-0.5)
    {
      //walk(100,98);
      walk(95,95);
    }
    else if(deviation<=-0.5)
    {
      //walk(100,80);
      walk(95,80);
    }
     else if(deviation>=0.5)
    {
      //walk(60,110);
      walk(65,100);
    }
    else if(deviation<0.5&&deviation>0.1)
    {
      //walk(83,110);
      walk(80,110);
    }
    last = now;
    //delay(30);
    delay(55);
  }
  standBy();
}

void turn(float angletoturn, int mode)
{
  detachInterrupt(0);
  detachInterrupt(1);
  get_angle();
  temp_angle = angle;
    if (angletoturn <= 90 && angletoturn > 0)  //对偏差进行手动调整
    {
      angletoturn -= angletoturn / 24;
    }
    else if (angletoturn > 90 && angletoturn <= 180)
    {
      angletoturn -= angletoturn / 50;
    }
    if (mode)
    {
      /*右转*/
      aim_angle = temp_angle - angletoturn;
      if (aim_angle < -1e-7)
      {
        aim_angle += 360;
      }
        while (1)
        {
          get_angle();
          if(fabs(aim_angle - angle) < 1.0){
            break;
          }
            walk(50,-50);
        }
    }
    else
    {
      /*左转*/
      aim_angle = temp_angle + angletoturn;
      if (aim_angle >= 360)
      {
        aim_angle -= 360;
      }
        while (1)
        {
          get_angle();
          if(fabs(aim_angle - angle) < 1.0){
            break;
          }
             walk(-50,50);
        }
    }
    attachInterrupt(0, blinkLeft, CHANGE);
    attachInterrupt(1, blinkRight, CHANGE);
  standBy();
}

void alongLine(float setDistance) //5号车
{
  volatile float distanceLeft = 0, distanceRight = 0, e;
  volatile float leftSpeed = 120, rightSpeed = 60;
  float actualDistance = 0;
  float init_angle;
  countLeft = 0;
  countRight = 0;
  get_angle();
  init_angle = angle;
  do {
    distanceLeft = left_round * countLeft / 60;  //单位：cm
    distanceRight = right_round * countRight / 60;
    actualDistance = (distanceLeft + distanceRight) / 2;
    get_angle();
    temp_angle = angle;
    e = temp_angle - init_angle;
    if(e > 300) //对超过360°（0°）界限时进行修正
    {
      e -= 360; 
    }
    if(e < -300)
    {
      e += 360;
    }
    if (e >= 5) //左偏5°
    {
//      leftSpeed = 92;
//      rightSpeed = 80;
        leftSpeed = 100;
        rightSpeed = 50;
    }
    else if (e <= -5) //右偏5°
    {
//      leftSpeed = 100;
//      rightSpeed = 88;
        leftSpeed = 50;
        rightSpeed = 100;
    }
    else if (e >= -2 && e <= 2)
    {
//      leftSpeed = 100;
//      rightSpeed = 80;
        leftSpeed = 100;
        rightSpeed = 110;
    }
    else if (e > -5 && e < -2) //右偏2~5°
    {
//      leftSpeed = 100;
//      rightSpeed = 82.0 - e * 2.0;
        leftSpeed = 70;
        rightSpeed = 100;
    }
    else //左偏2~5°
    {
//      leftSpeed = 98.0 - e * 2.0;
//      rightSpeed = 80;
        leftSpeed = 100;
        rightSpeed = 70;
    }
//    motorL.write(leftSpeed);
//    motorR.write(rightSpeed);
    walk(leftSpeed,rightSpeed);
    delay(30);
  } while (actualDistance < setDistance);
  standBy();
}

void standBy()
{
  motorL.writeMicroseconds(1500);
  motorR.writeMicroseconds(1500);
}

void adjust(float aim_angle)
{
  detachInterrupt(0);
  detachInterrupt(1);
  get_angle();
  temp_angle = angle;
  e = temp_angle - aim_angle;
  if(e > 2) //需右转
  {
   /*右转*/
    do
    {
      walk(30,-30);
      get_angle();
      if(fabs(aim_angle - angle) <= 1.0)
      {
       break;
      }
    }while(fabs(aim_angle - angle) > 1.0);
  }
  else if(e < -2) //需左转
  {
     /*左转*/
    do
    {
      walk(-30,30);
      get_angle();
      if(fabs(aim_angle - angle) <= 1.0)
      {
       break;
      }  
    }while(fabs(aim_angle - angle) > 1.0);
  }
  attachInterrupt(0, blinkLeft, CHANGE);
  attachInterrupt(1, blinkRight, CHANGE);
  standBy();
}
