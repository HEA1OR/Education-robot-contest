
#include "schedule3.h"
extern float angle;
extern float distance_cm;
extern float delta;
extern int countLeft, countRight;
void setup() {
  schedule_init();
//  motorInit();
//  encoderInit();
  Serial.begin(9600);
 
  
}

void loop() {

//Serial.println("距离");
//Serial.println(countLeft);
//Serial.println(countRight);
//delay(50);
//walk(100,100);// 500 550
//

schedule();

//alongLine(400);


//alongWall(400);
/*
  //car3 救护车B
  //*********************第一阶段*************************
  alongLine(80.7);//  83.7多了
  delay(1000);//所有点阵屏要在路口亮   这里有了delay 应该不用再多加delay了吧
  turn(89.7,1);//89.7没有 多了
  delay(500);
  
  alongLine(65);
  delay(3000);
  adjust(90+delta);
  //***********************第二三阶段********************
  alongLine(38.7);//35.7不够
  delay(500);
  turn(89.0,1);//89.3多了
  delay(500);
  
  adjust(delta);
  
  alongLine(76.4); 
  delay(3000);// 等着交互完  等A车先走一会会
  alongLine(28);//18不够
  delay(500);
  turn(89.6,1);//90多了
  
  delay(500);
  adjust(270+delta);
  alongLine(46.7);
  delay(5000);// 这里不确定delay几秒    跟在A的后面在中心路口等着



  alongLine(75);//让A先拐弯 150少
  adjust(270+delta);
  alongLine(80);
  delay(500);
  turn(90,0);
  delay(500);
  alongLine(27.9);
  delay(500);
  turn(90,0);
  delay(500);
  alongLine(30.1);
  delay(500);
  turn(180,0);
  delay(2000);// 在z车库的位置停两s
  adjust(delta);

  
  alongLine(29.1);//23.1少
  delay(500);
  turn(90,0);
  delay(500);
  alongWall(73);//70 后面的alongWall会左偏
  delay(500);
  turn(90,0);
  delay(500);
  alongWall(46.7);
  delay(100);
  alongLine(40);
  delay(500);  //经过岔路口 直接前进
  
  alongWall(55);
  delay(100);
  adjust(90+delta);
  alongLine(57);
 
  delay(500);
  turn(90,0);
  delay(500);
  alongWall(29.67);
  delay(1000);  //在医院门口停着 然后直接准备往B城返回了

  alongWall(85);
  delay(100);
  alongLine(90);
  delay(500);
  turn(90,0);
  delay(500);
  alongWall(57);
  delay(3000);//停在10的一半距离多一点点

  //*******************************第四阶段*******************************
  alongWall(44);//39.7多了
  delay(500);
  turn(90,0);
  delay(1000);// 等所有的车保持 整齐 &点阵屏
  adjust(delta);
  
  alongLine(73);//78.7
  delay(500);
  turn(45,1);
  delay(500);
  turn(45,0);
  delay(5000);
 */
}
