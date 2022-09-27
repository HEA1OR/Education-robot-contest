

#include "schedule5.h"
extern float angle;
extern float distance_cm;
extern float delta;
extern int countLeft, countRight;
void setup() {
   schedule_init();
   //motorInit();
   //encoderInit();
  Serial.begin(9600);
 
  
}

void loop() {
//walk(93,124);

//alongWall(300);
//delay(1000);
/*
Serial.println("距离");
Serial.println(countLeft);
Serial.println(countRight);
delay(50);
walk(100,0);// 500 550

*/
//walk(103,92);//120 168



schedule();

//alongLine(400);
//turn(90,0);
//delay(1000);

/*
 //**********第一阶段***********************
 delay(2000);
 alongLine(25);
 delay(500);
 turn(90,0);
 delay(500);
 alongLine(35);
 delay(500);
 turn(180.4,0); //180度不够 180.5多了
 delay(500);
 adjust(delta+90-1);

 
 alongLine(34);
 delay(500);
 turn(90.5,0);//因为直行会右偏，所以多转一点
 delay(500);
 
 adjust(180+1.5+delta);
 alongLine(67);
 delay(500);
 turn(90,0);
 delay(500);
 adjust(270+delta+1.7);
 alongWall(26);
 delay(1000);//说在每个车库门口都停一秒 同时 可以getangle 如果时间不够就不要了
 adjust(270+delta+2.2);
 alongLine(15);
 delay(1000);
 adjust(270+delta+2.5);
 alongLine(18);
 delay(1000);
 adjust(270+delta+2.5);
 alongLine(32);
 delay(500);
 turn(90,0);
 delay(500);
 alongWall(91);
 delay(500);
 turn(90.7,0);
 delay(500);
 adjust(90+1.5+delta);
 alongLine(95);
 delay(5000); // 直接进入圆心 社区车全部距离走完了
*/

}
