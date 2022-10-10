#include "motor.h"
//#include "ult_wall.h"
#include "encoder.h"
#include "compass.h"
#include "schedule5.h"
#include "led_matrix.h"


extern float angle;
extern float distance_cm;
extern float delta;
extern int countLeft, countRight;
volatile float initAngle;

void setup(){
//  motorInit();
//  ultrasonic_init();  
//  encoderInit();
//  compassInit();
//  Serial.begin(9600);
//  get_angle();
//  initAngle = angle;
schedule_init();
 //motorInit();
 //encoderInit();
  Serial.begin(9600);
  led_matrix_init();

}

void loop(){
  

  schedule();
//  // 模块检测，-1： 停止（舵机是否调零）                       # 在硬件上调整，一般不需要
//  //          0： 直行（左右轮速度尽量匹配）                  # 调整motor.cpp中的walk函数中的adjust部分
//  //          1： 走直线和右转弯（指标：至少能完整的走10圈）     # 调整motor.cpp中的alongLine和smoothTurn函数中的adjust部分
//  //          2： 走直线和左转弯（指标：至少能完整的走10圈）     # 调整motor.cpp中的alongLine和smoothTurn函数中的adjust部分
//  //          3： xbee联合走
//  int mode = 2;
//
//  if(mode == -1){
//    standBy();
//    delay(10000);
//  }
//
//  if(mode == 0){
//    standBy();
//    delay(1000);
//    walk(30, 30 );
//    delay(4000);
//  }
//  else if(mode == 1){
//    alongLine(10000);
//    smoothTurn(91, 1);
//    alongLine(10000);
//    smoothTurn(90, 1);
//    alongLine(10000);
//    smoothTurn(91, 1);
//    alongLine(10000);
//    get_angle();
//    float turnAngle = angle - initAngle;
//    if(turnAngle < 0)
//      turnAngle += 360;
//    smoothTurn(turnAngle, 1);
//  }
//  else if(mode == 2){
//    alongLine(10000);
//    smoothTurn(90, 0);
//    alongLine(10000);
//    smoothTurn(90, 0);
//    alongLine(10000);
//    smoothTurn(90, 0);
//    alongLine(10000);
//    smoothTurn(90, 0);
//    alongLine(10000);
//  }
//  else if(mode == 3){
//    alongLine(8000);
//    smoothTurn(90, 1);
//    circle();
//    smoothTurn(90, 0);
//    alongLine(5000);
//    turn(180, 1);
//  }
}
