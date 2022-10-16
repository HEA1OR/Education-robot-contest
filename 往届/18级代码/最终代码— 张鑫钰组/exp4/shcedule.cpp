#include "schedule.h"

int mode = 0;
byte command[2];

void scheduleInit()
{
  compassInit();
  encoderInit();
  motorInit();
  ledMatrixInit();
  xbee_init();
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);
  ultrasonic_init();
}

void schedule()
{
  byte c;
  c = getCommand();
  if (-1 != c)
    command_execute(c);
}

void turnRound(int a)
{
  if (a)
  {
    turn(180, right);
    turn(180, right);
    turn(20, right);
  }
  else
  {
    turn(180, left);
    turn(180, left);
    turn(20, left);
  }
}

void flash(int times)
{
  int i;
  for (i = 0; i < times; i++)
  {
    digitalWrite(ledpin, HIGH);
    delay(300);
    digitalWrite(ledpin, LOW);
    delay(300);
  }
}

void command_execute(byte c)      //任务执行函数 c是从受到的协调器的命令
{
  int ii;
  switch (c)
  {
    case 0xD0:
    standBy();
    break;
    
    case 0xDA:
    flash(1);         ////
    //sendSignal('P');
    standBy();
    break;
    
    case 0xD1:
    //sendSignal('P');
    delay(4000);
    alongWall(76);
    standBy();
    break;

    case 0xD2:
    flash(1);           ////
    //sendSignal('2');
    alongWall(76);
    delay(500);
    turn(90,right);
    standBy();
    break;

    case 0xD3:    
    alongWall(56);
    flash(1);            ////
    delay(500); 
    turn(90,right);
    delay(500);
    alongLine(12);
    delay(500);
    turn(90,left);
    delay(500);
    alongLine(40);
    alongWall(63);
    standBy();
    break;
    
    case 0xD4:
    //sendSignal('4');
    turn(90,right);
    delay(5500);
    alongWall(124);
    delay(500);
    turn(180,right);
    standBy();
    break;

    case 0xD5:
    //sendSignal('A');
    delay(4000);
    alongLine(10);
    standBy();
    break;

    case 0xDB:
    flash(3);        ////
    standBy();
    break;

    case 0xD6:
    turn(45,left);
    flash(2);       ////
    turn(45,right);
    delay(10000);
    alongLine(66); delay(100);
    turn(90,left);
    standBy();
    break;
    
    case 0xD7:
    //sendSignal('X');
    turn(90,right);
    standBy();
    break;

    case 0xDC:
    flash(5);        ////
    standBy();
    break;
  
   default:
   standBy();
   break;
 

  }
}
