#include "schedule2.h"
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
  open_flash(charH);
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
//car2 救护车A
void command_execute(byte c)
{
  switch (c)
  {
     case 0x90:

      close_flash();
      open_flash('H');
      //显示数字2，表示调试成功
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
     open_flash('C');
     alongLine(86.5);
     
     standBy();
     break;
      
    case 0xA2:

        turn(90,1);
        standBy();
        break;
        
    case 0xA3:
       alongLine(53);
       delay(500);
       turn(180,1);
       delay(500);
       adjust(270+delta);
        
  
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
     open_flash('C');
     alongWall(36.5);//比中心到现在的位置少了10
     //然后救护车A要和救护车B交互
     standBy();
     break;
     
  //A和B的交互
    case 0xB2:
      close_flash();
      open_flash('D');
      flash(500,3);
      
      standBy();
      break;
      
    case 0xB3:
      close_flash();
      open_flash('C');
     
      alongLine(14.5);
      delay(500);
      turn(90.9 ,0); // 91 多了 90.7少了一点点
      delay(500);
      adjust(delta/2.3);//11.22晚 把1.1改成1.3
      
      alongLine(73);
      delay(100);
      
      adjust(delta);
     
      standBy();
      break;

    // A 和 私家车 的交互
    case 0xB4:
    
      close_flash();
      open_flash('D');
      flash(500,3);
      
      standBy();
      break;

      // 救护车A经过这个信号直接停在车库
    case 0xB5:
      close_flash();
      open_flash('C');
      delay(5000);
     
      adjust(delta/1.2);
      alongLine(73.4);
      delay(100);
      //着重注意

      
      adjust(delta/1.2);
     
      alongLine(60);
      delay(500);
      turn(91,0);
      delay(500);
      alongWall(72.4);
      delay(500);
      turn(91,0);
      delay(500);
      alongLine(31);
      delay(500);
      turn(180,0); //在车库处停住
    
      standBy();
      break;

    case 0xB6:
     
      standBy();
      break;

    // 这里救护车A不管其他车的操作，直接回到自己的位置  
    case 0xC1:

      close_flash();
      open_flash('C');
      alongLine(34);
      delay(500);
      turn(91,0);
      delay(500);
      alongWall(29.8);
    
      
      delay(500);
      turn(90,0);
      delay(500);
      alongWall(94.7);
      delay(500);  //经过岔路口 直接前进
      
      alongWall(117.7); // 119.7
      
      delay(500);
      turn(91,0);
      delay(500);
      adjust(270+delta);
      alongLine(72.5);
      delay(500);
      turn(91.2,0);
      delay(500);
      alongLine(33.6);
      delay(500);
      turn(180,0);
     
      standBy();
      break;
      
    case 0xC4:

      
      close_flash();
      open_flash('J');
      
      
      standBy();
      break;

    case 0xD1:

      
      close_flash();
      open_flash('C');
      alongLine(32.6);
      delay(500);
      turn(91,0);
      delay(500);
      
      alongWall(33);
      adjust(270+1.3+delta);
      standBy();
      break;

       
    case 0xD2:

      
      turn(91,0);//11.21晚 91感觉不够多  11.22晚 90.8不够多  11.25 91.1多了
      delay(200);
      adjust(4+delta);    
      
      standBy();
      break;

    case 0xD3:

     
     alongLine(70);
    
      
     standBy();
     break;
     
    case 0xD4:
    
     close_flash();
     open_flash('P');
     turn(45,1);
     delay(500);
     turn(45,0);
     delay(500);
     turn(45,0);
     delay(500);
     turn(45,1);
     delay(500);
     standBy();
     break;

  }
}
