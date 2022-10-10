#include "schedule5.h"

extern float angle;

float delta;

void schedule_init()
{
  encoderInit();
  motorInit();
  ultrasonic_init();
  compassInit();
  xbee_init();
  led_matrix_init();
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW); 
  close_flash();
//  open_flash(charI);
  get_angle();
  delta = angle - 180;


//测试动作（2022/10/10 徐文江）

  alongLine(500);
}

void flash(int delayTime, int times)
{
  int i;
  for (i = 0; i < times; i++)
  {
    digitalWrite(ledpin, HIGH);
    delay(delayTime);
    digitalWrite(ledpin, LOW);
    delay(delayTime);  
  }
}
void schedule()
{
 /* volatile byte c = getCommand();
  if(c != 0xFF){
    Serial.print("收到信号: ");
    Serial.println(c);
  }
  command_execute(c);*/
  
}
// car5 社区车

void command_execute(byte c)
{
     // 目前用这个0x90作为调试信号，当car5接受到调试信号后，显示5

    //
    //if (c == 0x90){  
    //  turn(90,1);
    //  smoothTurn(90,1);
    //  turn(90,1);
    //  smoothTurn(90,1);
    //  standBy();
    //}
    // 

    //if (c == 0x91){
    //  // 右车第一阶段动作
    //  delay(3000);
    //  get_angle();
    //  volatile float lastAngle = angle;
    //  volatile float sumAngle = 0;
    //  volatile float coef = 1;
    //  float setAngle = angle;
    //  close_flash();
    //  open_flash('B');
    // 
    //  while(sumAngle < 45){
    //    if(sumAngle < 30)
    //      coef = 1 / (1 + 0.2 * exp(-(sumAngle / 10.0) * 1.5 + 3));
    //    get_angle();
    //    float tempAngle = angle - lastAngle;
    //    if(tempAngle < -180)
    //      tempAngle += 360;
    //    sumAngle += tempAngle;
    //    lastAngle = angle;
    //    walk(120 * coef, 50 * coef);
    //    delay(55);
    //  }
    //  alongLine(3500, 3);
    //  
    //  while(sumAngle > 0){
    //    get_angle();
    //    float tempAngle = lastAngle - angle;
    //    if(tempAngle < -180)
    //      tempAngle += 360;
    //    sumAngle -= tempAngle;
    //    lastAngle = angle;
    //    walk(55 * coef, 120 * coef);
    //    delay(55);
    //  }
    //  alongLine(10000, 1, setAngle);
    //  standBy();
    //}

    //
    //if (c == 0x92){
    //  // 右车第一阶段连接
    //  smoothTurn(90, 0);
    //  alongLine(10000);
    //  smoothTurn(90, 0);
    //  alongLine(4000);
    //  standBy();
    //}
   
    //if (c == 0x93){
    //  // 右车第二阶段动作
    //  circle(1);
    //  smoothTurn(90, 0);
    //  alongLine(10000);
    //  smoothTurn(90, 0);
    //  alongLine(10000);
    //  standBy();
    //}

    //
    //

    //if (c == 0x94){
    //  // 右车第二阶段连接
    //  smoothTurn(90, 0);
    //  standBy();
    //}

    //

    //if (c == 0x95){
    //  // 右车第三阶段动作
    //  delay(3000);
    //  alongLine(15000);
    //  standBy();
    //}

    //if (c == 0xFF){
    //  standBy();
    //}
      
}
