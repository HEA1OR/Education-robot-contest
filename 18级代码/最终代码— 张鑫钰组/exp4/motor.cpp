#include "motor.h"
#include "math.h"

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
#define left_standard_speed 1600
#define right_standard_speed 1398

void alongWall(float setDistance)
{
   float last, now, deviation;
  float distanceLeft = 0, distanceRight = 0, actualDistance = 0;
  countLeft = 0;
  countRight = 0;
  getDistance();
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
    //Serial.println("偏差");
   // Serial.println(deviation);
    if (deviation >= -0.06 && deviation <= 0.06)      //[-0.1,0.1]
    {
      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed);
    }
    else if ( deviation > -0.5 && deviation < -0.06) // (-0.5,-0.1)
    {
      motorL.writeMicroseconds(left_standard_speed - deviation * 150);
      motorR.writeMicroseconds(right_standard_speed - deviation*50);
    }
    else if (deviation <= -0.5)                     //(-inf,-0.5]
    {
      motorL.writeMicroseconds(left_standard_speed + 50);
      motorR.writeMicroseconds(right_standard_speed);
    }
    else if (deviation <0.5 && deviation >0.06)     // (0.1,0.5)
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
      motorR.writeMicroseconds(right_standard_speed+40);

      delay(25);
      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed-25);
      delay(15);

      motorL.writeMicroseconds(left_standard_speed);
      motorR.writeMicroseconds(right_standard_speed+25);
    }
    
    delay(30);
  }
  standBy();
}

void turn(float angletoturn, int mode)
{
  detachInterrupt(0);
  detachInterrupt(1);
  
  get_angle();
  temp_angle = angle;
  
   float last_angle;      //*
   
   int i=0;
    if(i==0)
    { last_angle=angle; 
      i++; 
     }
     if(angletoturn==45&&mode)
     {
      angletoturn=39.5;
     }
     else if(angletoturn==45&&!mode)
     {
      angletoturn=39.8;
     }
     else if(angletoturn==90&&!mode)
     {
      angletoturn=85;
     }
     else if(angletoturn==180&&!mode)
     {
      angletoturn=174;
     }
     else if(angletoturn==180&&mode)
     {
      angletoturn=173.3;
     }
      else if(angletoturn==135&&!mode)
     {
      angletoturn=129;
     }
     else if(angletoturn==135&&mode)
     {
      angletoturn=129;
     }
     else if(angletoturn==90&&mode)
     {
      angletoturn=84.3;
     }
    else if (angletoturn <= 90 && angletoturn > 0)  //对偏差进行手动调整
    {
      angletoturn -= angletoturn / 8;
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

          while(angle - last_angle > 5  || last_angle - angle > 5 )  //前后两次测得角度》10度，重新测量 ***
          { 
            if(last_angle>0&&last_angle<5  &&  angle<360&&angle>355)   //排除临界
            {
              break;
              }
             get_angle();
           }                                                           //***

         /* if( isnan(angle)==1 )  //右转中断误差修正
          {
            Serial.println(angle);
             get_angle();
             aim_angle= angle - fabs(last_angle - aim_angle);
              if (aim_angle < -1e-7)
              {
                 aim_angle += 360;
               }
               
            }*/
          
          if(fabs(aim_angle - angle) < 1.0){
            break;
          }
            walk(50,-50);

            last_angle=angle;                                          //***
            Serial.println(angle);
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

          while(angle - last_angle > 10  || last_angle - angle > 10 )  //前后两次测得角度》10度，重新测量
          { 
            if(angle>0&&angle<5  &&  last_angle<360&&last_angle>355)
            {
              break;
              }
             get_angle();
           }
          
          if(fabs(aim_angle - angle) < 1.0){
            break;
          }
             walk(-50,50);

             last_angle=angle;
        }
    }
    attachInterrupt(0, blinkLeft, CHANGE);
    attachInterrupt(1, blinkRight, CHANGE);
  standBy();
}

void alongLine(float setDistance) //3号车
{
  volatile float distanceLeft = 0, distanceRight = 0;
  volatile float leftSpeed = 100, rightSpeed = 101;
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
//      leftSpeed = 92;
//      rightSpeed = 80;
        leftSpeed = 100;
        rightSpeed = 62;
    }
    else if (e <= -5) //右偏5°
    {
//      leftSpeed = 100;
//      rightSpeed = 88;
        leftSpeed = 60;
        rightSpeed = 102;
    }
    else if (e >= -1.0 && e <= 1.0)
    {
//      leftSpeed = 100;
//      rightSpeed = 80;
        leftSpeed = 100;
        rightSpeed = 104;
    }
    else if (e > -5 && e < -1.0) //右偏1.5~5°
    {
   //   leftSpeed = 100;
 //     rightSpeed = 90.0 - e * 2.0;
      leftSpeed = 90;
     rightSpeed = 102;
    }
    else //左偏1.5~5°
    {
  //    leftSpeed = 100 ;
   //   rightSpeed = 87.0 + e * 2.0;
    leftSpeed = 100;
    rightSpeed = 92;
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
