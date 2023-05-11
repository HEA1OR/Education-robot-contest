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
// car3
void command_execute(byte c)
{

    //Serial.print("c: ");
    //Serial.println(c);
  // step1  入场
  if (c == 0x88)
  {
    alongLine(0, 0, 4000, 0);
  }
  // step2  花滑
  if (c == 0x89)
  {
    for (int i=1;i<=12;i++)
    {
      turn(90, 0);
      delay(200);
    }
    /*
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    delay(200);
    turn(180, 1);
    */
  }

  // step3 花滑to冰壶
  if (c == 0x90)
  {
    alongLine(0, 0, 1000, 0);
    delay(200);
    turn(92, 0);
    delay(200);
    alongLine(0, 0, 2200, 0);
    delay(200);
    turn(177, 1);
    delay(200);
  }
  // step4 冰壶
  if (c == 0x91)
  {
    alongLine(0, 0, 4000, 0);
    delay(200);
  }
  // step5 冰壶to冰球
  if (c == 0x92)
  {
    turn(90.5, 0);
    delay(200);
    alongLine(0, 0, 3000, 0);
    delay(200);
    turn(90.5, 0);
    delay(200);
    alongLine(0, 0, 4200, 0);
    delay(200);
    turn(177, 1);
  }
  // step6 冰球-car3不动
  if (c == 0x93)
  {
    delay(1000);
  }
  // step7 冰球-car3直行接球
  if (c == 0x94)
  {
    alongLine(0, 0, 3200, 0);
    delay(200);
  }
  // step8 冰球-car3直行
  if (c == 0x95)
  {
    alongLine(0, 0, 1200, 0);
    delay(200);
  }
  // step9 冰球to颁奖
  if (c == 0x96)
  {
    turn(177, 1);
    delay(200);
    alongLine(0, 0, 2000, 0);
    delay(200);
    turn(90.5, 0);
    delay(200);
    alongLine(0, 0, 6000, 0);
    delay(200);
    turn(177, 1);
    delay(200);
  }
  /*if (c == 0x95)
    {
    open_flash('A');
    }*/
  // step10 颁奖
  if (c == 0x97)
  {
    alongLine(0, 0, 3000, 0);
    delay(200);
    /* 
     *  =============
     *  摇旗
     *  =============
     */
  }
    // 目前用这个0x90作为调试信号，当car5接受到调试信号后，显示5
    /*
    if (c == 0x90){
      analogWrite(screwPin, 120);
      Serial.println("90");
      getEncoder();
      initAngle_ = angle;
      close_flash();
      open_flash('x');
      turn(90, 1);
      turn(90, 1);
      turn(90, 1);
      turn(90, 1);
      setLightMode(1);
      //
      delay(200);
//      digitalWrite(mpin, HIGH);
//      flash(200, 1);
      standBy();
//      analogWrite(screwPin, 0);
    }

    if (c == 0x91){
      Serial.println("91");
      // 主车第一阶段动作
//      digitalWrite(mpin, HIGH);
//      flash(300, 1);
      delay(200);
      alongLine(200, 0);
//      digitalWrite(mpin, LOW);
      standBy();
    }


    if (c == 0x92){
      analogWrite(screwPin, 120);
      Serial.println("92");
//      digitalWrite(mpin, HIGH);
      // 主车第一阶段连接
      turn(180, 1);
      alongLine(200);
//      digitalWrite(mpin, LOW);
      standBy();
    }

    if (c == 0x93){
      Serial.println("93");
      // 主车第二阶段动作
//      digitalWrite(mpin, HIGH);
      getEncoder();
      float angleTemp = angle;
      open_flash('i');
      setLightMode(0);
      delay(1800);
//      alongLine(10000, 0, angleTemp);
//      digitalWrite(mpin, LOW); 
      standBy();
    }

    if (c == 0x94){
      Serial.println("94");
      // 主车第二阶段连接
//      digitalWrite(mpin, HIGH);
      open_flash('A');
      turn(180, 1);
//      digitalWrite(mpin, LOW);
      standBy();
      analogWrite(screwPin, 0);
    }

    if (c == 0x95){
      Serial.println("95");
      // 主车第三阶段动作
//      digitalWrite(mpin, HIGH);
      open_flash('a');
      if(count == 0){
        alongLine(200);
        count ++;
      }
      else{
        initAngle_ = initAngle_ < 180 ? initAngle_ + 180 : initAngle_ - 180;
        alongLine(200, 0, initAngle_);
      }
//      flash(300, 1);
//      digitalWrite(mpin, LOW);
      standBy();
    }

    if (c == 0x96){
//      digitalWrite(mpin, HIGH);
      open_flash('A');
      alongLine(300);
//      digitalWrite(mpin, LOW);
    }

    if (c == 0x97){
//      digitalWrite(mpin, HIGH);
      turn(180, 1);
//      digitalWrite(mpin, LOW);
    }
*/
      
    /*******************************第一阶段***********************************/

}
