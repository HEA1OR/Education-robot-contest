#include "motor.h"
#include "math.h"
#include "time.h"


Servo motorL, motorR;

// extern是变量声名，告诉计算机去外部找这个变量
//extern int countLeft, countRight;
//extern float distance_cm;
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

void walk(float left_speed, float right_speed)
{
  //骅哥采取的代码是,左轮在1500的基础上减，右轮在1500的基础上加，这样就是后驱
////////////////////////  adjust  //////////////////////////////////
  left_speed *= 1.27;
  right_speed *= 1.4;
////////////////////////////////////////////////////////////////////
  motorL.writeMicroseconds(1500-left_speed);
  motorR.writeMicroseconds(1500+right_speed);
}

// 贴墙直行的函数
// 直行有两个控制函数，一个是这个alongwall，一个是alongLine
// 只剩一个控制函数了，是alongLine


//转弯函数
void turn(float angletoturn, int mode)
{
    //这个函数可以用于取消中断
    //在转弯过程中，必须中断之前定义的直行时候的encoder记录路程
    detachInterrupt(0);  
    detachInterrupt(1);
    get_angle();
    temp_angle = angle;
    // mode 是一个判断左转还是右转的标志变量，1为右转，0为左转
    if (mode)
    {
      /*右转*/
      aim_angle = temp_angle - angletoturn;
      if (aim_angle < -1e-7)
      {
        aim_angle += 360;
      }
//      Serial.println(aim_angle);
        while (1)
        {
          get_angle();
          
//          Serial.print("angle:");
//          Serial.println(angle);
          if(fabs(aim_angle - angle) < 0.4){
            break;
          }
          float leftCoef, rightCoef;
          float temp = fabs(aim_angle - angle);
          if(temp > 180)
            temp = fabs(temp - 360);
          float temp_1 = fabs(angletoturn - temp);
          temp = temp < temp_1 ? temp : temp_1;
////////////////////////  adjust  //////////////////////////////////
          leftCoef = pow(temp/fabs(angletoturn), 0.6);       
          rightCoef = pow(temp/fabs(angletoturn), 0.6);
          walk(-50 * rightCoef -10, 50 * leftCoef + 10);
////////////////////////////////////////////////////////////////////
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
          if(fabs(aim_angle - angle) < 0.4){
            break;
          }
          float leftCoef, rightCoef;
          float temp = fabs(aim_angle - angle);
          if(temp > 180)
            temp = fabs(temp - 360);
          float temp_1 = fabs(angletoturn - temp);
          temp = temp < temp_1 ? temp : temp_1;
////////////////////////  adjust  //////////////////////////////////
          leftCoef = pow(temp/fabs(angletoturn), 0.5);       
          rightCoef = pow(temp/fabs(angletoturn), 0.5);
          walk(40 * leftCoef + 5, -40 * rightCoef -5);
////////////////////////////////////////////////////////////////////
        }
    }
    
    //重启中断函数
    attachInterrupt(0, blinkLeft, CHANGE);
    attachInterrupt(1, blinkRight, CHANGE);
  standBy();
  get_angle();
//  Serial.println(angle - temp_angle);
}

// 与上面turn函数的区别是这个函数左转只动右轮，右转只动左轮
void smoothTurn(float angletoturn, int mode)
{
    //这个函数可以用于取消中断
    //在转弯过程中，必须中断之前定义的直行时候的encoder记录路程
    detachInterrupt(0);
    detachInterrupt(1);
    get_angle();
    temp_angle = angle;
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
          
          Serial.println(angle);
          if(fabs(aim_angle - angle) < 0.4){
            break;
          }
          float leftCoef, rightCoef;
          float temp = fabs(aim_angle - angle);
          if(temp > 180)
            temp = fabs(temp - 360);
          float temp_1 = fabs(angletoturn - temp);
          temp = temp < temp_1 ? temp : temp_1;
////////////////////////  adjust  //////////////////////////////////
          // leftCoef, rightCoef是指速度权重因子
          leftCoef = pow(temp/fabs(angletoturn), 0.6);       
          rightCoef = pow(temp/fabs(angletoturn), 0.6);
          walk(5, 60 * leftCoef + 15);
////////////////////////////////////////////////////////////////////
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
          Serial.println(angle);
          if(fabs(aim_angle - angle) < 0.4){
            break;
          }
          float leftCoef, rightCoef;
          float temp = fabs(aim_angle - angle);
          if(temp > 180)
            temp = fabs(temp - 360);
          float temp_1 = fabs(angletoturn - temp);
          temp = temp < temp_1 ? temp : temp_1;
////////////////////////  adjust  //////////////////////////////////
          // leftCoef, rightCoef是指速度权重因子
          leftCoef = pow(temp/fabs(angletoturn), 0.5);       
          rightCoef = pow(temp/fabs(angletoturn), 0.5);
          walk(50 * leftCoef + 10, 5);
////////////////////////////////////////////////////////////////////
        }
    }
    
    //重启中断函数
    attachInterrupt(0, blinkLeft, CHANGE);
    attachInterrupt(1, blinkRight, CHANGE);
    standBy();
    get_angle();
}


//
//这个是利用 陀螺仪 控制的直行函数
void alongLine(int setTime, int mode = 0,float setAngle = -1) //1号车
{
    // mode 用来控制小车的启动停止速度
    // 0：缓入缓出
    // 1：直入缓出
    // 2：缓入直出
    // 3：直入直出

    volatile float  error;
    volatile float leftSpeed, rightSpeed;
    float sumError = 0;  // PID中积分累加项
    float lastError = 0;  // PID中微分前项
    float total = 0;         //  PID总和
    float K_p = 300, K_i = 1, K_d = 1;  // PID中三项的系数

    int timer_1, timer_2;
 //   int distanceOrTime = 0;
    float record = 0;
    timer_1 = millis();
    float init_angle;
    if(setAngle < 0){
      get_angle();
      init_angle = angle; 
    }       
    else
      init_angle = setAngle;      
//    Serial.println(init_angle);
    delay(100);
    while(1){
        //每次调用一次get_angle() angle变量里就会存有一个值
        get_angle();
        temp_angle = angle;
//        Serial.println(angle);

//        Serial.println(temp_angle);
        error = temp_angle - init_angle;
        if(error > 300) {//对超过360°（0°）界限时进行修正
            error -= 360; 
        }
        if(error < -300){
            error += 360;
        }
        float temp = lastError - error;
        if(sumError + error > 10 || sumError + error < -10){
          sumError += 0;
        }
        else
          sumError += error;
////////////////////////  adjust  //////////////////////////////////
        // 一般当小车大幅度抖动甚至转圈时，需要调整此中参数，或者可以加入更多分段
        if(error < 1){ // error较小表明小车无较大偏差
          K_p = 100;
          K_i = 0;
          K_d = 0;
        }
        else{ // 否则小车偏差较大，需要调整
          K_p = 30;
          K_i = 0;
          K_d = 50;
        }
////////////////////////////////////////////////////////////////////

        total = K_p * error + K_i * sumError + K_d * temp;
////////////////////////  adjust  //////////////////////////////////
        total *= 0.1;
////////////////////////////////////////////////////////////////////

        lastError = error;
        leftSpeed = 100 - total;
        rightSpeed = 100 + total;

        timer_2 = millis();     
//        Serial.print(timer_2 - timer_1);
//        Serial.print("\t");
//        Serial.println(distanceOrTime);
        // 时序启动
////////////////////////  adjust  //////////////////////////////////
        if (timer_2 - timer_1 <  2000 && mode%2 == 0){
          volatile double xTime = (timer_2 - timer_1)/1000.0;
//          Serial.println(xTime);
          leftSpeed *= 1/(1 + 0.1*exp(-xTime*2 + 4));
          rightSpeed *= 1/(1 + 0.1*exp(-xTime*2 + 4));
        }
////////////////////////////////////////////////////////////////////
        
//        // 超声波控停
//        if(distanceOrTime == 0 || distanceOrTime == 2){
//          // 这儿的distanceOrTime变量是为了防止超声波控停和时序控停相冲突而定义的
//          // 也就是说只要小车进入其中一个控停环节，便不会同时进入另外一个控停环节
//          getDistance();
//////////////////////////  adjust  //////////////////////////////////
//          if(distance_cm < 35 && distance_cm > 3 && fabs(record - distance_cm) < 5 && mode < 2){
//            volatile double xDistance = fabs(distance_cm - 45) / 5.0 ;
//            Serial.print("distance: ");
//            Serial.println(xDistance);
//            float leftSpeedTemp = (100 - total) * (1 - 1/(1 + 0.1*exp(-xDistance*1 + 5)));
//            float rightSpeedTemp = (100 + total) * (1 - 1/(1 + 0.1*exp(-xDistance*1 + 5)));
//            leftSpeed = leftSpeed ? leftSpeedTemp : leftSpeed < leftSpeedTemp;
//            rightSpeed = rightSpeed ? rightSpeedTemp : rightSpeed < rightSpeedTemp;
//            distanceOrTime = 2;
//          }
//          if(distance_cm < 22 && distance_cm > 3 && fabs(record - distance_cm) < 5){
//            break;
//          }
//////////////////////////////////////////////////////////////////////
//          record   = distance_cm;
//        }

        // 时序控停
      //if(distanceOrTime == 0 || distanceOrTime == 1){
////////////////////////  adjust  //////////////////////////////////
          if (timer_2 - timer_1 > setTime - 2000 && mode < 2){
            volatile double xTime = (timer_2 - timer_1 - setTime + 2000 )/1000.0 ;
            Serial.print("time: ");
            Serial.println(xTime);
            float leftSpeedTemp = (100 - total) * (1 - 1/(1 + 0.1*exp(-xTime*2 + 4)));
            float rightSpeedTemp = (100 + total) * (1 - 1/(1 + 0.1*exp(-xTime*2 + 4)));
            leftSpeed = leftSpeed ? leftSpeedTemp : leftSpeed < leftSpeedTemp;
            rightSpeed = rightSpeed ? rightSpeedTemp : rightSpeed < rightSpeedTemp;
           
          }
////////////////////////////////////////////////////////////////////
          if(timer_2 - timer_1 > setTime){
            break;
          }
        
        
        walk(leftSpeed, rightSpeed);
        delay(55);
    }
    
    standBy();
}

// 花活函数，用于小车绕圈(右转)
void circle(int mode){
  get_angle();
  float initAngle = angle;
  int count = 0;
  delay(100);
  alongLine(6000);  //直走走到圆的切线处
  if(initAngle > 180)
    count = 1;
  else
    count = 0;
  float lastAngle = angle;
  float diffAngle;
  float sumAngle = 0;
  float coef = 0;
  while(true){
    get_angle();
    Serial.print(angle);
    if(mode == 1){
      diffAngle = lastAngle - angle;
    }
    else{
      diffAngle = angle - lastAngle;
    }
    lastAngle = angle;
    if(diffAngle < -180)
      diffAngle += 360;
    sumAngle += diffAngle;
    Serial.print("\t");
    Serial.println(sumAngle);
    if(sumAngle > 540)
      break;
    if(sumAngle < 30)
      coef = 1 / (1 + 0.2 * exp(-(sumAngle / 10.0) * 1.5 + 3));
    else if(sumAngle > 510)
      coef = 1 - 1 / (1 + 0.2 * exp(-((sumAngle - 510) / 10.0) * 1.2 + 4));
    if(mode == 1){
      walk(57 * coef, 100 * coef);
    }
    else{
      walk(100 * coef, 57 * coef);
    }
    delay(55);
  }
  alongLine(6000); //走回墙边
}

//静止函数，当writeMicroseconds中给的值是1500时，静止不动
//writeMicroseconds的值的范围是1000-2000，1000为逆时针全速，2000为顺时针全速
void standBy()
{
  motorL.writeMicroseconds(1500);
  motorR.writeMicroseconds(1500);
}
