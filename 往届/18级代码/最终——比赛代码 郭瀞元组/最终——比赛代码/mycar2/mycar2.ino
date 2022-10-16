 
#include "schedule2.h"

extern float distance_cm;
extern int countLeft, countRight;
extern float angle;
extern float delta;
void setup() {
  schedule_init();
  Serial.begin(9600);
}

void loop() {
 
/*
get_angle();

Serial.println("下面是角度");
Serial.println(angle);

delay(100);
*/
//alongLine(300);

  
schedule();


//alongWall(300);
//delay(500);


/*

//car2 救护车A
delay(3000);
  //*********************第一阶段*************************
  alongLine(84.5); //  比中心到中心少了6.7
  delay(1000); //所有点阵屏要在路口亮   这里有了delay 应该不用再多加delay了吧
  turn(90,1);
  delay(500);
  alongLine(53);
  delay(500);
  turn(180,1);
  delay(3000);
  adjust(270+delta);
  
  // *********************第二阶段********************************
  alongWall(36.5);//比中心到现在的位置少了10
  delay(5000); //等B到达路口 + 交互的时间
  alongLine(13.5);
  delay(500);
  turn(91,0);
  delay(500);
  adjust(delta);
  
  alongLine(80);
  delay(5000);//和私家车 进行交互的时间
  adjust(delta);
 
  alongLine(64.4);
  adjust(delta);
 
  alongLine(60);
  delay(500);
  turn(91,0);
  delay(500);
  alongWall(69.4);
  delay(500);
  turn(91,0);
  delay(500);
  alongLine(27);
  delay(500);
  turn(180,0);
  delay(2000);// 在x车库的位置停两s
  adjust(delta);
  alongLine(30);
  delay(500);
  turn(91,0);
  delay(500);
  alongWall(29.3);

  
  delay(500);
  turn(90,0);
  delay(500);
  alongWall(86.7);
  delay(500);  //经过岔路口 直接前进
  alongWall(119.7);
  delay(500);
  turn(91,0);
  delay(500);
  adjust(270+delta);
  alongLine(70);
  delay(500);
  turn(91.2,0);
  delay(500);
  alongLine(24.6);
  delay(500);
  turn(180,0);
  delay(3000);
  

  //******************第四阶段*************************
  adjust(180+delta);
  alongLine(26.6);
  delay(500);
  turn(91,0);
  delay(500);
  alongWall(36.1);
  delay(500);
  turn(91,0);
  delay(1000);// 留出1s给点阵屏
  adjust(delta);
  
  alongLine(83);
  delay(500);
   turn(45,1);
 delay(500);
 turn(45,0);
 delay(5000); 
 */

}
