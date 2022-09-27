
#include "schedule4.h"
extern float angle;
extern float distance_cm;
extern int countLeft, countRight;
extern float delta;
void setup() {
  schedule_init();
   //motorInit();
 // encoderInit();
  Serial.begin(9600);
 
  
}

void loop() {

 // alongWall(300);
//  walk(0,0);
//walk(86,91);
//点阵屏调试代码  
/*
 close_flash();
      open_flash('D');
      delay(5000);
 */
//舵机调零代码
//walk(0,0);
//编码器调试代码

//Serial.println("距离");
//Serial.println(countLeft);
//Serial.println(countRight);
//delay(50);
//walk(100,100);// 500 550

//陀螺仪调试代码
//get_angle();
//delay(100);

//转圈
//turn(90,0);
//delay(1000);
//walk(100,100);//120 168
//Serial.println(countLeft);
//standBy();

schedule();


}
