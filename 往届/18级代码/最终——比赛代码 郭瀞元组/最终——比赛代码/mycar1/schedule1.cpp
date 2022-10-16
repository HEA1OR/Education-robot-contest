#include "schedule1.h"
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
  open_flash(charC);
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

void command_execute(byte c)
//car1私家车
{
  switch (c)
  {
    // 目前用这个0x90作为调试信号，当car1接受到调试信号后，显示1
    
    case 0x90:
    
      close_flash();
      open_flash('G');
      //显示数字1，表示调试成功
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
      open_flash('B');
     
      //直走
      alongLine(66);   
          
      standBy();
      break;
      
    case 0xA2:
    
     turn(90,0);
     standBy();
     break;
      
    case 0xA3:
   
    
     alongWall(46.5);//48.4多了
     delay(500);
  
     turn(89.2,0);//90
  
     delay(500);
     alongLine(29.2);
     delay(500);
     turn(178.5,0);// 11.21晚 179
     delay(500);
     //adjust(180+delta);

    
      standBy();
      break;

    case 0xA4:
    
      close_flash();
      open_flash('J');
      standBy();
      break;

    /************************第二阶段***********************************/
    //私家车跑到路口和救护车A交互
    case 0xB1:
      close_flash();
      open_flash('B');
      alongLine(30.2);
      delay(500);
      turn(89.7,1);
      delay(500);
      
      adjust(90+1.2+delta);
      
      alongLine(48.5);
      delay(500);
      turn(89.5,1);
      delay(500);
      adjust(1.2+delta);
      alongLine(65);//11.25 70快撞上了
       
      standBy();
      break;

    //私家车不能有 0xB2这个信号
     
    case 0xB3:
     standBy();
      break;

    //这是私家车和救护车A的交互信号  
    case 0xB4:

      close_flash();
      open_flash('J');
      flash(500,3);
      
      standBy();
      break;

//给了这个信号之后，私家车直接走完了第二阶段
    case 0xB5:
      
      close_flash();
      open_flash('B');

      alongLine(19);//20.7走少了
      delay(500);
      turn(88,1);//89.5 转多了
      delay(500);
      adjust(270+1.5+delta);
      alongLine(45.2);
      adjust(270+1.6+delta);
      alongLine(49.5);//11.21晚  50有点点多
      delay(500);
      turn(90,0);
      delay(500);
      //下面两个是医院处的alongwall
      alongWall(97.4);//11.21晚 97.1 太极限了
      delay(500);
      turn(90,0);
      delay(500);
      
      alongWall(31.7);
      
      standBy();
      break;

     case 0xB6:

      close_flash();
      open_flash('N');
      flash(500,3);
      standBy();
      break;

     
    case 0xC1:

      close_flash();
      open_flash('B');
      
      adjust(90-0.5+delta);
      alongWall(61.5);//11.21晚 65多了
      delay(500);
      adjust(90-0.5+delta);
      turn(89,0);//11.21晚 89.6好像也多了
      delay(500);
      adjust(180+-0.4+delta);
      alongLine(71);//80
      adjust(180+0.4+delta);
      standBy();
      break;

     
    case 0xC2:
      
      turn(45,0);
      close_flash();
      open_flash('J');
      flash(500,3);
      turn(46.2,1); //11.21晚  45不够
      standBy();
      break;

    case 0xC3:

      
      close_flash();
      open_flash('B');
      adjust(180+0.5+delta);
      alongLine(44.4);
      adjust(180+0.6+delta);
      alongLine(66);//64 多了
      delay(500);
      turn(89.5,0);//90 多了
      delay(500);
      alongWall(45.3);//45.4多了  42.4 不够到达车库2
      delay(500);
      turn(90,0);
      delay(500);
      alongLine(29.2);
      delay(500);
      turn(180,0);
      delay(500);
      //adjust(180+delta);
      
      standBy();
      break;

    case 0xC4:

      
      close_flash();
      open_flash('J');
      
      
      standBy();
      break;

    case 0xD1:

      
      close_flash();
      open_flash('B');
      
      alongLine(29.8);//26.2 还不够
      delay(500);
      turn(90,1);
      delay(500);
      adjust(90+delta);
      alongLine(48.3);//45.4
      
      standBy();
      break;

  case 0xD2:

      
     turn(89,1);//11.21晚 89.4多了
     delay(500);
     adjust(delta);
      
     standBy();
     break;

  case 0xD3:

     alongLine(53);//11.25 73多了
      
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
