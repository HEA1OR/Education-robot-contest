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
  delay(21000);

  // step 1.5
  Serial.flush();
  Serial.write(0x91);
  Serial.flush();
  delay(7000);

  // step 2
  Serial.flush();
  Serial.write(0x92);
  Serial.flush();
  delay(25000);

  // step 2.5
  Serial.flush();
  Serial.write(0x93);
  Serial.flush();
  delay(5000);

  // step3
  Serial.flush();
  Serial.write(0x94);
  Serial.flush();
  delay(17000);

  // step3.5
  Serial.flush();
  Serial.write(0x95);
  Serial.flush();
  delay(5000);

  // step 4
  Serial.flush();
  Serial.write(0x96);
  Serial.flush();
  delay(7000);

}
