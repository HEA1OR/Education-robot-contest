#include <Servo.h>            // 调用Servo库

Servo myservo;             // 定义Servo对象来控制
int pos=0;    
int potPin = 9;
void rise(){
  int val = digitalRead(potPin);
  if(val){
     for (pos = 0; pos <= 160; pos ++) {   // 0°到160°
    // in steps of 1 degree
    myservo.write(pos);               // 舵机角度写入
    delay(5);                         // 控制移动速度
  }
  for (pos = 160; pos >= 0; pos --) {   // 从160°到0°
    myservo.write(pos);               // 舵机角度写入
    delay(5);                         // 控制移动速度
  }
    }
  }
void setup(){
  myservo.attach(10);          // 控制线连接数字10
}

void loop(){
  digitalWrite(potPin, HIGH); //将舵机接口电平置高
  delay(1000);
 //rise();
 digitalWrite(potPin, LOW); //将舵机接口电平置高
 delay(3000);
 //rise();
}
