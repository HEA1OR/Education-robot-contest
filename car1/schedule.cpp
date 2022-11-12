#include "schedule.h"
#include "encoderLED.h"

extern float angle;
volatile float count = 0;
float delta;
float initAngle_;
int command = 0;

void schedule_init()
{
  //  encoderInit();
  //  motorInit();
  //  ultrasonic_init();
  //  compassInit();
  //  xbee_init();
  led_matrix_init();
  pinMode(screwPin, OUTPUT);
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
// car1
void command_execute(byte c)
{

  //    Serial.print("c: ");
  //    Serial.println(c);
  if (c == 0x88)
  {
    setLightMode(6);
    open_flash('W');
    open_flash('W');
    open_flash('W');
    alongLine(0, 0, 5000, 0);
    delay(500);
    setLightMode(4);

    open_flash('A');
    turn(90, 0);
    delay(500);
    setLightMode(0);

    open_flash('T');
    alongLine(0, 0, 1200, 0);
    delay(500);
    setLightMode(4);

    open_flash('B');
    turn(90, 0);
  }
  // step0
  if (c == 0x89)
  {
    open_flash('R');
    open_flash('R');
    open_flash('R');
    open_flash('R');
    setLightMode(7);
    delay(3000);
  }

  // step1 冰舞
  if (c == 0x90)
  {
    setLightMode(3);
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 4000, 0);

    setLightMode(4);
    open_flash('H');
    turn(93, 0);
    delay(500);
    open_flash('L');
    open_flash('L');
    turn(180, 0);
    delay(500);
    open_flash('L');
    open_flash('L');
    turn(180, 0);
    delay(500);

    setLightMode(3);
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 8000, 0);

    setLightMode(4);
    open_flash('L');
    turn(93, 0);

    setLightMode(6);
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 4000, 0);
  }
  // step1.5
  if (c == 0x91)
  {
    setLightMode(1);
    open_flash('H');
  }
  // step2 滑雪
  if (c == 0x92)
  {
    setLightMode(0);
    open_flash('J');
    open_flash('J');
    open_flash('J');
    alongLine(0, 3, 3000, 0);
    delay(800);

    setLightMode(2);
    open_flash('J');
    open_flash('J');
    open_flash('J');
    open_flash('J');
    open_flash('J');
    open_flash('J');
    alongLine(0, 3, 6000, 1);
    delay(800);

    setLightMode(0);
    open_flash('J');
    open_flash('J');
    open_flash('J');
    open_flash('J');
    open_flash('J');
    open_flash('J');
    alongLine(0, 3, 6000, 0);
    delay(800);

    setLightMode(2);
    open_flash('J');
    open_flash('J');
    open_flash('J');
    open_flash('J');
    alongLine(0, 3, 3000, 1);
  }
  // step2.5
  if (c == 0x93)
  {

    open_flash('H');
    setLightMode(3);
    turn(93, 1);

    setLightMode(2);
    open_flash('K');
    alongLine(0, 0, 1000, 0);

    open_flash('K');
    setLightMode(4);
    turn(180, 1);
    setLightMode(0);
  }
  // step3  冰壶
  if (c == 0x94)
  {
    open_flash('M');
    open_flash('M');
    setLightMode(6);
    alongLine(0, 0, 2000, 0);
    setLightMode(0);
  }
  if (c == 0x95)
  {
    setLightMode(4);
    open_flash('A');
    open_flash('A');
    turn(180, 0);
    setLightMode(2);
    open_flash('L');
    alongLine(0, 0, 800, 0);
    setLightMode(3);
    open_flash('A');
    turn(90, 0);
    setLightMode(0);
  }
  /*if (c == 0x95)
    {
    open_flash('A');
    }*/
  // step4  回位
  if (c == 0x96)
  {
    open_flash('R');
    open_flash('R');
    setLightMode(3);
    turn(160, 0);

    open_flash('G');
    open_flash('G');
    open_flash('G');
    setLightMode(2);
    alongLine(0, 0, 3000, 0);

    setLightMode(6);
    open_flash('L');
    open_flash('L');
    turn(160, 1);
    setLightMode(0);
  }
  // step5  领奖
  if (c == 0x97)
  {
    setLightMode(5);
    open_flash('Q');
    open_flash('Q');
    open_flash('Q');
    alongLine(0, 0, 3000, 0);
  }

}
