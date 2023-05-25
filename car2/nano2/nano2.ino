#include <SPI.h>
#include "JY901.h"
#include "Adafruit_NeoPixel.h"    //引入头文件
#include <Servo.h>            // 调用Servo库

#define LED_COUNT 26     //定义LED灯个数
#define ADD true
#define SUB false
#define nanoModePin0 3
#define nanoModePin1 4     // 译码法选择灯带显示模式
#define motorPIN 5     // 舵机引脚
#define flag1 6
#define flag2 7
#define flag3 8
#define flag4 9

Servo myservo;             // 定义Servo对象来控制
int flag = 0;
int mode = 0;
void setnanoMode();
void rise();
void down();
void servo();
void servo2();

void setup(void)
{
  pinMode(nanoModePin0, INPUT);
  pinMode(nanoModePin1, INPUT);
  pinMode(flag1, OUTPUT);
  pinMode(flag2, OUTPUT);
  pinMode(flag3, OUTPUT);
  pinMode(flag4, OUTPUT);
  myservo.attach(motorPIN);
}
void loop(void)
{
  setnanoMode();
  if (mode == 0)
  {
    myservo.writeMicroseconds(1480);
    if (flag == 1)
    {
      flag = 0;
      down();
    }
  }
  else if (mode == 1)
  {
    // servo2();       //小角度摇晃
    if (flag == 1)
    {
      flag = 0;
      down();
    }
    myservo.writeMicroseconds(1540);
  }
  else if (mode == 2)
  { // servo();    // 大角度摇晃
    if (flag == 1)
    {
      flag = 0;
      down();
    }
    myservo.writeMicroseconds(1580);
  }
  else if (mode == 3)
  {
    myservo.writeMicroseconds(1550);
    if (flag == 0)
    {
      rise();
      flag = 1;
    }
  }
}

void setnanoMode(){
  int a = digitalRead(nanoModePin0);
  int b = digitalRead(nanoModePin1);
  if(a == 0 && b == 0)
    mode = 0;
  else if(a == 1 && b == 0)
    mode = 1;
  else if(a == 0 && b == 1)
    mode = 2;
  else if(a == 1 && b == 1)
    mode = 3;
}


void rise(){         // 升旗仪式

    for (int i = 0; i < 700; i++)
  {
    digitalWrite(flag1, LOW);
    digitalWrite(flag2, LOW);
    digitalWrite(flag3, HIGH);
    digitalWrite(flag4, LOW);
    delay(3);

    digitalWrite(flag1, HIGH);
    digitalWrite(flag2, LOW);
    digitalWrite(flag3, HIGH);
    digitalWrite(flag4, LOW);
    delay(3);

    digitalWrite(flag1, HIGH);
    digitalWrite(flag2, LOW);
    digitalWrite(flag3, LOW);
    digitalWrite(flag4, LOW);
    delay(3);

    digitalWrite(flag1, HIGH);
    digitalWrite(flag2, LOW);
    digitalWrite(flag3, LOW);
    digitalWrite(flag4, HIGH);
    delay(3);

    digitalWrite(flag1, LOW);
    digitalWrite(flag2, LOW);
    digitalWrite(flag3, LOW);
    digitalWrite(flag4, HIGH);
    delay(3);

    digitalWrite(flag1, LOW);
    digitalWrite(flag2, HIGH);
    digitalWrite(flag3, LOW);
    digitalWrite(flag4, HIGH);
    delay(3);

    digitalWrite(flag1, LOW);
    digitalWrite(flag2, HIGH);
    digitalWrite(flag3, LOW);
    digitalWrite(flag4, LOW);
    delay(3);

    digitalWrite(flag1, LOW);
    digitalWrite(flag2, HIGH);
    digitalWrite(flag3, HIGH);
    digitalWrite(flag4, LOW);
    delay(3);
  }
}

void down(){
  for (int i = 0; i < 700; i++)
  {

    digitalWrite(flag1, LOW);
    digitalWrite(flag2, HIGH);
    digitalWrite(flag3, HIGH);
    digitalWrite(flag4, LOW);
    delay(2);

    digitalWrite(flag1, LOW);
    digitalWrite(flag2, HIGH);
    digitalWrite(flag3, LOW);
    digitalWrite(flag4, LOW);
    delay(2);

    digitalWrite(flag1, LOW);
    digitalWrite(flag2, HIGH);
    digitalWrite(flag3, LOW);
    digitalWrite(flag4, HIGH);
    delay(2);

    digitalWrite(flag1, LOW);
    digitalWrite(flag2, LOW);
    digitalWrite(flag3, LOW);
    digitalWrite(flag4, HIGH);
    delay(2);

    digitalWrite(flag1, HIGH);
    digitalWrite(flag2, LOW);
    digitalWrite(flag3, LOW);
    digitalWrite(flag4, HIGH);
    delay(2);

    digitalWrite(flag1, HIGH);
    digitalWrite(flag2, LOW);
    digitalWrite(flag3, LOW);
    digitalWrite(flag4, LOW);
    delay(2);

    digitalWrite(flag1, HIGH);
    digitalWrite(flag2, LOW);
    digitalWrite(flag3, HIGH);
    digitalWrite(flag4, LOW);
    delay(2);

    digitalWrite(flag1, LOW);
    digitalWrite(flag2, LOW);
    digitalWrite(flag3, HIGH);
    digitalWrite(flag4, LOW);
    delay(2);
  }
}

void servo(){
    myservo.writeMicroseconds(1430); // 舵机顺时针旋转
    delay(2000);
    myservo.writeMicroseconds(1574); // 舵机逆时针旋转
    delay(2000);
    /*可以修改myservo.writeMicroseconds(1500); 中的值控制舵机，1500时控制舵机停止旋转。
500~1500控制顺时针旋转，值越小，旋转速度越大
1500~2500控制逆时针旋转，值越大，旋转速度越大
*/
}

void servo2(){
    myservo.writeMicroseconds(1455); // 舵机顺时针旋转
    delay(200);
    myservo.writeMicroseconds(1550); // 舵机逆时针旋转
    delay(200);
}
