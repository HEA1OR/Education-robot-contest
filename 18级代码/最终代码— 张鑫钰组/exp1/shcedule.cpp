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
    sendSignal('n');
    standBy();
    break;

    case 0xDD:
    delay(15000);
    flash(1);
    sendSignal('n');
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
    delay(2200);    
    sendSignal('C');
    alongLine(40);delay(500);
    turn(90,right);delay(500);
    alongLine(75);delay(500);
    turn(90,right);delay(500);
    alongLine(72);delay(500);
    turn(90,right);delay(800);
    alongLine(33);delay(500);
    standBy();
    break;

    case 0xD3: 
    turn(180,right);delay(500);
    sendSignal('A');
    alongLine(82);delay(500);
    turn(90,right);
    sendSignal('E');
    delay(300);
    alongWall(38);
    standBy();
    break;
    
    case 0xD4:
    turn(90,right);delay(50);
    alongWall(121);delay(50);
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
    delay(500);
    turn(45,right);    
    sendSignal('L');
    flash(2);
    delay(2000);
    turn(90,left);      
    flash(2);
    delay(2000);
    turn(90,left);
    delay(500);
    alongLine(20);   
    standBy();
    break;
    
    case 0xD6:
    delay(800);
    flash(2);
    turn(90,left);delay(500);
    alongLine(20);delay(500);
    turn(140,left);
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
   
  }
}
