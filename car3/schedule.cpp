#include "schedule.h"
#include "encoderLED.h"

extern float angle;
volatile float count = 0;
float delta;
float initAngle_, subangle;
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
  initAngle_ = angle;
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
    setLightMode(1);
    open_flash('A');
    open_flash('A');
    open_flash('A');
    alongLine(0, 0, 3600, 0);
  }
  // step2  花滑
  if (c == 0x89)
  {
    setLightMode(6);
    getEncoder();
    float tempangle = angle;
    delay(6500);
    for (int i=1;i<=10;i++)
    {
      open_flash('A');
      turn(89, 0);
      delay(200);
    }

    turn(90, 0);
    delay(200);
    turn(90, 0);
    delay(200);
    /*
    getEncoder();
    float subangle = angle - tempangle;
    if (subangle < -90)
        subangle += 360;
    else if (subangle > 90)
        subangle -= 360;
    if(subangle>0.4)
    {
      turn(subangle ,1);
      }
    else if(subangle<-0.4)
    {
      turn(fabs(subangle),0);
      }*/
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
    setLightMode(1);
    delay(1000);
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 2700, 0);
    delay(200);
    open_flash('A');
    turn(89, 0);
    delay(200);
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 2800, 0);
    delay(200);
    open_flash('A');
    turn(180, 1);
    delay(200);
  }
  // step4 冰壶
  if (c == 0x91)
  {
    open_flash('D');
    open_flash('D');
    open_flash('D');
    open_flash('D');
    setLightMode(0);
    alongLine(0, 0, 4000, 0);
    setLightMode(1);
    delay(200);
  }
  // step5 冰壶to冰球
  if (c == 0x92)
  {
    setLightMode(1);
    open_flash('H');
    turn(90, 0);
    delay(200);
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 2200, 0);
    delay(200);
    open_flash('H');
    turn(89, 0);
    delay(200);
    open_flash('G');
    open_flash('G');
    open_flash('G');
    open_flash('G');
    alongLine(0, 0, 4300, 0);
    delay(200);
    open_flash('M');
    turn(180, 1);
  }
  // step6 冰球-car3不动
  if (c == 0x93)
  {
    setLightMode(0);
    delay(1000);
  }
  // step7 冰球-car3直行接球
  if (c == 0x94)
  {
    delay(3000);
    open_flash('M');
    open_flash('M');

    alongLine(0, 0, 2700, 0);
    delay(200);
  }
  // step8 冰球-car3直行
  if (c == 0x95)
  {
    //delay(1000);
    open_flash('M');
    open_flash('M');
    open_flash('M');
    open_flash('I');
    alongLine(0, 0, 3000, 0);
    delay(200);
  }
  // step9 冰球to颁奖
  if (c == 0x96)
  {
    setLightMode(6);
    open_flash('A');
    turn(90, 1);
    delay(3000);
    open_flash('H');
    open_flash('H');
    open_flash('H');
    open_flash('H');
    open_flash('H');
    alongLine(0, 0, 5400, 0);
    delay(200);
    open_flash('A');
    turn(178, 1);
    delay(200);
    /*
    getEncoder();
    subangle = angle - initAngle_;
    if (subangle < -300)
        subangle += 360;
    else if (subangle > 300)
        subangle -= 360;
    if(subangle>0.4)
    {
      turn(subangle ,1);
      }
    else if(subangle<-0.4)
    {
      turn(fabs(subangle),0);
      }*/
    /*
    turn(180, 1);
    delay(200);
    alongLine(0, 0, 3800, 0);
    delay(200);
    turn(89, 0);
    delay(200);
    alongLine(0, 0, 8500, 0);
    delay(200);
    turn(178, 1);
    delay(200);
    getEncoder();
    subangle = angle - initAngle_;
    if (subangle < -300)
        subangle += 360;
    else if (subangle > 300)
        subangle -= 360;
    if(subangle>0.4)
    {
      turn(subangle ,1);
      }
    else if(subangle<-0.4)
    {
      turn(fabs(subangle),0);
      }*/
  }
  /*if (c == 0x95)
    {
    open_flash('A');
    }*/
  // step10 颁奖
  if (c == 0x97)
  {
    open_flash('W');
    open_flash('W');
    delay(1000);
    open_flash('Q');
    open_flash('Q');
    delay(2000);
    
    setLightMode(7);
    //alongLine(0, 0, 3000, 0);
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
