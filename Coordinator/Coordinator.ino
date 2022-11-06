#include<Servo.h>
Servo S;

void setup() {
  Serial.begin(9600);
  S.attach(13);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  delay(7000);
}

void loop() {

  // step 0
  Serial.flush();
  Serial.write(0x89);
  Serial.flush();
  Serial.println(89);
  delay(4000);
  
    // step 1
  Serial.flush();
  Serial.write(0x90);
  Serial.flush();
  Serial.println(90);
<<<<<<< HEAD
  delay(24000);
=======
  delay(21000);
>>>>>>> da50a07571e7aef7308c69cd90b0d571efeb6cc1

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
<<<<<<< HEAD
  delay(11000);
=======
  delay(5000);
>>>>>>> da50a07571e7aef7308c69cd90b0d571efeb6cc1

  // step3
  Serial.flush();
  Serial.write(0x94);
  Serial.flush();
<<<<<<< HEAD
  delay(15000);
=======
  delay(17000);
>>>>>>> da50a07571e7aef7308c69cd90b0d571efeb6cc1

  // step3.5
  Serial.flush();
  Serial.write(0x95);
  Serial.flush();
  delay(5000);

  // step 4
  Serial.flush();
  Serial.write(0x96);
  Serial.flush();
<<<<<<< HEAD
  delay(14000);

  // step 5
  Serial.flush();
  Serial.write(0x97);
  Serial.flush();
  delay(7000);

=======
  delay(7000);
>>>>>>> da50a07571e7aef7308c69cd90b0d571efeb6cc1

}
