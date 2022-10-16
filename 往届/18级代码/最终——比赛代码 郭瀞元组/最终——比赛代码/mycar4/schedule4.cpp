#include "schedule4.h"

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
//car4 政府车
void command_execute(byte c)
{
  switch (c)
  {
     // 目前用这个0x90作为调试信号，当car4接受到调试信号后，显示4
    
    case 0x90:
    /*open_flash('A');
walk(70,90);
delay(2000);
break;*/
      
      close_flash();
      open_flash('Q');
      //显示数字4，表示调试成功
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
      open_flash('A');
      
      alongLine(119); 
      
      standBy();
      break;  
        
    case 0xA2:
      
     turn(90,0);
      
     standBy();
 
     break;
        
    case 0xA3:
    
      alongLine(70);
      delay(500);
      turn(90,0);
      delay(500);
      alongLine(56);
      delay(500);
      turn(180,0);
      delay(500);
      adjust(delta+181);
      
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
      open_flash('A');
    
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

      alongLine(52.5);
      delay(500);
      turn(90,1);
      delay(500);
      alongLine(68);
      delay(500);
      turn(90,1);
      delay(500);
      adjust(1.5+delta);
      alongLine(48);
      adjust(1.5+delta);
      alongLine(43);
      // 在中心路口等到 迟来的私家车 并且完成交互 并且等到car3先过了这个岔路口
      adjust(1+delta);
     

      standBy();
      break;
     
    case 0xC2:

      turn(45,1);
      close_flash();
      open_flash('D');
      flash(500,3);
      turn(45,0);//催促私家车回家防疫
      adjust(1+delta);   
      standBy();
      break;

              
    case 0xC3:


      close_flash();
      open_flash('V');//卸下物资
      flash(500,3);
      delay(4000);
      close_flash();
      open_flash('A');
      
      //等10秒
      delay(10000);
      alongLine(60.2);
      delay(500);
      turn(90.3,0);      
      delay(500);
      adjust(91+0.5+delta);
      alongLine(77.5);
      adjust(91+0.5+delta);
      alongLine(77);
      delay(500);
      turn(90.6,0);
      delay(500);
      adjust(178.5+delta);
      alongWall(70);
      delay(500);
      //下面要显示叉号图案了
      close_flash();
      open_flash('S');
      delay(5000); // 暂定叉号显示5秒
      adjust(181+delta);
      close_flash();
      open_flash('A');
      delay(500);
      alongWall(90);
      delay(500);
      turn(90,0);
      delay(500);
      alongWall(77.2);// 第三阶段结束的时候 停在比一半距离多一点的位置上
     
      standBy();
      break;

   case 0xC4:

      
      close_flash();
      open_flash('J');
      adjust(271+delta); 
      
      standBy();
      break;

   case 0xD1:

      
      close_flash();
      open_flash('A');
      alongWall(76);
      
      standBy();
      break;

   case 0xD2:

      
      turn(90.3,0);
      delay(500);
      adjust(1.5+delta); 
      standBy();
      break;

   case 0xD3:

     alongLine(40.5);
     adjust(1.2+delta); 
     alongLine(43);
     standBy();
     break;

   case 0xD4:
    
     close_flash();
     open_flash('P');
     turn2(45,1);
     delay(500);
     turn2(45,0);
     delay(500);
     turn2(45,0);
     delay(500);
     turn2(45,1);
     delay(500);
     standBy();
     break;
    
   case 0xE1:
     
  open_flash('A');
  alongLine(300);
  delay(2000);
  break;
  }
}
