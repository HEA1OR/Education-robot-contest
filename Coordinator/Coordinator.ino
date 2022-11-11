#include<Servo.h>
Servo S;

void setup() {
  Serial.begin(9600);
  S.attach(13);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  delay(4000);
}

void loop() {

  Serial.flush();
  Serial.write(0x88);
  Serial.flush();
  Serial.println(88);
  delay(13000);
  
  // step 0
  Serial.flush();
  Serial.write(0x89);
  Serial.flush();
  Serial.println(89);
  delay(13000);
  
    // step 1   冰舞
  Serial.flush();
  Serial.write(0x90);
  Serial.flush();
  Serial.println(90);
  delay(28000);
  /*
  // step 1.5
  Serial.flush();
  Serial.write(0x91);
  Serial.flush();
  delay(7000);
  */
 // step 2.5  右移
  Serial.flush();
  Serial.write(0x93);
  Serial.flush();
  delay(17000);

  // step3  冰壶
  Serial.flush();
  Serial.write(0x94);
  Serial.flush();
  delay(17000);
  
  // step3.5 回正
  Serial.flush();
  Serial.write(0x95);
  Serial.flush();
  delay(10000);
  
  // step 2 滑雪
  Serial.flush();
  Serial.write(0x92);
  Serial.flush();
  delay(28000);

  // step 4 回位
  Serial.flush();
  Serial.write(0x96);
  Serial.flush();
  delay(14000);

  // step 5 颁奖
  Serial.flush();
  Serial.write(0x97);
  Serial.flush();
  delay(7000);


}
