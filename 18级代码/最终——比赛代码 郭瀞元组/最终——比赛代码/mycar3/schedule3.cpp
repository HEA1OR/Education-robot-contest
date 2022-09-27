#include "schedule3.h"

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
//car3 救护车B
void command_execute(byte c)
{
  switch (c)
  {
    // 目前用这个0x90作为调试信号，当car3接受到调试信号后，显示3
    
    case 0x90:
     
      close_flash();
      open_flash('I');
      //显示数字3，表示调试成功
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
      
      alongLine(79.7); //80.7 每段减少5
      
      standBy();
      break;  
        
    case 0xA2:
      
      turn(89.7,1);
      
      standBy();
 
      break;
        
    case 0xA3:
      adjust(90+0.4+delta*2);
      alongLine(60);
      delay(500);
      adjust(90+0.4+delta*2);
      delay(4000);
      close_flash();
      open_flash('C');
      
    
      alongLine(43.7);//没改
      delay(500);
      turn(88.8,1);//89.3多了
      delay(500);    
      adjust(0.7+delta*2.5);
      alongLine(58.4);//
      
      standBy();
      break;

      

    case 0xA4:
    
      close_flash();
      open_flash('J');
      standBy();
      break;
  
    /************************第二阶段***********************************/
//    case 0xB1:
//
//      close_flash();
//      open_flash('C');
//      
//    
//      alongLine(43.7);//没改
//      delay(500);
//      turn(88.8,1);//89.3多了
//      delay(500);    
//      adjust(0.7+delta*2.5);
//      alongLine(58.4);//
//      
//      standBy();
//      break;
      
  //救护车B还要和救护车A交互   
    case 0xB2:
      close_flash();
      open_flash('J');
      flash(500,3);
      
      standBy();
      break;
      
    case 0xB3:
     
      close_flash();
      open_flash('C');
      delay(6000);
      alongLine(41.5);//41
      delay(500);
      turn(88,1);//11.22晚 88.9多了  88.5还是有点点多  88.3怎么还是多 
      delay(500);
      
     
      adjust(270+1.3+delta*1.2);
      alongLine(34.7);//38.7
      adjust(270+1.3+delta*1.2);
      standBy();
      break;

   case 0xB4:

      standBy();
      break;
  
     // 救护车B经过这个信号直接停在车库
    case 0xB5:

      delay(8000);
      alongLine(51.5);//53
      delay(100);
      adjust(270+1.2+delta);
      alongLine(50);//50
      delay(100);
      adjust(270+1.2+delta);
      alongLine(71);
      
      delay(500);
      turn(90,0);
      delay(500);
      alongWall(29.5);//11.22晚 27.9少了
      delay(500);
      turn(90,0);
      delay(500);
      alongLine(29.1);//30.1
      delay(500);
      turn(180,0);
      delay(500);
      adjust(delta);
      
      standBy();
      break;



     case 0xB6:
     
     standBy();
      break;
     
   
    // 这个信号救护车B走的最长 加了一个救护车B显示对勾表示任务完成，不过没加信号，时间不够了
  
     case 0xC1:

      delay(5000);
      alongLine(31.1);//29.1
      delay(500);
      turn(90,0);
      delay(500);
      adjust(-1.2+delta);
      alongWall(73);//73
      
      delay(500);
      turn(89.5,0);
      delay(500);
      
      alongWall(76.7);//46.7
      //alongLine(42.7);
      delay(500);
      
     // alongLine(39);//40
      //经过岔路口 直接前进
      
     alongLine(52);
    // alongLine(51);
      delay(100);
      adjust(90-1.2+delta);
      
      alongWall(79);//60
     
      delay(500);
      turn(90,0);
      delay(500);
      alongWall(62.7);//29.67
      delay(500);
      close_flash();
      open_flash('J');
      flash(500,3);
      delay(3000);
      close_flash();
      open_flash('C');
      
      adjust(180+delta);
      
      alongLine(66);
     // alongWall(85);//11.22晚改
      //alongLine(81);
      
      delay(500);
      adjust(180+delta-2.5);
      alongWall(77);//90
      delay(500);
      turn(90,0);
      delay(500);
      alongWall(52.5);//57
      //alongLine(53); 
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
      alongWall(53.5);//11.22 45不够
    
      
      standBy();
      break;

    case 0xD2:

      
      turn(89.8,0);
     
      
      standBy();
      break; 

    case 0xD3:

     alongLine(57);//73
      
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
