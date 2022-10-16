#include "schedule.h"
#include "encoder&LED.h"

extern float angle;
volatile float count = 0;
float delta;
float initAngle_;
byte last_c = 255;
volatile int number = 0;

void schedule_init()
{
  //  encoderInit();
  //  motorInit();
  //  ultrasonic_init();
  //  compassInit();
  //  xbee_init();
  //  led_matrix_init();
  //  pinMode(screwPin, OUTPUT);
  //  digitalWrite(ledpin, LOW);
  pinMode(mpin, OUTPUT);
  digitalWrite(mpin, LOW);
  close_flash();
  //  open_flash('A');
  getEncoder();

  delta = angle - 180;
}

//void flash(int delayTime, int times)
//{
//  int i;
//  for (i = 0; i < times; i++)
//  {
//    digitalWrite(ledpin, HIGH);
//    Serial.println("high");
//    delay(delayTime);
//    digitalWrite(ledpin, LOW);
//    Serial.println("Low");
//    delay(delayTime);
//  }
//}
void schedule()
{
  byte c = getCommand();
  command_execute(c);
}
// car5 社区车
void command_execute(byte c)
{
  // 目前用这个0x90作为调试信号，当car5接受到调试信号后，显示5
  Serial.print("c: ");
  Serial.println(c);

  // initial
  if (c == 0x90) {
    number = 1;
    Serial.println("90");
    setLightMode(2);
    getEncoder();
    initAngle_ = angle;
    close_flash();
    open_flash('B');
//    turn(90, 1);
//    turn(90, 0);
//    turn(90, 0);
//    turn(90, 1);
    delay(3000);
    setLightMode(0);
    delay(500);
    standBy();
  }

  // scene 1 - 1
  if (c == 0x91 && number == 1) {
    Serial.println("91");
    number ++;
    setLightMode(1);
    open_flash('L');
    getEncoder();
    float angleTemp = angle - 90 < 0 ? angle + 270 : angle - 90;
    alongLine(100, 0, 8000);
    turn(90, 1);
    alongLine(900, 0, 10000, angleTemp);
    //      alongCurve(1400, -2, 50, 0, 14000);
    //      alongCurve(300, 3, 75, 3, 3000);
    //      alongLine(150, 1, 1500, angleTemp);
    standBy();
    setLightMode(0);
  }

  // scene 1 - 2
  if (c == 0x92 && number == 2) {
    Serial.println("92");
    number ++;
    //      turn(180, 1);
    turn(90, 1);
    standBy();
  }

  // scene 2 - 1
  if (c == 0x93 && number == 3) {
    Serial.println("93");
    number ++;
    setLightMode(1);
    delay(2000);
    float angleTemp = initAngle_ - 180 < 0 ? initAngle_ + 180 : initAngle_ - 180;
    alongLine(150, 0, 1500, angleTemp);
    turn(90, 1);
    alongLine(330, 0, 3300);
    setLightMode(2);
    open_flash('B');
    delay(1000);
    open_flash('L');
    setLightMode(1);
    turn(90, 0);
    alongLine(200, 0, 2000);
    turn(90, 0);
    alongLine(300, 0, 3000, initAngle_ - 90);
    standBy();
    setLightMode(0);
  }

  // scene 2 - 2
  if (c == 0x94 && number == 4) {
    Serial.println("94");
    number ++;
    turn(180, 1);
    standBy();
  }

  // scene 3 - 1
  if (c == 0x95 && number == 5) {
    Serial.println("95");
    number ++;
    setLightMode(2);
    alongLine(600, 0, 6000);
//    alongCurve(1400, -2.6, 176, 1, 13500);
    turn(90, 1);
    alongLine(400, 0, 4000);
    turn(90, 1);
    alongLine(600, 0, 6000);
    standBy();
    setLightMode(0);
    delay(500);
  }

  // scene 4 - 1
  if (c == 0x96 && number == 6) {
    Serial.println("96");
    number ++;
    turn(90, 1);
    delay(500);
    standBy();
  }

  // scene 4 - 2
  if (c == 0x97 && number == 7) {
    Serial.println("97");
    number ++;
    getEncoder();
//    turn(90, 0);
    alongLine(200, 0, 2500);
    standBy();
    delay(500);
  }

  // scene 5 - 1
  if (c == 0x98 && number == 8) {
    Serial.println("98");
    number ++;
    setLightMode(1);
    alongLine(350, 0, 3500);
    standBy();
    setLightMode(0);
    delay(500);
  }

  // scene 5 - 2
  if (c == 0x99 && number == 9) {
    Serial.println("99");
    number ++;
    turn(180, 1);
    standBy();
    delay(500);
  }

  // scene 6 - 1
  if (c == 0xA0 && number == 10) {
    Serial.println("A0");
    number ++;
    delay(5000);
    setLightMode(3);
    open_flash('H');
    alongLine(900, 0, 10000);
    standBy();
    setLightMode(0);
    delay(500);
  }

  // bonus
  if (c == 0xA1 && number == 11) {
    Serial.println("A1");
    number ++;
    delay(500);
    turn(180, 1);
    turn(180, 1);
    setLightMode(2);
  }

  last_c = c;

  /*******************************完结撒花***********************************/

}
