#include "motor.h"
#include "math.h"
#include "encoderLED.h"

Servo motorL, motorR;
int sideChoose = 0; // 选择一边做为基准边，0为左，1为右
float leftVoltage = 0, rightVoltage = 0;      // 左右舵机的电压
float sideSpeed;
extern float angle;
extern int sideLength;
long int initLength;
long int record[5];
int initVoltage = 0;
int initSpeed = 40;

float temp_angle,e,temp,aim_angle,last_angle;

/**************使能函数Init***********/
void motorInit() {

  // attach函数，设定舵机的接口
  motorL.attach(pinL); //motor.h中已经定义了 pinL 为7  pinR 为8
  motorR.attach(pinR);

  //writeMicroseconds函数的取值是1000-2000,1500为静止,2000全速顺时针，1000全速逆时针
  motorL.writeMicroseconds(1500);
  motorR.writeMicroseconds(1500);
  
}
/**************************************/


/*******************walk 运动函数************************************/
void walk(float left_speed, float right_speed)
{
  //骅哥采取的代码是,左轮在1500的基础上减，右轮在1500的基础上加，这样就是后驱
  //左右定义错误？
  //后驱前进时，右轮在1500基础上减（逆时针）,左轮在1500基础上加(顺时针)
  //改为前驱设计,walk为右加左减少
////////////////////////  adjust  //////////////////////////////////
  left_speed *= 1.46;
  right_speed *= 1.38;//基本可以走直线 右轮比左轮转速快较多
////////////////////////////////////////////////////////////////////
  left_speed = min(left_speed, 400);//最大到400
  right_speed = min(right_speed, 400);
  motorL.writeMicroseconds(1500+left_speed);
  motorR.writeMicroseconds(1500-right_speed);
}
/*********************************************************************/

//等待函数
void standBy()
{
  motorL.writeMicroseconds(1500);
  motorR.writeMicroseconds(1500);
}


//转弯函数
void turn(float angletoturn, int mode, bool smoothTurn = false)
{
    // angleTurn为需要转到的角度，mode为左右转变量， smoothTurn为是否只动一个轮
    getEncoder();
    temp_angle = angle;//记录当前的角度
    // mode 是一个判断左转还是右转的标志变量，1为右转，0为左转
    if (mode)
    {
      /*右转*/
      aim_angle = temp_angle - angletoturn;
     if (aim_angle < -1e-7)
      {
        aim_angle += 360;
      }
      // Serial.println(aim_angle);
        while (1)
        {
            getEncoder();
            
              Serial.print("angle:");
              Serial.println(angle);
            if(fabs(aim_angle - angle) < 0.4){
            break;
            }//角度差距较小时不转
            float leftCoef, rightCoef;
            float temp = fabs(aim_angle - angle);//角度差的绝对值
            if(temp > 180)
                temp = fabs(temp - 360);
            float temp_1 = fabs(angletoturn - temp);
            temp = temp < temp_1 ? temp : temp_1;
    ////////////////////////  adjust  //////////////////////////////////
            leftCoef = pow(temp/fabs(angletoturn), 0.6);       
            rightCoef = pow(temp/fabs(angletoturn), 0.6);//调整思路是什么?
            if(!smoothTurn)
               // walk(-55 * rightCoef -10, 55 * leftCoef + 5);
               walk(55 * rightCoef +10, -55 * leftCoef - 5);
            else
                walk(5, -55 * leftCoef - 5);
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
          
            getEncoder();
            
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
            if(!smoothTurn)
               // walk(50 * leftCoef + 5, -50 * rightCoef -10);
                walk(-50 * leftCoef - 5, 50 * rightCoef +10);
            else
                walk(-50 * leftCoef - 5, 5);
////////////////////////////////////////////////////////////////////
        }
    }
    
  standBy();
}




//这个是小车的最核心函数，建议仔细研究
void alongLine(int setDistance, int mode = 0, int setTime = 10000, int reverse = 0, float setAngle = -1, float setBias = 0, float angleToTurn = 0)
{
    // mode 用来控制小车的启动停止速度，用来控制动作的衔接
    // 0：缓入缓出
    // 1：直入缓出
    // 2：缓入直出
    // 3：直入直出
    // reverse 控制车辆行驶方向，0为前进，1为后退
    // setAngle 用来设置小车的初始角度，默认值为-1（函数初始定义好）
    // setBias 是陀螺仪调整直线的偏差量，为0则走直线，否则走弧线，建议范围+-0.2 alongline中走直线
    // setBias 在alongLine中只保留接口，为防止歧义不应该直接修改，而是在alongCurve中修改
    // first的作用?

    volatile float errorA;
    bool stopSequence = false;
    volatile float leftSpeed = 0, rightSpeed = 0;
    int len = 0;
    volatile float countAngle = 0;
    int timer_1, timer_2, timer;
    timer_1 = millis();
    float sumErrorA = 0;                 // PID中积分累加项
    float lastErrorA = 0;                // PID中微分前项
    float totalA = 0;                    // PID总和
    float K_p = 300, K_i = 1, K_d = 1;   // PID中三项的系数

    float init_angle;
    //记录第一次的角度值(小车一定要放好)
    if(setAngle < 0){
        getEncoder();
        init_angle = angle;
        setAngle = init_angle; 
    }       
    else
        init_angle = setAngle;
    //initLength = sideLength; //sideLength用不上 
    getEncoder();
    last_angle = angle; //记录上一次的angle 只有角度变化时，getEncoder会更新角度数据
    
//    delay(100);
    int first = 0;
    int index = 0;
    Serial.println("start: ");
    //后续过程重复进行
    while(1){

        getEncoder();    
        //countAngle和angleToTurn初始值都为0
        if(abs(countAngle) > angleToTurn){
            setBias = 0; //调整偏差，直线
        }
        else{
            init_angle += setBias; //第一次读取的角度+0
            countAngle += setBias; //count+1
            if(init_angle > 360)  //init_angle记录了最初始一次的角度数据
                init_angle -= 360;
            else if(init_angle < 0)
                init_angle += 360;
        }
        Serial.print("init_angle: ");
        Serial.println(init_angle);
   //     Serial.print("length: ");
   //     Serial.println(sideLength);
        Serial.print("angle_now");
        Serial.println(angle);
        Serial.print("last_angle: ");
        Serial.println(last_angle);
        if(abs(last_angle - angle) > 10 && abs(last_angle - init_angle) < 10)
            temp_angle = last_angle; //角度差小时，当前角度等于上次记录的角度数据
        else if(abs(last_angle - angle) > 10 && abs(angle - init_angle) < 10)
            temp_angle = angle;
        else
            temp_angle = angle;
        Serial.print("temp_angle");
        Serial.println(angle);
        last_angle = angle; //不断更新lastangle和temp_angle的数值
        
//        errorL = setSpeeed - observeSpeed;
//        totalL = 2 * errorL; 
        errorA = temp_angle - init_angle; //角度误差为当前角度值-初始的角度值
        if(errorA < -360)
            errorA += 360;
        if(errorA > 360)
            errorA -= 360;
//        if(errorA < -20)
//            errorA = -20;
//        if(errorA > 20)
//            errorA = 20;
        Serial.print("errorA: ");
        Serial.println(errorA);
        if(errorA > 300) {//对超过360°（0°）界限时进行修正
            errorA -= 360; 
        }
        if(errorA < -300){
            errorA += 360;
        }
        float tempErrorA = lastErrorA - errorA;
        if(sumErrorA + errorA > 10 || sumErrorA + errorA < -10){
          sumErrorA += 0;
        }
        else
          sumErrorA += errorA;
////////////////////////  adjust  //////////////////////////////////
        // 一般当小车大幅度抖动甚至转圈时，需要调整此中参数，或者可以加入更多分段
        if(errorA < 1){ // error较小表明小车无较大偏差
          K_p = 150;
          K_i = 0;
          K_d = 0;
        }
        else if(errorA < 3){
          K_p = 70;
          K_i = 0;
          K_d = 30;
        }
        else{ // 否则小车偏差较大，需要调整
          K_p = 50;
          K_i = 10;
          K_d = 10;;
        }  
        /*
       if(errorA < 2){ // error较小表明小车无较大偏差
          K_p = 100;
          K_i = 0;
          K_d = 0;
        }
        else{ // 否则小车偏差较大，需要调整
          K_p = 30;
          K_i = 10;
          K_d = 60;
        } */       
////////////////////////////////////////////////////////////////////

        totalA = K_p * errorA + K_i * sumErrorA + K_d * tempErrorA;
////////////////////////  adjust  //////////////////////////////////
        totalA *= 0.10;
////////////////////////////////////////////////////////////////////

        lastErrorA = errorA;
//        Serial.print("totalL: ");
//        Serial.println(totalL);
        Serial.print("totalA: ");
        Serial.println(totalA);
        
//           leftSpeed = leftSpeed + totalL;
//           rightSpeed = leftSpeed + totalA;
//         leftSpeed = 100 + totalA;
//         rightSpeed = 100 - totalA;
         if (!reverse){
          leftSpeed = 100 + totalA;
          rightSpeed = 100 - totalA;
         }
         else{
          leftSpeed = -100 + totalA;
          rightSpeed = -100 - totalA;
         }
        
//        Serial.print("len: ");
//        Serial.println(sideLength - initLength);
        
        len = sideLength - initLength;
        timer_2 = millis();
        timer = timer_2 - timer_1;
        
        // 时序启动
        //初始定义了first = 0
        if(timer < 2000 && mode%2 == 0 && first == 0){
            double xtime = timer / 1000.0;
            float k = 1 / (1 + 0.1*exp(-xtime*2 + 4));
            Serial.print("k: ");
            Serial.println(k);
            leftSpeed *= k;
            rightSpeed *= k;
        }
        
        // 控停
//        Serial.println(mode);
        
        if((len > setDistance || timer_2 - timer_1 > setTime || stopSequence) && mode < 2){
            Serial.println("stop");
            stopSequence = true;
            if(first == 0){
                first = 1;
                timer_1 = timer_2;
                timer = 0;
            }
            double xtime = timer / 1000.0;
            float k = 1 - 1 / (1 + 0.1*exp(-xtime*2 + 4));
            if(timer > 2000)
                break;
            else{
                int leftSpeedTemp = leftSpeed;
                int rightSpeedTemp = rightSpeed;
                leftSpeedTemp *= k;
                rightSpeedTemp *= k;
                leftSpeed = leftSpeed ? leftSpeedTemp : abs(leftSpeed) < abs(leftSpeedTemp);
                rightSpeed = rightSpeed ? rightSpeedTemp : abs(rightSpeed) < abs(rightSpeedTemp);
            }
        }
        else if((len > setDistance || timer_2 - timer_1 > setTime || stopSequence) && mode >1){
            Serial.println("stop without buffer");
            return;
        }
         
        Serial.print("leftSpeed: ");
        Serial.println(leftSpeed);
        Serial.print("rightSpeed: ");
        Serial.println(rightSpeed);
        Serial.println(" ");
        walk(leftSpeed, rightSpeed);
        delay(55);
    }
    standBy();
}

/*
void alongCurve(int setDistance, float setBias,  float angleToTurn, int mode = 0, int setTime = 10000){
  alongLine(setDistance, mode, setTime, -1, setBias, angleToTurn);
}
*/
