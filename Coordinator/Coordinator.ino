#include<Servo.h>
Servo S;

void setup() {
  Serial.begin(9600);
  S.attach(13);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  delay(3000);
}

void loop() {
  
  // step 1
  Serial.flush();
  Serial.write(0x90);
  Serial.flush();
  Serial.println(90);
  delay(20000);

  // step 1.5
  Serial.flush();
  Serial.write(0x91);
  Serial.flush();
  delay(3000);

  // step 2
  Serial.flush();
  Serial.write(0x92);
  Serial.flush();
  delay(18000);

  // step 2.5
  Serial.flush();
  Serial.write(0x93);
  Serial.flush();
  delay(8000);

  // step3
  Serial.flush();
  Serial.write(0x94);
  Serial.flush();
  delay(8000);

  // step3.5
  Serial.flush();
  Serial.write(0x95);
  Serial.flush();
  delay(7000);

  // step 4
  Serial.flush();
  Serial.write(0x96);
  Serial.flush();
  delay(4000);

}
