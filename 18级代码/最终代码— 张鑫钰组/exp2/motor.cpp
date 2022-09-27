#include "motor.h"

Servo motorL, motorR;
extern int countLeft, countRight;
extern float distance_cm; //距离墙的距离
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



#define left_standard_speed 1580
#define right_standard_speed 1415

//改进后
void alongWall(float setDistance)
{
  float last, now, deviation;
  float distanceLeft = 0, distanceRight = 0, actualDistance = 0;
  countLeft = 0;
  countRight = 0;
  
  getDistance();  //初始时多次探测，减少上次运行alongwall对本次的影响
  getDistance();
  getDistance();
  getDistance();
  getDistance();
  
  last = distance_cm;
  while (setDistance > actualDistance) {
    getDistance();
    now = distance_cm;
    distanceLeft = left_round * countLeft / 60;  //单位：cm
    distanceRight = right_round * countRight / 60;
    actualDistance = (distanceLeft + distanceRight) / 2;
    deviation = now - last;

   // Serial.print("leftdistance:");
    //Serial.println(distanceLeft);
    //Serial.print("rightdistance");
    //Serial.println(distanceRight);
    
   // Serial.println("偏差");
    //Serial.println(deviation);
    if (deviation >= -0.1 && deviation <= 0.1)      //[-0.1,0.1]
    {
      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed);
    }
    else if ( deviation > -0.5 && deviation < -0.08) // (-0.5,-0.1)
    {
      motorL.writeMicroseconds(left_standard_speed - deviation * 26);
      motorR.writeMicroseconds(right_standard_speed - deviation * 26);
    }
    else if (deviation <= -0.5)                     //(-inf,-0.5]
    {
      motorL.writeMicroseconds(left_standard_speed + 12);
      motorR.writeMicroseconds(right_standard_speed + 12);
    }
    else if (deviation <0.5 && deviation >0.1)     // (0.1,0.5)
    {
      motorL.writeMicroseconds(left_standard_speed - deviation * 22);
      motorR.writeMicroseconds(right_standard_speed - deviation * 22);
    }
    else                                            //[0.5,inf)
    {
      motorL.writeMicroseconds(left_standard_speed - 12);
      motorR.writeMicroseconds(right_standard_speed - 12);
    }
    
    last = now;

    if(now<=6.0) //避免撞墙
    {
      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed+20);

      delay(25);
      motorL.writeMicroseconds(left_standard_speed-5);
      motorR.writeMicroseconds(right_standard_speed);
      delay(5);

      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed+5);
    }
    
    delay(25);
  }
  standBy();
}
/*
void alongWall(float setDistance)
{
  float last, now, deviation;
  float distanceLeft = 0, distanceRight = 0, actualDistance = 0;
  countLeft = 0;
  countRight = 0;
  
  getDistance();  //初始时多次探测，减少上次运行alongwall对本次的影响
  getDistance();
  getDistance();
  getDistance();
  getDistance();
  
  last = distance_cm;
  while (setDistance > actualDistance) {
    getDistance();
    now = distance_cm;
    distanceLeft = left_round * countLeft / 60;  //单位：cm
    distanceRight = right_round * countRight / 60;
    actualDistance = (distanceLeft + distanceRight) / 2;
    deviation = now - last;

   // Serial.print("leftdistance:");
    //Serial.println(distanceLeft);
    //Serial.print("rightdistance");
    //Serial.println(distanceRight);
    
   // Serial.println("偏差");
    //Serial.println(deviation);
    if (deviation >= -0.1 && deviation <= 0.1)      //[-0.1,0.1]
    {
      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed);
    }
    else if ( deviation > -0.5 && deviation < -0.1) // (-0.5,-0.1)
    {
      motorL.writeMicroseconds(left_standard_speed -deviation * 60);
      motorR.writeMicroseconds(right_standard_speed );
    }
    else if (deviation <= -0.5)                     //(-inf,-0.5]
    {
      motorL.writeMicroseconds(left_standard_speed + 30);
      motorR.writeMicroseconds(right_standard_speed );
    }
    else if (deviation <0.5 && deviation >0.1)     // (0.1,0.5)
    {
      motorL.writeMicroseconds(left_standard_speed - deviation * 60);
      motorR.writeMicroseconds(right_standard_speed );
    }
    else                                            //[0.5,inf)
    {
      motorL.writeMicroseconds(left_standard_speed - 30);
      motorR.writeMicroseconds(right_standard_speed );
    }
    
    last = now;

    if(now<=6.0) //避免撞墙
    {
      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed+20);

      delay(25);
      motorL.writeMicroseconds(left_standard_speed-5);
      motorR.writeMicroseconds(right_standard_speed);
      delay(5);

      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed+5);
    }
    
    delay(40);
  }
  standBy();
}
*/
void turn(float angletoturn, int mode)
{
  detachInterrupt(0);
  detachInterrupt(1);
  get_angle();
  temp_angle = angle;

  if(mode)
  {                                               //对右转偏差进行手动调整
    if(angletoturn <= 45.5 && angletoturn > 0)
    {
     angletoturn -= angletoturn / 10; 
    }
    else if (angletoturn <= 90.5 && angletoturn > 45.5)  
    {
      angletoturn -= angletoturn / 20;   //***
    }
    else if (angletoturn > 90.5 && angletoturn <= 180)
    {
      angletoturn -= angletoturn / 50;
    }
  }
  else                                             //对左转偏差进行手动调整
  {
    if(angletoturn <= 45.5 && angletoturn > 0)
    {
     angletoturn -= angletoturn / 10;     //****
    }
    else if (angletoturn <= 90.5 && angletoturn > 45.5)  
    {
      angletoturn -= angletoturn / 18;
    }
    else if (angletoturn > 90.5 && angletoturn <= 180.5)
    {
      angletoturn -= angletoturn / 40;
    }
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
            walk(45,-45);
        }
    }
    else
    {    /*左转*/
      aim_angle = temp_angle + angletoturn ;
      
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
             walk(-45,45);
        }
    }
    
    attachInterrupt(0, blinkLeft, CHANGE);
    attachInterrupt(1, blinkRight, CHANGE);
  standBy();
}

void alongLine(float setDistance) //
{
  volatile float distanceLeft = 0, distanceRight = 0, e;
  volatile float leftSpeed = 78, rightSpeed = 80;          //*********可调量
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
    Serial.print("leftdistance:");
    Serial.println(distanceLeft);
    Serial.print("rightdistance");
    Serial.println(distanceRight);
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
        leftSpeed = 80;
        rightSpeed = 50;
    }
    else if (e <= -5) //右偏5°
    {
        leftSpeed = 50;
        rightSpeed = 80;
    }
    else if (e >= -1.5 && e <= 1.5)
    {

        leftSpeed = 80;                   //*******可调量
        rightSpeed = 80;
    }
    else if (e > -5 && e < -1.5) //右偏2~5°
    {
//      leftSpeed = 100;
//      rightSpeed = 82.0 - e * 2.0;
        leftSpeed = 65;
        rightSpeed = 80;
    }
    else //左偏2~5°
    {
//      leftSpeed = 98.0 - e * 2.0;
//      rightSpeed = 80;
        leftSpeed = 80;
        rightSpeed = 65;
    }
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
  //standBy();
}
