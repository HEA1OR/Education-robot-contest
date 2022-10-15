#include "schedule.h"
#include "encoder&LED.h"

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
//  pinMode(screwPin, OUTPUT);
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

    // initial
    if (c == 0x90){
      Serial.println("90");
      setLightMode(1);
      getEncoder();
      initAngle_ = angle;
      close_flash();
      open_flash('B');
      turn(90, 1);
      turn(90, 1);
      turn(90, 1);
      turn(90, 1);
      setLightMode(0);
      delay(500);
      standBy();
    }

    // scene 1 - 1
    if (c == 0x91){
      Serial.println("91");
      setLightMode(1);
      open_flash('L');
      getEncoder();
      float angleTemp = angle;
      alongLine(900, 2, 9000);
      alongCurve(1430, 2, 90, 1, 12000);
//      alongCurve(300, -3, 75, 3, 3000);
//      alongLine(150, 1, 1500, angleTemp);
      
      standBy();
      setLightMode(0);
    }

    // scene 1 - 2
    if (c == 0x92){
      Serial.println("92");
//      turn(180, 1);
      turn(90, 0);
      standBy();
    }

    // scene 2 - 1
    if (c == 0x93){
      Serial.println("93");
      setLightMode(1);
      alongLine(350, 0, 3500);
      turn(90, 0);
      alongLine(330, 0, 3300);
      setLightMode(2);
      open_flash('B');
      delay(1000);
      open_flash('L');
      setLightMode(1);
      turn(90, 0);
      alongLine(200, 0, 2000, initAngle_);
      turn(90, 0);
      alongLine(350, 0, 3500);
      standBy();
      setLightMode(0);
    }

    // scene 3 - 1
    if (c == 0x94){
      Serial.println("94");
      turn(180, 1);
      standBy();
    }

    // scene 3 - 2
    if (c == 0x95){
      Serial.println("95");
      delay(500);
      standBy();
    }

    // scene 4 - 1
    if (c == 0x96){
      Serial.println("96");
      setLightMode(2);
      alongLine(600, 2, 6000);
      alongCurve(1400, -2.6, 170, 1, 13000);
      standBy();
      setLightMode(0);
      delay(500);
    }

    // scene 4 - 2
    if (c == 0x97){
      Serial.println("97");
      getEncoder();
      turn(85, 1);
      standBy();
      delay(500);
    }

    // scene 5 - 1
    if (c == 0x98){
      Serial.println("98");
      setLightMode(1);
      alongLine(650, 0, 6500);
      standBy();
      setLightMode(0);
      delay(500);
    }

    // scene 5 - 2
    if (c == 0x99){
      Serial.println("99");
      turn(180, 1);
      standBy();
      delay(500);
    }

    // scene 6 - 1
    if (c == 0xA0){
      Serial.println("A0");
      delay(5000);
      setLightMode(3);
      open_flash('H');
      alongLine(900, 0, 10000);
      standBy();
      setLightMode(0);
      delay(500);
    }

    // bonus
    if (c == 0xA1){
      Serial.println("A1");
      delay(500);
      turn(180, 1);
      turn(180, 1);
      setLightMode(2);
    }

      
    /*******************************完结撒花***********************************/

}
