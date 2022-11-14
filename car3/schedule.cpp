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
    // step0
    if (c == 0x88)
    {
        setLightMode(6);
        open_flash('Y');
        open_flash('Y');
        open_flash('Y');
        alongLine(0, 0, 5000, 0);
        delay(500);
        setLightMode(4);

        open_flash('A');
        turn(90,1);
        delay(500);
        setLightMode(0);

        open_flash('T');
        alongLine(0, 0, 1200, 0);
        delay(500);
        setLightMode(4);

        open_flash('B');
        turn(90,0);
        
    }
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
    
    // step1 冰舞
    if (c == 0x90)
    {
      setLightMode(3);
      open_flash('G');
      open_flash('G');
      open_flash('G');
      open_flash('G');
      open_flash('G');
      alongLine(0,0,4000,0);
      
      setLightMode(4);
      open_flash('H');
      turn(90,0);
      open_flash('L');
      open_flash('L');
      turn(180,0);
      open_flash('L');
      open_flash('L');
      turn(180,0);
      
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
      alongLine(0,0,8000,0);
      
      setLightMode(4);
      open_flash('L');
      turn(90,0);
      
      setLightMode(6);
      open_flash('G');
      open_flash('G');
      open_flash('G');
      open_flash('G');
      open_flash('G');
      alongLine(0,0,4000,0);
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
      alongLine(0,3,3000,0);
      delay(800);
      
      setLightMode(2);
      open_flash('J');
      open_flash('J');
      open_flash('J');
      open_flash('J');
      open_flash('J');
      open_flash('J');
      alongLine(0,3,6000,1);
      delay(800);
      
      setLightMode(0);
      open_flash('J');
      open_flash('J');
      open_flash('J');
      open_flash('J');
      open_flash('J');
      open_flash('J');
      alongLine(0,3,6000,0);
      delay(800);
      
      setLightMode(2);
      open_flash('J');
      open_flash('J');
      open_flash('J');
      open_flash('J');
      alongLine(0,3,3000,1);
    }
    // step2.5
    if (c == 0x93)
    {
      open_flash('H');
      setLightMode(3);
      turn(90,0);

      setLightMode(2);
      open_flash('K');
      alongLine(0,0,1000,0);

      open_flash('K');
      setLightMode(4);
      turn(177,1);
      setLightMode(0);
    }
    // step3 冰壶
    if (c == 0x94)
    {
      open_flash('K');
      open_flash('K');
      delay(4000);
      
      setLightMode(6);
      open_flash('N');
      open_flash('N');
      alongLine(0,0,1500,0);
      setLightMode(0);
    }
    // step3.5
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
        turn(87, 0);
        setLightMode(0);
        /*setLightMode(1);
        turn(180, 0);
        setLightMode(0);*/
    }
    // step4 回位
    if (c == 0x96)
    {
      setLightMode(3);
      open_flash('R');
      open_flash('R');
      turn(160,1);
      
      setLightMode(2);
      open_flash('G');
      open_flash('G');
      open_flash('G');
      alongLine(0,0,3000,0);
      
      setLightMode(6);
      open_flash('L');
      open_flash('L');
      turn(160,0);
      setLightMode(0);
    }
    // step5 领奖
    if (c == 0x97)
    {
        setLightMode(5);
        open_flash('Q');
        open_flash('Q');
        open_flash('Q');
        alongLine(0, 0, 3000, 0);
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
      delay(500);
//      digitalWrite(mpin, HIGH);
//      flash(500, 1);
      standBy();
//      analogWrite(screwPin, 0);
    }

    if (c == 0x91){
      Serial.println("91");
      // 主车第一阶段动作
//      digitalWrite(mpin, HIGH);
//      flash(300, 1);
      delay(500);
      alongLine(500, 0);
//      digitalWrite(mpin, LOW);
      standBy();
    }


    if (c == 0x92){
      analogWrite(screwPin, 120);
      Serial.println("92");
//      digitalWrite(mpin, HIGH);
      // 主车第一阶段连接
      turn(180, 1);
      alongLine(500);
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
        alongLine(500);
        count ++;
      }
      else{
        initAngle_ = initAngle_ < 180 ? initAngle_ + 180 : initAngle_ - 180;
        alongLine(500, 0, initAngle_);
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
