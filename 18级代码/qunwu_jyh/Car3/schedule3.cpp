#include "schedule3.h"

void schedule_init()
{
  encoderInit();
  motorInit();
  ultrasonic_init();
  compassInit();
  xbee_init();
  led_matrix_init();
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, HIGH); //3号车HIGH是灯灭
  close_flash();
  open_flash(charI);
}

void flash(int delayTime, int times)
{
  int i;
  for (i = 0; i < times; i++)
  {
    digitalWrite(ledpin, LOW);
    delay(delayTime);
    digitalWrite(ledpin, HIGH);
    delay(delayTime);  
  }
}
void schedule()
{
  byte c = getCommand();
  command_execute(c);
}

void command_execute(byte c)
{
  switch (c)
  {
    /*************************调试代码***********************************/
    case 0xFF:
      standBy();
      break;
    case 0x90:
      standBy();
      break;
    /*******************************任务1***********************************/
    case 0xA1:
      alongLine(42);
      standBy();
      break;
    case 0xA2:
      close_flash();
      open_flash(CHINA);
      standBy();
      break;
    case 0xA3:
      close_flash();
      open_flash(escortFlash);
      standBy();
      break;
    case 0xA4:
      alongLine(12);
      adjust(180);
      break;
    /************************任务2***********************************/
    case 0xB1:
      close_flash();
      open_flash(areaPatrol);
      standBy();
      break;
    case 0xB2:
      standBy();
      break;
    case 0xB3:
      standBy();
      break;
    /************************任务3***********************************/
    case 0xC1:
      close_flash();
      open_flash(patrolFlash);
      turn(180, right);
      turn(180, right);
      adjust(180);
      break;
    case 0xC2:
      standBy();
      break;
    case 0xC3:
      standBy();
      break;
    case 0xC4:
      standBy();
      break;
    case 0xC5:
      standBy();
      break;
    case 0xC6:
      standBy();
      break;
    /************************任务4***********************************/
    case 0xD1:
      close_flash();
      open_flash(greenInput);
      turn(45, right);
      break;
    case 0xD2:
      standBy();
      break;
    case 0xD3:
      flash(300, 3);
      break;
    case 0xD4:
      turn(90, right);
      break;
    case 0xD5:
      standBy();
      break;
    case 0xD6:
      flash(300, 3);
      break;
    case 0xD7:
      turn(90, right);
      break;
    case 0xD8:
      standBy();
      break;
    case 0xD9:
      flash(300, 3);
      break;
    case 0xDA:
      turn(90, right);
      break;
    case 0xDB:
      standBy();
      break;
    case 0xDC:
      flash(300, 3);
      break;
    /*****************************任务5*********************************/
    case 0xE1:
      turn(45, right);
      adjust(180);
      break;
    case 0xE2:
      standBy();
      break;
    case 0xE3:
      standBy();
      break;
    case 0xE4:
      standBy();
      break;
    case 0xE5:
      standBy();
      break;
    case 0xE6:
      digitalWrite(ledpin,LOW); //3号车LOW是灯亮
      close_flash();
      open_flash(charN);
      break;
  }
}
