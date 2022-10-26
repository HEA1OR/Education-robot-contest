#include "schedule.h"
#include "encoderLED.h"

extern float angle;
volatile float count = 0;
float delta;
float initAngle_;

void schedule_init()
{
//  encoderInit();
//  motorInit();
//  ultrasonic_init();
//  compassInit();
//  xbee_init();
//  led_matrix_init();
  pinMode(screwPin, OUTPUT);
//  digitalWrite(ledpin, LOW); 
  pinMode(mpin, OUTPUT);
  digitalWrite(mpin, LOW); 
  close_flash();
//  open_flash('A');
  getEncoder();
  
  delta=angle-180;
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


    // step1
    if (c == 0x90)
    {
        open_flash('A');
        turn(180, 1);
        open_flash('B');
        turn(180, 1);
        open_flash('A');
        turn(180, 1);
        open_flash('B');
        turn(180, 1);
    }
    // step1.5
    // step2
    if (c == 0x92)
    {
        open_flash('C');
        alongLine(0, 0, 2000, 1);
        open_flash('D');
        alongLine(0, 0, 4000, 0);
        open_flash('C');
        alongLine(0, 0, 4000, 1);
        open_flash('D');
        alongLine(0, 0, 2000, 0);
    }
    // step2.5
    if (c == 0x93)
    {
        open_flash('E');
        turn(90, 1);
        alongLine(0, 0, 1000, 0);
        turn(180, 0);
    }
    // step3
    if (c == 0x94)
    {
        open_flash('F');
        alongLine(0, 0, 4000, 0);
        open_flash('E');

    }
    // step3.5
    if (c == 0x95)
    {
        open_flash('A');
        turn(180, 0);
        alongLine(0, 0, 1500, 0);
        turn(90, 1);
    }
    // step4
    if (c == 0x96)
    {
        open_flash('O');
        alongLine(0, 0, 4500, 0);
        delay(500);
    }

      
    /*******************************第一阶段***********************************/

}
