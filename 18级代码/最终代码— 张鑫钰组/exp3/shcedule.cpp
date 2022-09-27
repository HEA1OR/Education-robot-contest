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
    sendSignal('u');
    standBy();
    break;

    case 0xDD:
    delay(15000);
    flash(1);
    sendSignal('u');
    standBy();
    break;
    
    case 0xD1:
    sendSignal('I');
    delay(2000);    

    alongLine(75);
    standBy();
    break;

    case 0xD2:
    flash(1);
    turn(180,left);delay(500);    
    sendSignal('C');
    alongLine(40);delay(500);
    turn(90,right);delay(500);
    alongLine(75);delay(500);
    turn(90,right);delay(700);
    alongLine(75);delay(500);
    turn(90,right),delay(700);
    alongLine(34);
    standBy();
    break;

    case 0xD3:
    delay(2500);
    sendSignal('A');
    alongLine(81);delay(500);
    turn(90,right);    
    sendSignal('E');
    delay(2500);
    alongWall(36);
    standBy();
    break;
    
    case 0xD4:
    delay(5200);
    alongWall(70.5);delay(50);
    turn(90,right);delay(50);
    alongWall(37);delay(50);
    turn(90,right);   
    standBy();
    break;

    case 0xD5:
    delay(2000);
    alongLine(30);
    standBy();
    break;

    case 0xDB:
    flash(3);
    delay(2000);
    alongLine(30);
    delay(600);
    turn(45,left);    
    sendSignal('L'); 
    flash(2);
    delay(2000);
    turn(90,right);      

    flash(2);
    delay(2000);
    turn(90,right);
    delay(500);
    alongLine(20);    
    standBy();
    break;
    
    case 0xD6:
    delay(800);
    flash(2);
    turn(90,right);delay(500);
    alongLine(20);delay(500);
    turn(130,right);
    delay(500);    
    standBy();
    break;
    
    case 0xD7:   
    alongLine(42);
    standBy();
    break;

    case 0xDC:
    sendSignal('D');
    flash(5);
    standBy();
    delay(20000);
    break;
   
   default:
   standBy();
   break;

  }
}
