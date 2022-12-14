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
 led_matrix_init();
  pinMode(screwPin, OUTPUT);
//  digitalWrite(ledpin, LOW); 
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
// car2
void command_execute(byte c)
{
     // 目前用这个0x90作为调试信号，当car5接受到调试信号后，显示5
//    Serial.print("c: ");
//    Serial.println(c);
    if (c == 0x88)
    {   
        setLightMode(6);
        open_flash('X');
        open_flash('X');
        open_flash('X');
        alongLine(0, 0, 5000, 0);
    }
    // step0
    if (c == 0x89)
    {
        open_flash('R');
        open_flash('R');
        open_flash('R');
        open_flash('R');
        open_flash('R');
        open_flash('R');
        open_flash('R');
        open_flash('R');
        setLightMode(7);
        delay(3000);
    }

    // step1  冰舞
    if (c == 0x90)
    {
        setLightMode(6);
        open_flash('A');
        open_flash('B');
        turn(180, 1);
        open_flash('B');
        open_flash('A');
        turn(180, 1);
        delay(500);
        open_flash('A');
        open_flash('B');
        turn(180, 1);
        open_flash('B');
        open_flash('A');
        turn(180, 1);
        delay(500);
        
        open_flash('A');
        open_flash('B');
        turn(180, 0);
        open_flash('B');
        open_flash('A');
        turn(180, 0);
        delay(500);
        open_flash('A');
        open_flash('B');
        turn(180, 0);
        open_flash('B');
        open_flash('A');
        turn(180, 0);
        setLightMode(0);
    }
    // step1.5
    if (c == 0x91)
    {
      setLightMode(3);
      open_flash('A');
      open_flash('A');
      turn(180, 0);
    }
    // step2  滑雪
    if (c == 0x92)
    {
        setLightMode(6);
        open_flash('C');
        open_flash('C');
        open_flash('C');
        alongLine(0, 3, 3000, 1);
        delay(800);
        
        open_flash('D');
        open_flash('D');
        open_flash('D');
        open_flash('D');
        open_flash('D');
        open_flash('D');
        alongLine(0, 3, 6000, 0);
        delay(800);
        
        open_flash('C');
        open_flash('C');
        open_flash('C');
        open_flash('C');
        open_flash('C');
        open_flash('C');
        alongLine(0, 3, 6000, 1);
        delay(800);
        
        open_flash('D');
        open_flash('D');
        open_flash('D');
        alongLine(0, 3, 3000, 0);
        delay(800);
        setLightMode(0);
    }
    // step2.5  右移
    if (c == 0x93)
    {
        setLightMode(4);
        open_flash('H');
        turn(90, 1);
        open_flash('E');
        setLightMode(2);
        alongLine(0, 0, 2500, 0);
        setLightMode(3);

        turn(180, 1);
        setLightMode(0);
    }
    // step3  冰壶
    if (c == 0x94)
    {
        open_flash('F');
        open_flash('F');
        open_flash('F');
        open_flash('F');
        setLightMode(2);
        alongLine(0, 0, 3500, 0);
        open_flash('E');
        setLightMode(0);
    }
    // step3.5  回正
    if (c == 0x95)
    {
        setLightMode(4);
        open_flash('H');
        open_flash('H');
        turn(180, 0);
        setLightMode(2);
        open_flash('L');
        alongLine(0, 0, 800, 0);
        setLightMode(3);
        open_flash('A');
        turn(90, 0);
        setLightMode(0);
    }
    // step4  回位
    if (c == 0x96)
    {
        open_flash('A');
        open_flash('A');
        setLightMode(6);
        turn(180,0);
        open_flash('G');
        open_flash('G');
        open_flash('G');
        setLightMode(2);
        alongLine(0, 0, 2700, 0);
        setLightMode(6);
        open_flash('A');
        open_flash('A');
        turn(180, 0);
        setLightMode(0);
    }
    // step5  颁奖
    if (c == 0x97)
    {
        setLightMode(5);
        open_flash('O');
        open_flash('O');
        open_flash('O');
        alongLine(0, 0, 3500, 0);
    }

}
