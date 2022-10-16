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


//walk along the wall to set distance
#define left_standard_speed 1610
#define right_standard_speed 1405

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
    actualDistance = (distanceLeft + distanceRight) / 2;
    deviation = now - last;
//    Serial.println("偏差");
//    Serial.println(deviation);
   
    if (deviation >= -0.06 && deviation <= 0.1)      //[-0.1,0.1]
    {
      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed);
    }
    else if ( deviation > -0.5 && deviation < -0.06) // (-0.5,-0.1)
    {
      motorL.writeMicroseconds(left_standard_speed - deviation * 180); //根据车的特点增惩罚系数
      motorR.writeMicroseconds(right_standard_speed);
    }
    else if (deviation <= -0.5)                     //(-inf,-0.5]
    {
      motorL.writeMicroseconds(left_standard_speed + 50);
      motorR.writeMicroseconds(right_standard_speed);
    }
    else if (deviation <0.5 && deviation >0.1)     // (0.1,0.5)
    {
      motorL.writeMicroseconds(left_standard_speed - deviation * 100);
      motorR.writeMicroseconds(right_standard_speed);
    }
    else                                            //[0.5,inf)
    {
      motorL.writeMicroseconds(left_standard_speed - 50);
      motorR.writeMicroseconds(right_standard_speed);
    }
    
    last = now;

    if(now<=6.0) //避免撞墙
    {
      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed+25);
    }
    
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
    if (angletoturn < 89.7 && angletoturn > 0)  //对偏差进行手动调整
    {
      angletoturn -= angletoturn / 8;
    }
    else if (angletoturn <= 90.3 && angletoturn>=89.7)  //对偏差进行手动调整
    {
      angletoturn -= angletoturn / 12;
    }
    else if (angletoturn > 90.3 && angletoturn < 179.7)
    {
      angletoturn -= angletoturn / 19;
    }
    else if(angletoturn >= 179.7 && angletoturn <=180.2)  //对偏差进行手动调整
    {
      angletoturn -= angletoturn / 22;
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

void alongLine(float setDistance) //1号车
{
  volatile float distanceLeft = 0, distanceRight = 0, e;
  volatile float leftSpeed = 110, rightSpeed = 94.5;
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
  //  Serial.print("temp_angle:");
 //   Serial.println(temp_angle);
 //   Serial.print("init_angle");
 //   Serial.println(init_angle);
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
        leftSpeed = 110;
        rightSpeed = 50;
    }
    else if (e <= -5) //右偏5°
    {
//      leftSpeed = 100;
//      rightSpeed = 88;
        leftSpeed = 60;
        rightSpeed = 100;
    }
    else if (e >= -1.0 && e <= 1.0)
    {
//      leftSpeed = 100;
//      rightSpeed = 80;
        leftSpeed = 110;
        rightSpeed = 94.5;
    }
    else if (e > -5 && e < -1.0) //右偏1.5~5°
    {
   //   leftSpeed = 100;
 //     rightSpeed = 90.0 - e * 2.0;
      leftSpeed = 90;
     rightSpeed = 94;
    }
    else //左偏1.5~5°
    {
  //    leftSpeed = 100 ;
   //   rightSpeed = 87.0 + e * 2.0;
    leftSpeed = 110;
    rightSpeed = 75;
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
