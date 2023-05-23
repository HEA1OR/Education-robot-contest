
#include <SPI.h>
#include "JY901.h"
#include "Adafruit_NeoPixel.h"    //引入头文件
#include <Servo.h>            // 调用Servo库
#ifdef __AVR__
 #include <avr/power.h> 
#endif

float angle = 0;


#define LEDModePin0 2
#define LEDModePin1 3     // 译码法选择灯带显示模式
#define LEDModePin2 4     // 译码法选择灯·带显示模式
#define ModePin0 5
#define ModePin1 6
#define ModePin2 7

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )


uint8_t data_to_send[10]={0};           // 数据流 
volatile int EvenCheckLeft = 0;         // 偶检验变量
volatile int EvenCheckRight = 0;
long int cc = 0;                        // 记录整个路程，最后采用这个数据
int mode = 0;
// 函数列表：
void setLightMode();
void counter();
void get_angle();
void sendmode();

void setup (void)
{
  // 开始串口通讯
  //注意：此串口与SPI通信没有任何关系，只是为了程序演示输出SPI接收到的字节。
  Serial.begin(115200);      

  pinMode(LEDModePin0, INPUT);
  pinMode(LEDModePin1, INPUT);
  pinMode(LEDModePin2, INPUT);
  pinMode(ModePin0, OUTPUT);
  pinMode(ModePin1, OUTPUT);
  pinMode(ModePin2, OUTPUT);

  digitalWrite(SS, HIGH);    // SS - pin 10
  digitalWrite(MISO, INPUT);
  digitalWrite(MOSI, OUTPUT);
  SPI.begin ();              // SPI通讯初始化配置
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  attachInterrupt(0, counter, CHANGE);
  
}



void loop (void)
{
  setLightMode();
  sendmode();
  digitalWrite(SS, LOW);    // SS - pin 10
  // 循环发送字节，实现字符串的发送
  for(int i = 0; i < 20; i ++){
      get_angle();
      Send_Data(cc, angle);
      delay(4);
  }


  }
  



void setLightMode(){
  int a = digitalRead(LEDModePin0);
  int b = digitalRead(LEDModePin1);
  int c = digitalRead(LEDModePin2);
  if(a == 0 && b == 0 && c ==0)
    mode = 0;
  else if(a == 1 && b == 0 && c ==0)
    mode = 1;
  else if(a == 0 && b == 1 && c ==0)
    mode = 2;
  else if(a == 1 && b == 1 && c ==0)
    mode = 3;
  else if(a == 0 && b == 0 && c ==1)
    mode = 4;
  else if(a == 1 && b == 0 && c ==1)
    mode = 5;
  else if(a == 0 && b == 1 && c ==1)
    mode = 6;
  else if(a == 1 && b == 1 && c ==1)
    mode = 7;
}


void Send_Data(long int a, float b)
{
  // 一次发送两个字节的数据，分别为左右轮所行进的长度。
  uint8_t cnt=0;
  data_to_send[cnt++]=0xAA;
  data_to_send[cnt++]=BYTE3(a);
  data_to_send[cnt++]=BYTE2(a);
  data_to_send[cnt++]=BYTE1(a);
  data_to_send[cnt++]=BYTE0(a);
  data_to_send[cnt++]=BYTE3(b);
  data_to_send[cnt++]=BYTE2(b);
  data_to_send[cnt++]=BYTE1(b);
  data_to_send[cnt++]=BYTE0(b);
  data_to_send[cnt++]=0xDD;
  for(int i=0;i<cnt;i++)
  {
    SPI.transfer(data_to_send[i]);
    Serial.write(data_to_send[i]);
  }
}


void counter(){
  if(EvenCheckLeft == 0){
    cc ++;
    EvenCheckLeft = 1 - EvenCheckLeft;
  }
  else
    EvenCheckLeft = 1 - EvenCheckLeft;
  
}


void get_angle(void)
{
  while(Serial.available())
  {
    JY901.CopeSerialData(Serial.read());
  }
  angle = (float)JY901.stcAngle.Angle[2] / 32768 * 180 + 180;
}

void sendmode(){
  if(mode == 0)
  {
    digitalWrite(ModePin0, LOW);
    digitalWrite(ModePin1, LOW);
    digitalWrite(ModePin2, LOW);
  }
  else if(mode == 1)
  {
    digitalWrite(ModePin0, HIGH);
    digitalWrite(ModePin1, LOW);
    digitalWrite(ModePin2, LOW);
  }
  else if(mode == 2)
  {
    digitalWrite(ModePin0, LOW);
    digitalWrite(ModePin1, HIGH);
    digitalWrite(ModePin2, LOW);
  }
  else if(mode == 3)
  {
    digitalWrite(ModePin0, HIGH);
    digitalWrite(ModePin1, HIGH);
    digitalWrite(ModePin2, LOW);
  }
  else if(mode == 4)
  {
    digitalWrite(ModePin0, LOW);
    digitalWrite(ModePin1, LOW);
    digitalWrite(ModePin2, HIGH);
  }
  else if(mode == 5)
  {
    digitalWrite(ModePin0, HIGH);
    digitalWrite(ModePin1, LOW);
    digitalWrite(ModePin2, HIGH);
  }
  else if(mode == 6)
  {
    digitalWrite(ModePin0, LOW);
    digitalWrite(ModePin1, HIGH);
    digitalWrite(ModePin2, HIGH);
  }
  else if(mode == 7)
  {
    digitalWrite(ModePin0, HIGH);
    digitalWrite(ModePin1, HIGH);
    digitalWrite(ModePin2, HIGH);
  }

}
