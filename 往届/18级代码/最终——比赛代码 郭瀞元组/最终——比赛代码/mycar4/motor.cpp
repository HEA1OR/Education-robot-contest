#include "motor.h"
#include "math.h"

Servo motorL, motorR;

// extern是变量声名，告诉计算机去外部找这个变量
extern int countLeft, countRight;
extern float distance_cm;
extern float angle;

float temp_angle,e,temp,aim_angle;

void motorInit() {

  // attach函数，设定舵机的接口
  motorL.attach(pinL); //motor.h中已经定义了 pinL 为7  pinR 为8
  motorR.attach(pinR);

  //writeMicroseconds函数的取值是1000-2000,1500为静止,2000全速向前，1000全速向后
  motorL.writeMicroseconds(1500);
  motorR.writeMicroseconds(1500);
 
}

void walk(int left_speed, int right_speed)
{
  //骅哥采取的代码是,左轮在1500的基础上减，右轮在1500的基础上加
  motorL.writeMicroseconds(1500+left_speed); 
  motorR.writeMicroseconds(1500-right_speed);
}

// 贴墙直行的函数
// 直行有两个控制函数，一个是这个alongwall，一个是alongLine

void alongWall(float setDistance)
{
  
  //setDistance目标前进距离   actualDistance实际前进距离
  
  float last, now, deviation;
  float distanceLeft = 0, distanceRight = 0, actualDistance = 0;
  countLeft = 0;
  countRight = 0;

//getDistance()是ult_wall.cpp中定义的函数，其作用是获得车距墙的距离
//调用一次  getDistance()  distance_cm里面就有一个当前车和墙的距离值了
  /*getDistance();
  while(distance_cm-exdistance>3||distance_cm-exdistance<-3)
  {
    
    Serial.println(exdistance);
    if(distance_cm-exdistance>3)
    {
      Serial.println("if1");
      walk(100,80);
    }
    else if(distance_cm-exdistance<3)
    {
      Serial.println("if2");
      walk(80,100);
    }
    getDistance();

  }*/
  getDistance();
  last = distance_cm;
  while (setDistance > actualDistance) {
    getDistance();
    now = distance_cm;
    distanceLeft = left_round * countLeft / 40;  //左轮走了多少，单位：cm
    distanceRight = right_round * countRight / 40;  //右轮走了多少
//    Serial.print("leftdistance:");
//    Serial.println(distanceLeft);
//    Serial.print("rightdistance");
//    Serial.println(distanceRight);


    actualDistance = (distanceLeft + distanceRight) / 2;

   //actualDistance = distanceRight/2;

   //actualDistance = distanceLeft;
    
    deviation = now - last;
    Serial.println(deviation);


   //这一堆if判断 deviation 是干啥用的啊
   //这一堆 deviation 的判断标准就不改了，调参只需要调下面的walk函数的两个值
   
    if(deviation<=0.07 &&deviation>=-0.07)
    {
      walk(86,95);  
      delay(30);
    }
     else if(deviation<0.13&&deviation>0.07)
    {
     walk(88,93);  
     delay(30);
    }
     else if(deviation<-0.07&&deviation>-0.13)
    {
     walk(80,127);  // 95 114   99 114 会右偏  104 118右偏  100 128右偏  95 115
     delay(30);
    }
     else if(deviation<0.25&&deviation>0.13)
    {
     walk(87+100*deviation,99);  // 94 98
     delay(30);
    }
     else if(deviation>-0.25&&deviation<-0.13)
    {
     walk(67,123+200*deviation);//96 120  98 120还是右偏  104 135  90 130
     delay(30);
    }
   
    else if(deviation<-0.25&&deviation>-0.5)
    {
     walk(67,243);  // 78 185 右偏   88 185
     delay(30);
    }
    else if(deviation<=-0.5)
    {
      walk(60,279);  
      delay(30);
    }
     else if(deviation>=0.5)
    {
      walk(190,74); //230 60
      delay(30);
    }
    else if(deviation<0.5&&deviation>0.25)
    {
      walk(128,84); //  150 85
      delay(30);    //  55
    }
    last = now;
    
  }
  standBy();
}

//转弯函数
void turn(float angletoturn, int mode)
{

  //这个函数可以用于取消中断
  //在转弯过程中，必须中断之前定义的直行时候的encoder记录路程

   get_angle();
  temp_angle = angle;
  Serial.println(angle);
  float x = 14;
  if(mode==0)
  x = 17.3;

  
  float y = 10;  // y是控制45度的
  if(mode==0)
  y = 8.5;
  else
  y=6;
  
  //这里具体调整的细节也不懂
  // if 判断里的不做改变,只变后面的调整部分
  
    if (angletoturn <= 91 && angletoturn > 46)  //对偏差进行手动调整
    {
      angletoturn -= angletoturn / x;
    }
    else if (angletoturn > 0 && angletoturn <= 46)
    {
      angletoturn -= angletoturn / y;
    }
    else if (angletoturn > 90 && angletoturn <= 180)
    {
      angletoturn -= angletoturn / 33;  // 26    
    // mode 是一个判断左转还是右转的标志变量，1为右转，0为左转
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
    
    //重启中断函数
  
  standBy();
}
void turn2(float angletoturn, int mode)
{

  //这个函数可以用于取消中断
  //在转弯过程中，必须中断之前定义的直行时候的encoder记录路程

   get_angle();
  temp_angle = angle;
  Serial.println(angle);
  float x = 14;
  if(mode==0)
  x = 17.3;

  
  float y = 10;  // y是控制45度的
  if(mode==0)
  y = 8.5;
  else
  y=6;
  
  //这里具体调整的细节也不懂
  // if 判断里的不做改变,只变后面的调整部分
  
    if (angletoturn <= 91 && angletoturn > 46)  //对偏差进行手动调整
    {
      angletoturn -= angletoturn / x;
    }
    else if (angletoturn > 0 && angletoturn <= 46)
    {
      angletoturn -= angletoturn / y;
    }
    else if (angletoturn > 90 && angletoturn <= 180)
    {
      angletoturn -= angletoturn / 33;  // 26    
    // mode 是一个判断左转还是右转的标志变量，1为右转，0为左转
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
            walk(70,-70);
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
             walk(-70,70);
        }
    }
    
    //重启中断函数
  
  standBy();
}


//这个是利用 陀螺仪 控制的直行函数
void alongLine(float setDistance) //1号车
{

  volatile float distanceLeft = 0, distanceRight = 0, e;


  volatile float leftSpeed = 86, rightSpeed = 91;
  float actualDistance = 0;
  float init_angle;
  countLeft = 0;
  countRight = 0;
  get_angle();
  init_angle = angle;

  do {

    distanceLeft = left_round * countLeft / 40;  //单位：cm
    distanceRight = right_round * countRight / 40;
    
    actualDistance = (distanceLeft + distanceRight) / 2;
     //actualDistance = distanceRight/2;
    //actualDistance = distanceLeft;
     
    /*Serial.println("actualDistance");
    Serial.println(distanceLeft);
    Serial.println(distanceRight);
    Serial.println(actualDistance);
    Serial.println(countLeft);
    Serial.println(countRight);
    */
    //每次调用一次get_angle() angle变量里就会存有一个值
    get_angle();
    temp_angle = angle;
    e = temp_angle - init_angle;
    /*
    Serial.print("init:");
    Serial.println(init_angle);
    Serial.print("temp:");
    Serial.println(temp_angle);
    Serial.print("e:");
    Serial.println(e);
    */
    if(e > 300) //对超过360°（0°）界限时进行修正
    {
      e -= 360; 
    }
    if(e < -300)
    {
      e += 360;
    }
    //98 102
    if (e >= 5) //左偏5°
    {


        leftSpeed = 106;//delta=45
        rightSpeed = 85;
    }
    else if (e <= -5) //右偏5°
    {

      

        leftSpeed = 71;
        rightSpeed = 118;
    }
    else if (e >= -1.5 && e <= 0)
    {

      

        leftSpeed = 86;//delta=10
        rightSpeed = 107;
    }
     else if (e >= 0 && e <= 1.5)
    {

      

        leftSpeed = 96;
        rightSpeed = 97;
    }
    else if (e > -5 && e < -1.5) //右偏2~5°
    {

        leftSpeed = 86;
        rightSpeed = 98-5*e ;
    }
    else //左偏2~5°
    {
      

        leftSpeed = 86+5*e ;
        rightSpeed = 98;
    }
    /*
     Serial.print("leftspeed:");
     Serial.println(leftSpeed);
     Serial.print("rightspeed:");
     Serial.println(rightSpeed);
     */
    
    walk(leftSpeed,rightSpeed);
    
  } while (actualDistance < setDistance);
  standBy();
}
void alongLine0(float setDistance) //1号车
{

  volatile float distanceLeft = 0, distanceRight = 0, e;


  volatile float leftSpeed = 74, rightSpeed = 90;
  int i=10;
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
     //actualDistance = distanceRight/2;
    //actualDistance = distanceLeft;
     /*
    Serial.println("actualDistance");
    Serial.println(distanceLeft);
    Serial.println(distanceRight);
    Serial.println(actualDistance);
    Serial.println(countLeft);
    Serial.println(countRight);
    */
    //每次调用一次get_angle() angle变量里就会存有一个值
    get_angle();
    temp_angle = angle;
    e = temp_angle - init_angle;
    /*
    Serial.print("init:");
    Serial.println(init_angle);
    Serial.print("temp:");
    Serial.println(temp_angle);
    Serial.print("e:");
    Serial.println(e);
    */
    if(e > 300) //对超过360°（0°）界限时进行修正
    {
      e -= 360; 
    }
    if(e < -300)
    {
      e += 360;
    }
    //98 102
    if (e >= 5) //左偏5°
    {


        leftSpeed = 98 ;//delta=55
        rightSpeed = 79;
    }
    else if (e <= -5) //右偏5°
    {

      

        leftSpeed = 66;
        rightSpeed = 117;
    }
    else if (e >= -1.5 && e <= 0)
    {

      

        leftSpeed = 70.5;//delta=10
        rightSpeed = 95;
    }
     else if (e >= 0 && e <= 1.5)
    {

      

        leftSpeed = 78.5;
        rightSpeed = 89;
    }
    else if (e > -5 && e < -1.5) //右偏2~5°
    {

        leftSpeed = 75;
        rightSpeed = 89-7*e ;
    }
    else //左偏2~5°
    {
      

        leftSpeed = 75+7*e ;
        rightSpeed = 89;
    }
    /*
     Serial.print("leftspeed:");
     Serial.println(leftSpeed);
     Serial.print("rightspeed:");
     Serial.println(rightSpeed);
     */
     if(i>0)
     {
      leftSpeed=74;
      rightSpeed=90;
     }
     i--;
    walk(leftSpeed,rightSpeed);
    
  } while (actualDistance < setDistance);
  standBy();
}

//静止函数，当writeMicroseconds中给的值是1500时，静止不动
//writeMicroseconds的值的范围是1000-2000，1000为逆时针全速，2000为顺时针全速
void standBy()
{
  motorL.writeMicroseconds(1500);
  motorR.writeMicroseconds(1500);
}

//adjust函数是调整小车转过角度的函数，反馈调节
void adjust(float aim_angle)
{

  //因为涉及到转向，停止中断函数

  get_angle();
  temp_angle = angle;
  e = temp_angle - aim_angle;
  if(e > 1&& e < 10) //需右转
  {
   /*右转*/
   
      walk(20,-20);
      delay(30*e);
  }
  else if(e < -1 && e > -10) //需左转
  {
     /*左转*/
   
      walk(-20,20);
     delay(-30*e);
  }

  //重启中断函数

  standBy();
}
