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
    sendSignal('j');
    standBy();
    break;

    case 0xDD:
    delay(15000);
    flash(1);
    sendSignal('j');
    standBy();
    break;
    
    case 0xD1:     
    sendSignal('I');
    alongLine(73); 
    standBy();
    break;

    case 0xD2:
    
    flash(1);
    sendSignal('F');
    standBy();
    break;

    case 0xD3:
    delay(700);
    turn(90,right);delay(500);    
    sendSignal('A');
    alongLine(79);delay(500);
    turn(90,right);
    sendSignal('E');
    delay(1300);      
    alongWall(36);
    standBy();
    break;

    case 0xD4:   
    delay(2000);
    alongWall(32);delay(50);
    turn(90,right);delay(50);
    alongWall(76);delay(50);
    turn(88,right);
    standBy();
    break;

    case 0xD5:
    alongLine(50);    
    standBy();
    break;

    case 0xDB:
    flash(3);
    standBy();
    break;
    
    case 0xD6:
    delay(3000);
    sendSignal('c');
    standBy();
    break;

   case 0xD7:   
   alongLine(20);
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
