#include<Servo.h>
Servo S;

void setup() {
  Serial.begin(9600);
  S.attach(13);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
}

void loop() {
  /******************空指令：开场白*******************/
  delay(6000);
  Serial.flush();
  Serial.write(0x90);
  Serial.flush();
  delay(5000);

  /*****************任务1：升旗+插队********************/
  Serial.flush(); //人字形，敬礼
  Serial.write(0xA1);
  Serial.flush();
  delay(4000);

  Serial.flush(); //奏国歌，delay时间待定
  Serial.write(0xA2);
  Serial.flush();
  
  S.writeMicroseconds(1660);
  delay(15000);
  S.writeMicroseconds(1500);
  delay(100);

  Serial.flush(); //预插队
  Serial.write(0xA3);
  Serial.flush();
  delay(4000);

  Serial.flush(); //插队
  Serial.write(0xA4);
  Serial.flush();
  delay(8000);

  /*****************任务2：区域巡逻********************/
  Serial.flush();
  Serial.write(0xB1);
  Serial.flush();
  delay(10000);

  Serial.flush();
  Serial.write(0xB2);
  Serial.flush();
  delay(7000);

  Serial.flush();
  Serial.write(0xB3);
  Serial.flush();
  delay(5000);

  /*****************任务3：边界巡逻********************/
  Serial.flush(); //中间转一圈，开始边界巡逻
  Serial.write(0xC1);
  Serial.flush();
  delay(4000);

  Serial.flush();
  Serial.write(0xC2);
  Serial.flush();
  delay(4000);

  Serial.flush();
  Serial.write(0xC3);
  Serial.flush();
  delay(5000);

  Serial.flush();
  Serial.write(0xC4);
  Serial.flush();
  delay(5000);

  Serial.flush();
  Serial.write(0xC5);
  Serial.flush();
  delay(10000);

  Serial.flush();
  Serial.write(0xC6);
  Serial.flush();
  delay(13000);

  /*****************任务4：汇报********************/
  Serial.flush();
  Serial.write(0xD1); //1东北
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xD2);
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xD3);
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xD4); //2东南
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xD5);
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xD6);
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xD7); //4西南
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xD8);
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xD9);
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xDA); //5西北
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xDB);
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xDC);
  Serial.flush();
  delay(3000);
  /*****************任务5：集合********************/
  Serial.flush();
  Serial.write(0xE1);
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xE2);
  Serial.flush();
  delay(5000);

  Serial.flush();
  Serial.write(0xE3);
  Serial.flush();
  delay(7000);

  Serial.flush();
  Serial.write(0xE4);
  Serial.flush();
  delay(5000);

  Serial.flush();
  Serial.write(0xE5);
  Serial.flush();
  delay(3000);

  Serial.flush();
  Serial.write(0xE6);
  Serial.flush();
  delay(15000);
}
