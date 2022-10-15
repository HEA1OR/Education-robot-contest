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
    distanceLeft = left_round * countLeft / 60;  //左轮走了多少，单位：cm
    distanceRight = right_round * countRight / 60;  //右轮走了多少
//    Serial.print("leftdistance:");
//    Serial.println(distanceLeft);
//    Serial.print("rightdistance");
//    Serial.println(distanceRight);


    //actualDistance = (distanceLeft + distanceRight) / 2;

   actualDistance = distanceRight;

   //actualDistance = distanceLeft;
    
    deviation = now - last;
//    Serial.println(deviation);
     Serial.println("juju");
    Serial.println(deviation);

   //这一堆if判断 deviation 是干啥用的啊
   //这一堆 deviation 的判断标准就不改了，调参只需要调下面的walk函数的两个值
   
    if(deviation<=0.07 &&deviation>=-0.07)
    {
      walk(92,87);   //80  90
      delay(30);
    }
     else if(deviation<0.14&&deviation>0.07)
    {
     walk(144,92);  //11.22 125 85减少偏差  115 95感觉还是会有点向左偏 先试下 感觉还ok 那么 125 95也在减小偏差 
     
     delay(30);
    }
     else if(deviation<-0.07&&deviation>-0.14)
    {
     walk(81,96);//81 86  
     delay(30);
    }
     else if(deviation<0.25&&deviation>0.14)
    {
     walk(170,84);  // 11.22怀疑不是上面 是这里的左轮不够了 127  133也还是差那么一丢丢    135 90减少偏差  125 100还在减小偏差
     delay(30);
    }
     else if(deviation>-0.25&&deviation<-0.14)
    {
     walk(88,113);//11.22 80 120减少偏差   90 110还在减小偏差
     delay(30);
    }
   
    else if(deviation<-0.25&&deviation>-0.5)
    {
     walk(60,235);  //  65  157
     delay(40);
    }
    else if(deviation<=-0.5)
    {
      walk(50,270);//65 190
      delay(60);
    }
     else if(deviation>=0.5)
    {
      walk(330,50); //230 60
      delay(60);
    }
    else if(deviation<0.5&&deviation>0.25)
    {
      walk(250,50); //  150 85   170 80
      delay(40);    //  55
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
  detachInterrupt(0);  
  detachInterrupt(1);
   get_angle();
  temp_angle = angle;
//  Serial.println(angle);
  float x = 17;
  if(mode==0)
  x = 15;

  
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
      angletoturn -= angletoturn / 29.5;  // 26
    }
    // mode 是一个判断左转还是右转的标志变量，1为右转，0为左转
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
//          Serial.print("angle:");
//          Serial.println(angle);
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
    attachInterrupt(0, blinkLeft, CHANGE);
    attachInterrupt(1, blinkRight, CHANGE);
  standBy();
}


//这个是利用 陀螺仪 控制的直行函数
void alongLine(float setDistance) //1号车
{

  volatile float distanceLeft = 0, distanceRight = 0, e;


  volatile float leftSpeed = 92, rightSpeed = 80;
  
  float actualDistance = 0;
  float init_angle;
  countLeft = 0;
  countRight = 0;
  get_angle();
  init_angle = angle;

  do {

    distanceLeft = left_round * countLeft / 60;  //单位：cm
    distanceRight = right_round * countRight / 60;
    
  //  actualDistance = (distanceLeft + distanceRight) / 2;
     actualDistance = distanceRight;
    //actualDistance = distanceLeft;
     
    Serial.println("actualDistance");
    Serial.println(distanceLeft);
    Serial.println(distanceRight);
//    Serial.println(actualDistance);
//    Serial.println(countLeft);
//    Serial.println(countRight);
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
    if (e >= 5) //左偏5°
    {


        leftSpeed = 147 ;
        rightSpeed = 100;
    }
    else if (e <= -5) //右偏5°
    {

      

        leftSpeed = 92;
        rightSpeed = 147;
    }
    else if (e >= -1 && e <= 0)
    {

      

        leftSpeed = 82;
        rightSpeed = 100;
    }
     else if (e >= 0 && e <= 1)
    {

      

        leftSpeed = 104;
        rightSpeed = 90;
    }
    else if (e > -5 && e < -1) //右偏2~5°
    {

        leftSpeed = 82;
        rightSpeed = 92-8*e ;
    }
    else //左偏2~5°
    {
      

        leftSpeed = 96+8*e ;
        rightSpeed = 90;
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
  detachInterrupt(0);
  detachInterrupt(1);
  get_angle();
  temp_angle = angle;
  if(temp_angle>350)
  aim_angle+=360;
  e = temp_angle - aim_angle;
  
  if(e > 0.4 && e < 1) //需右转   11.22把 0.3改成了0.4
  {
   /*右转*/
   
      walk(20,-20);
      delay(70*e);  
  }
  else if(e > 1 && e < 10) //需右转
  {
   /*右转*/
   
      walk(20,-20);
      delay(50*e);  
  }
  else if(e < -0.4 && e > -1) //需左转
  {
     /*左转*/
   walk(-20,20);
   delay(-70*e);
   
  }
  else if(e < -1 && e > -10) //需左转
  {
     /*左转*/
   walk(-20,20);
   delay(-50*e);
   
  }

  //重启中断函数
  attachInterrupt(0, blinkLeft, CHANGE);
  attachInterrupt(1, blinkRight, CHANGE);
  standBy();
}
