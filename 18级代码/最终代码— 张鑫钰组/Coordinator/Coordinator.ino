#include<Servo.h>
Servo S;

void setup() {
  Serial.begin(9600);
  S.attach(13);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
}

void loop() {
   delay(7000);
   Serial.flush();
   Serial.write(0xD0);
   Serial.flush();
   delay(3500);
   
   Serial.flush();
   Serial.write(0xDA);
   Serial.flush();
   delay(5000);
   
   Serial.flush();
   Serial.write(0xD1);
   Serial.flush();
   delay(20000);
   delay(5000);
   Serial.flush();
   Serial.write(0xD2);
   Serial.flush();
   delay(8000);

   delay(6000);
   Serial.flush();
   Serial.write(0xD3);
   Serial.flush();
   delay(20000);

   delay(6000);
   Serial.flush();
   Serial.write(0xD4);
   Serial.flush();
   delay(35000);

   delay(10000);
   Serial.flush();
   Serial.write(0xD5);
   Serial.flush();
   delay(11000);

   delay(6000);
   Serial.flush();
   Serial.write(0xD6);
   Serial.flush();
   delay(16000);

   delay(6000);
   Serial.flush();
   Serial.write(0xD7);
   Serial.flush();
   delay(16500);

   Serial.flush();
   Serial.write(0xD8);
   Serial.flush();
   delay(15000);

  
}
