#include <SPI.h>
#include "JY901.h"
#include "Adafruit_NeoPixel.h"    //引入头文件
#ifdef __AVR__
 #include <avr/power.h> =-
#endif

float angle = 0;

#define ENCODER_LEFT   2 // 编码器左引脚
#define ENCODER_RIGHT  3 // 编码器右引脚
#define LED_PIN    4     //定义信号输出引脚
#define LED_COUNT 26     //定义LED灯个数
#define ADD true
#define SUB false
#define LEDModePin0 5
#define LEDModePin1 6     // 译码法选择灯带显示模式
uint8_t mode = 0;         // 灯带状态
boolean stat1 = true;     //呼吸状态反转标志
int val = 130;            //呼吸亮度变量
int color;            //色彩改变变量
int count = 0;            // 控制尾灯熄灭时长的计数变量，不用改
int lightNumber = 22;            // 灯珠数量
int leftStartLight = 0;          // 左侧灯珠的起始位置
int rightStartLight = 21;        // 右侧灯珠的起始位置
int leftEndLight = 10;           // 左侧灯珠的结束位置
int rightEndLight = 11;          // 右侧灯珠的结束位置
int leftMainLight = 0;           // 流水灯的主灯位置（左）
int rightMainLight = 21;         // 流水灯的主灯位置（右）
int sideBrightness = 100;        // 侧灯的最大亮度
int tailGroup[] = {11, 12};// 尾灯的灯珠位置
int tailNumber = 0;              // 尾灯数量
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);//创建灯条对象
uint32_t hsvcolor = strip.ColorHSV(0*256,255, val); //控制颜色

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

#define leftPin 2                       // 编码器所在中断引脚
#define rightPin 3

uint8_t data_to_send[10]={0};           // 数据流 
volatile int EvenCheckLeft = 0;         // 偶检验变量
volatile int EvenCheckRight = 0;
long int cc = 0;                        // 记录整个路程，最后采用这个数据


// 函数列表：
void setLightMode();
void counter();
void get_angle();
void fadeinout(int colorTemp, int patial = 5);
void forword(int sideColor);
void backword(int sideColor);
void tail(int sideColor);



void setup (void)
{
  // 开始串口通讯
  //注意：此串口与SPI通信没有任何关系，只是为了程序演示输出SPI接收到的字节。
  Serial.begin(115200);      
  strip.begin();           
  strip.show();
  pinMode(leftPin, INPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(LEDModePin0, INPUT);
  pinMode(LEDModePin1, INPUT);
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
  digitalWrite(SS, LOW);    // SS - pin 10
  // 循环发送字节，实现字符串的发送
  for(int i = 0; i < 20; i ++){
      get_angle();
      Send_Data(cc, angle);
      delay(4);
  }
  // 复位从机
  // digitalWrite(SS, HIGH);    // SS - pin 10
  Serial.print("angle: ");
  Serial.println(angle);
  Serial.print("cc: ");
  Serial.println(cc);
 
  if(mode == 0){
      fadeinout(127);
      hsvcolor = strip.ColorHSV(0*256, 255, val);
      for(int i = 0; i < tailNumber; i ++){
      strip.setPixelColor(tailGroup[i], hsvcolor);
      }
  }
  else if(mode == 1){
    forword(128);
    tail(0);
  }
  else if(mode == 2){
    fadeinout(0, 20);
  }
  else{
    forword(color);
    tail(0);
    color += 3;
  }
}


void setLightMode(){
  int a = digitalRead(LEDModePin0);
  int b = digitalRead(LEDModePin1);
  if(a == 0 && b == 0)
    mode = 0;
  else if(a == 1 && b == 0)
    mode = 1;
  else if(a == 0 && b == 1)
    mode = 2;
  else if(a == 1 && b == 1)
    mode = 3;
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


void fadeinout(int colorTemp, int patial = 5){
  Serial.println(val);
  for(int i=-1; i<lightNumber; i++){
      uint32_t hsvcolor_ = strip.ColorHSV(colorTemp*256, 255, val);
      strip.setPixelColor(i, hsvcolor_);
  }
  Serial.println(colorTemp);
  if(val >= 140)
    stat1 = SUB;
  if(val <= patial + 1)
    stat1 = ADD;  
  
  strip.show();
  //delay(20);
  if(stat1==SUB) val -= patial;
  else if(stat1==ADD) val += patial;
}



void forword(int sideColor){
  for(int i=-1;i<26;i++){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, 0);
      strip.setPixelColor(i, hsvcolor);
  }
  for(int i = leftStartLight; i != leftEndLight + 1; i ++){
    if(abs(i-leftMainLight) == 2 || abs(i - leftEndLight + leftStartLight - 1 - leftMainLight) == 2 || abs(i + leftEndLight - leftStartLight + 1 - leftMainLight) == 2){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, 0.1 * sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
    if(abs(i-leftMainLight) == 1 || abs(i - leftEndLight + leftStartLight - 1 - leftMainLight) == 1 || abs(i + leftEndLight - leftStartLight + 1 - leftMainLight) == 1){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, 0.5 * sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
    if(i == leftMainLight){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
  }
  leftMainLight ++;
  if(leftMainLight > leftEndLight)
    leftMainLight = leftStartLight;
  for(int i = rightEndLight; i != rightStartLight + 1; i ++){
    if(abs(i-rightMainLight) == 2 || abs(i - rightEndLight + rightStartLight + 1 - rightMainLight) == 2 || abs(i + rightEndLight - rightStartLight - 1 - rightMainLight) == 2){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, 0.1 * sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
    if(abs(i-rightMainLight) == 1 || abs(i - rightEndLight + rightStartLight + 1 - rightMainLight) == 1 || abs(i + rightEndLight - rightStartLight - 1 - rightMainLight) == 1){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, 0.5 * sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
    if(i == rightMainLight){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
  }
  rightMainLight --;
  if(rightMainLight < rightEndLight)
    rightMainLight = rightStartLight;
    color += 1;
    if(color>255)
      color -= 255;
  strip.show();
}



void backword(int sideColor){
  for(int i=-1;i<26;i++){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, 0);
      strip.setPixelColor(i, hsvcolor);
  }
  for(int i = leftStartLight; i != leftEndLight + 1; i ++){
    if(abs(i-leftMainLight) == 2 || abs(i - leftEndLight + leftStartLight - 1 - leftMainLight) == 2 || abs(i + leftEndLight - leftStartLight + 1 - leftMainLight) == 2){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, 0.1 * sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
    if(abs(i-leftMainLight) == 1 || abs(i - leftEndLight + leftStartLight - 1 - leftMainLight) == 1 || abs(i + leftEndLight - leftStartLight + 1 - leftMainLight) == 1){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, 0.5 * sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
    if(i == leftMainLight){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
  }
  leftMainLight --;
  if(leftMainLight < leftStartLight)
    leftMainLight = leftEndLight;

  for(int i = rightEndLight; i != rightStartLight + 1; i ++){
    if(abs(i-rightMainLight) == 2 || abs(i - rightEndLight + rightStartLight + 1 - rightMainLight) == 2 || abs(i + rightEndLight - rightStartLight - 1 - rightMainLight) == 2){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, 0.1 * sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
    if(abs(i-rightMainLight) == 1 || abs(i - rightEndLight + rightStartLight + 1 - rightMainLight) == 1 || abs(i + rightEndLight - rightStartLight - 1 - rightMainLight) == 1){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, 0.5 * sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
    if(i == rightMainLight){
      hsvcolor = strip.ColorHSV(sideColor*256, 255, sideBrightness);
      strip.setPixelColor(i, hsvcolor);
    }
  }
  rightMainLight ++;
  if(rightMainLight > rightStartLight)
    rightMainLight = rightEndLight;
    color += 1;
    if(color>255)
      color -= 255;
  strip.show();
}



void tail(int sideColor){
  hsvcolor = strip.ColorHSV(sideColor*256, 255, val);
  for(int i = 0; i < tailNumber; i ++){
    strip.setPixelColor(tailGroup[i], hsvcolor);
  }
  if(val>=150)
    stat1 = SUB;
  if(count > 3){
    stat1 = ADD; 
    count = 0;
  }
  else if(val<=12){ 
    count ++;
    strip.show();
    return;
  }
   
       
  strip.show();
  //delay(20);
  if(stat1==SUB) val -= 5;
  else if(stat1==ADD) val += 5;  
}
