#include "schedule1.h"
extern float angle;
extern float delta;
extern float distance_cm;
extern int countLeft, countRight;  //encoder
void setup() {
 
 schedule_init();
 //motorInit();
 //encoderInit();
  Serial.begin(9600);
  
}

void loop() {

//Serial.println("距离");
//Serial.println(countLeft);
//Serial.println(countRight);
//delay(50);
//walk(100,100);// 500 550

//alongWall(300);
schedule();

//turn(90,0);
//delay(1000);
//turn(90,1);
//delay(1000);

//alongLine(300);
  
 /*
// car1 私家车

  //*********************第一阶段*************************
  delay(3000);
  alongLine(70);//72
  delay(1000);//所有点阵屏要在路口亮   这里有了delay 应该不用再多加delay了吧
  turn(90,0);
  delay(500);
  alongWall(48.5);//48.4多了
  delay(500);
  
  turn(89.2,0);//90
  
  delay(500);
  alongLine(29.2);
  delay(500);
  turn(179,0);// 180
  delay(3000);
  adjust(180+delta);
  
  //********************第二阶段*************************
  alongLine(29.2);
  delay(500);
  turn(89.7,1);
  delay(500);
  
  adjust(90+delta);
  
  alongLine(48.5);
  delay(500);
  turn(89.5,1);
  delay(500);
  adjust(delta);
  alongLine(70);//78
  delay(8000);// 在中心岔路口等救护车AB过来  并且完成交互

    
    alongLine(20.7);//10.7
    delay(500);
    turn(89.5,1);//90
    delay(500);
    adjust(270+delta);
    alongLine(46.7);
    adjust(270+delta);
    alongLine(50);
    delay(500);
    turn(90,0);
    delay(500);
    //下面两个是医院处的alongwall
    alongWall(97.7);//89.7
    delay(500);
    turn(90,0);
    delay(500);
    
    alongWall(31.7);
    delay(3000);


    //*******************第三阶段***********************
    adjust(90+delta);
    alongLine(65);//60 多了
    delay(500);
    turn(90,0);//90 转多了
    delay(500);
    adjust(180+delta);
    alongLine(73);//80
    
    delay(5000); //在中间岔路口与政府车交互
    adjust(180+delta);
    alongLine(52.4);
    adjust(180+delta);
    alongLine(60);
    delay(500);
    turn(89.5,0);//90 多了
    delay(500);
    alongWall(48.3);//45.4多了  42.4 不够到达车库2
    delay(500);
    turn(90,0);
    delay(500);
    alongLine(29.2);
    delay(500);
    turn(180,0);
    delay(3000);
    adjust(180+delta);

//**************************第四阶段*****************************
 
   alongLine(32.8);//26.2 还不够
  delay(500);
  turn(90,1);
  delay(500);
  adjust(90+delta);
  alongLine(48.3);//45.4
  delay(500);
  turn(89.4,1);//90
  delay(1000);// 点阵屏在这里停1s
  adjust(delta);
  alongLine(73); //80 太多了
  delay(500);
 //停在初始位置后，所有车都会向右偏45再回偏
 turn(45,1);
 delay(500);
 turn(45,0);
 delay(5000); 
*/ 
}
