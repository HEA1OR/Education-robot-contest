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
  // step1  入场
  Serial.flush();
  Serial.write(0x88);
  Serial.flush();
  Serial.println(88);
  delay(12000);
  
  // step2  花滑
  Serial.flush();
  Serial.write(0x89);
  Serial.flush();
  Serial.println(89);
  delay(54000);
  
  // step3 花滑to冰壶
  Serial.flush();
  Serial.write(0x90);
  Serial.flush();
  Serial.println(90);
  delay(20000);
  
  // step4 冰壶
  Serial.flush();
  Serial.write(0x91);
  Serial.flush();
  delay(13000);

  // step5 冰壶to冰球
  Serial.flush();
  Serial.write(0x92);
  Serial.flush();
  delay(25000);

  // step6 冰球1
  Serial.flush();
  Serial.write(0x93);
  Serial.flush();
  delay(12000);
  
  // step7 冰球2
  Serial.flush();
  Serial.write(0x94);
  Serial.flush();
  delay(13000);
  
  // step8 冰球
  Serial.flush();
  Serial.write(0x95);
  Serial.flush();
  delay(18000);

  // step9 冰球to颁奖
  Serial.flush();
  Serial.write(0x96);
  Serial.flush();
  delay(30000);

  // step 5 颁奖
  Serial.flush();
  Serial.write(0x97);
  Serial.flush();
  delay(70000);


}
