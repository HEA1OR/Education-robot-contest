#include "schedule5.h"

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
  open_flash(charA);
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
      alongLine(5);
      standBy();
      break;
    case 0xA2:
      close_flash();
      open_flash(seventy);
      turn(45, left);
      break;
    case 0xA3:
      close_flash();
      open_flash(escortFlash);
      turn(45, left);
      alongLine(30);
      turn(90, right);
      break;
    case 0xA4:
      adjust(180);
      alongLine(42);
      adjust(180);
      break;
    /************************任务2***********************************/
    case 0xB1:
      close_flash();
      open_flash(scrollArrow);
      turn(90, right);
      alongLine(40);
      turn(90, right);
      alongWall(32); //到达顶角
      turn(90, right);
      break;
    case 0xB2:
      alongWall(33);
      turn(90, right);
      alongLine(25);
      break;
    case 0xB3:
      adjust(180);
      close_flash();
      open_flash(blueShield);
      standBy();
      break;
    /************************任务3***********************************/
    case 0xC1:
      standBy();
      break;
    case 0xC2:
      turn(90, right);
      close_flash();
      open_flash(scrollArrow);
      break;
    case 0xC3:
      alongLine(40);
      turn(90, right);
      break;
    case 0xC4:
      alongWall(32); //到达顶角
      turn(90, right);
      break;
    case 0xC5:
      alongWall(125);
      turn(90, right);
      break;
    case 0xC6:
      alongWall(130);
      break;
    /************************任务4***********************************/
    case 0xD1:
      standBy();
      break;
    case 0xD2:
      standBy();
      break;
    case 0xD3:
      standBy();
      break;
    case 0xD4:
      standBy();
      break;
    case 0xD5:
      standBy();
      break;
    case 0xD6:
      standBy();
      break;
    case 0xD7:
      standBy();
      break;
    case 0xD8:
      standBy();
      break;
    case 0xD9:
      standBy();
      break;
    case 0xDA:
      standBy();
      break;
    case 0xDB:
      turn(135, right);
      break;
    case 0xDC:
      close_flash();
      open_flash(greenS);
      flash(300, 3);
      break;
    /*****************************任务5*********************************/
    case 0xE1:
      standBy();
      break;
    case 0xE2:
      alongLine(60);
      turn(45, right);
      break;
    case 0xE3:
      standBy();
      break;
    case 0xE4:
      alongLine(24);
      break;
    case 0xE5:
      turn(180, right);
      adjust(180);
      break;
    case 0xE6:
      digitalWrite(ledpin, HIGH);
      close_flash();
      open_flash(redHeart);
      break;
  }
}
