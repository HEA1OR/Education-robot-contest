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
  open_flash(charI);
  get_angle();
  
  delta=angle-180;
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
// car5 社区车
void command_execute(byte c)
{
  switch (c)
  {
     // 目前用这个0x90作为调试信号，当car5接受到调试信号后，显示5
    
    case 0x90:
     
      close_flash();
      open_flash('R');
      //显示数字5，表示调试成功
      standBy();
      
      break;
      
    /*******************************第一阶段***********************************/

    case 0xA0:
    
      close_flash();
      open_flash('E');
      //显示叹号
      standBy();
  
      break;

    case 0xA1:

      
      close_flash();
      open_flash('T');
      // 显示笑脸，社区车初始图案
      standBy();
      break;  
        
    case 0xA2:
   
      standBy();
 
      break;
      
        
    case 0xA3:
    
     alongLine(28);
     delay(500);
     turn(90,0); //180度不够 180.5多了
     delay(500);
     alongLine(37);
     delay(500);
     turn(180.4,0); //180度不够 180.5多了
     delay(500);
     adjust(delta+90-0.5);

    
      standBy();
      break;

    case 0xA4:
    
      close_flash();
      open_flash('J');
      standBy();
      break;

      
    /************************第二阶段***********************************/
    case 0xB1:

      close_flash();
      open_flash('U');
      standBy();
      break;
      
    case 0xB2:

     
     standBy();
      break;
      
    case 0xB3:

      standBy();
      break;

      

   case 0xB4:

      standBy();
      break;

    case 0xB5:

      standBy();
      break;

     case 0xB6:
     
     standBy();
      break;
     
    case 0xC1:

     
     standBy();
      break;
     
      
    case 0xC2:

     
     standBy();
      break;
     
    case 0xC3:

      
      close_flash();
      open_flash('J');
      flash(500,3);
      delay(4000);
      close_flash();
      open_flash('U');
      delay(2000);
      alongLine(37);
      delay(500);
      turn(90.5,0);//因为直行会右偏，所以多转一点
      delay(500);
      adjust(180+delta+2.0);
      alongLine(80);
      delay(500);
      turn(90,0);
      delay(500);
      adjust(270+delta+2.1);
      alongWall(31); 
      delay(500);
      adjust(270+delta+2.2); 
      close_flash();
      open_flash('V');// 这里显示运货图案
      flash(300,3);
      delay(1000);
      alongLine(21);
      close_flash();
      open_flash('V');
      flash(300,2);
      delay(1000);
      adjust(270+delta+2.8);
      
      alongLine(23);
      close_flash();
      open_flash('V');
      flash(300,2);
      delay(1000);
      adjust(270+delta+2.8);
      close_flash();
      open_flash('U'); // 这里运货结束，将图案改回来
      
      alongWall(35);
      delay(500);
      turn(90,0);
      delay(500);
      alongWall(110);
      delay(500);
      turn(91.2,0);
      delay(500);
      adjust(90+3+delta);
      alongLine(104);
      //社区车到这里就走完了，进入了圆心
      standBy();
      break;

   case 0xC4:

      
      close_flash();
      open_flash('J');
      
      
      standBy();
      break;
      
   case 0xD1:

      
      close_flash();
      open_flash('T');
      
      
      standBy();
      break;

    case 0xD2:

      standBy();
      break;


      
    case 0xD3:

      standBy();
      break;

    case 0xD4:
    
      close_flash();
      open_flash('O');
      
      standBy();
      break;
      
    
  }
}
