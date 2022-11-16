#include <SPI.h>
#include "JY901.h"
#include "Adafruit_NeoPixel.h"    //引入头文件
#include <Servo.h>            // 调用Servo库
#ifdef __AVR__
 #include <avr/power.h> 
#endif

float angle = 0;


#define leftPin 2                       // 编码器所在中断引脚
#define rightPin 3
#define LED_PIN    4     //定义信号输出引脚
#define LED_COUNT 27     //定义LED灯个数
#define ADD true
#define SUB false
#define LEDModePin0 5
#define LEDModePin1 6     // 译码法选择灯带显示模式
#define LEDModePin2 7     // 译码法选择灯·带显示模式
#define RISEPIN 8     // 舵机引脚

#define IN1 2  //定义IN1为2
#define IN2 3 //定义IN2为3
#define  ENA 4  //定义ENA为A4

uint8_t mode = 0;         // 灯带状态
boolean stat1 = true;     //呼吸状态反转标志
int val = 130;            //呼吸亮度变量
int flag =90;
int changeflag =0;
int color;            //色彩改变变量
int count = 0;            // 控制尾灯熄灭时长的计数变量，不用改
int lightNumber = 27;            // 灯珠数量
int leftStartLight = 0;          // 左侧灯珠的起始位置
int rightStartLight = 27;        // 右侧灯珠的起始位置
int leftEndLight = 13;           // 左侧灯珠的结束位置
int rightEndLight = 14;          // 右侧灯珠的结束位置
int leftMainLight = 0;           // 流水灯的主灯位置（左）
int rightMainLight = 27;         // 流水灯的主灯位置（右）
int sideBrightness = 100;        // 侧灯的最大亮度
int tailGroup[] = {13, 14};// 尾灯的灯珠位置
int tailNumber = 0;              // 尾灯数量
int change=0;                   //
int changecolor=0;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);//创建灯条对象
uint32_t hsvcolor = strip.ColorHSV(0*256,255, val); //控制颜色

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )


uint8_t data_to_send[10]={0};           // 数据流 
volatile int EvenCheckLeft = 0;         // 偶检验变量
volatile int EvenCheckRight = 0;
long int cc = 0;                        // 记录整个路程，最后采用这个数据

// 当前灯珠指向
  int16_t idx = 0;

//初始化将灯珠的等级保存于数组中
  int16_t ArraySave[LED_COUNT][3] = {0};
  Servo myservo;             // 定义Servo对象来控制

// 函数列表：
void setLightMode();
void counter();
void get_angle();
void fadeinout(int colorTemp, int patial = 5);
void forword(int sideColor);
void backword(int sideColor);
void tail(int sideColor);
void engine_stop();
void engine_act();

void setup (void)
{
  // 开始串口通讯
  //注意：此串口与SPI通信没有任何关系，只是为了程序演示输出SPI接收到的字节。
  Serial.begin(115200);      
  strip.begin();           
  strip.show();

  pinMode(LEDModePin0, INPUT);
  pinMode(LEDModePin1, INPUT);
  pinMode(LEDModePin2, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(SS, HIGH);    // SS - pin 10
  digitalWrite(MISO, INPUT);
  digitalWrite(MOSI, OUTPUT);
  SPI.begin ();              // SPI通讯初始化配置
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  attachInterrupt(0, counter, CHANGE);
  

  myservo.attach(8);          // 控制线连接数字8

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

  if(mode == 0){             //蓝色呼吸灯
   myservo.write(90); 
    engine_stop();              //关马达
      fadeinout(124,15);
///////////////////////////////
  
  }
  else if(mode == 1){           // 蓝色跑马灯
   myservo.write(90); 
    engine_stop();              //关马达
    forword(124);
    tail(0);
///////////////////////////////////
    
  }
  else if(mode == 2){          //红色呼吸灯
   myservo.write(90); 
    engine_stop();
    fadeinout(0, 20);           
///////////////////////////////////
   
  }
  else if(mode == 3){           //彩色跑马灯
   myservo.write(90); 
    engine_stop();              //关马达
    forword(color);
    tail(0);
    color += 3;
//////////////////////////////////
 
  }
  else if(mode == 4){            //彩虹效果，每个灯珠颜色不一
   myservo.write(90); 
    engine_stop();             //关马达
    rainbow();
///////////////////////////////////////////////
    
  }
  else if(mode == 5){           //升旗+呼吸
    engine_act();              //开马达
    rise();
    
    for(int i=0;i<=27;i++){
      hsvcolor = strip.ColorHSV(changecolor*256, 255, val);
      strip.setPixelColor(i, hsvcolor);
      }
      strip.show();
      if(val<10)
      {change=1;
      changecolor=random(250);}
      else if(val>140)
      {change=0;}
      
      if(change == 1)
      {val+=10;}
      else if(change == 0)
      {val-=10;}
////////////////////////////////////
    
    
  }
  else if(mode == 6){            //变色呼吸灯
   myservo.write(90); 
    engine_stop();               //关马达
    
      for(int i=0;i<=27;i++){
      hsvcolor = strip.ColorHSV(changecolor*256, 255, val);
      strip.setPixelColor(i, hsvcolor);
      }
      strip.show();
      if(val<10)
      {change=1;
      changecolor=random(250);}
      else if(val>140)
      {change=0;}
      
      if(change == 1)
      {val+=10;}
      else if(change == 0)
      {val-=10;}

////////////////////////////////////////
   
  }
  else if(mode == 7){             //快速变色
    engine_act();       //开马达  
     rise();
      for(int i=0;i<=27;i++){
      hsvcolor = strip.ColorHSV(val*6250, 255, 150);
      strip.setPixelColor(i, hsvcolor);
      strip.show();
      }
      if(val<40)
      {change=1;}
      else if(val>250)
      {change=0;}
      
      if(change == 1)
      {val+=30;}
      else if(change == 0)
      {val-=30;}
/////////////////////////////////////////

    
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



void engine_act()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,500);
}


void engine_stop()
{
    digitalWrite(IN1,LOW); //控制电机停下
    digitalWrite(IN2,LOW);
}

void rise(){         // 升旗仪式

  int pos=0;
  //myservo.write(50);
  //delay(50);
  for (pos = 60; pos <= 120; pos += 1) {   
    myservo.write(pos);               // 舵机角度写入
    delay(12);                         // 控制移动速度
  }
  for (pos = 120; pos >= 60; pos -= 1) {   
    myservo.write(pos);               // 舵机角度写入
    delay(12);                         // 控制移动速度
  }

}


void rainbow(void)  //添加彩虹效果/116
{


  int j = 0;
  for(j=0;j<LED_COUNT/3;j++){
      strip.setPixelColor(j,strip.Color(248-255/(LED_COUNT/3)*j,255/(LED_COUNT/3)*j,0));
      ArraySave[j][0]=248-255/(LED_COUNT/3)*j;
      ArraySave[j][1]=255/(LED_COUNT/3)*j;
      ArraySave[j][2]=0;
  }
  for(j=0;j<LED_COUNT/3;j++){
      strip.setPixelColor(j+8,strip.Color(0,248-255/(LED_COUNT/3)*j,255/(LED_COUNT/3)*j));
      ArraySave[j+LED_COUNT/3][0]=0;
      ArraySave[j+LED_COUNT/3][1]=248-255/(LED_COUNT/3)*j;
      ArraySave[j+LED_COUNT/3][2]=255/(LED_COUNT/3)*j;
  }
  for(j=0;j<LED_COUNT/3;j++){
      strip.setPixelColor(j+16,strip.Color(255/(LED_COUNT/3)*j,0,248-255/(LED_COUNT/3)*j));
      ArraySave[j+LED_COUNT/3*2][0]=255/(LED_COUNT/3)*j;
      ArraySave[j+LED_COUNT/3*2][1]=0;
      ArraySave[j+LED_COUNT/3*2][2]=248-255/(LED_COUNT/3)*j;
  }



    uint16_t i = 0,k = 0;
    uint16_t t[3] = {0};
    for(k=0;k<3;k++){
        t[k]=ArraySave[0][k];
    }
    for(i=0;i<LED_COUNT;i++){
      for(k=0;k<3;k++){
        ArraySave[i][k]=ArraySave[i+1][k];
      }
      strip.setPixelColor(i,ArraySave[i][0],ArraySave[i][1],ArraySave[i][2]);
    }
    
    for(k=0;k<3;k++){
        ArraySave[LED_COUNT-1][k]=t[k];  
    }
    strip.setPixelColor(LED_COUNT-1,ArraySave[LED_COUNT-1][0],ArraySave[LED_COUNT-1][1],ArraySave[LED_COUNT-1][2]);
    
    delay(50);
    // 显示
    strip.show();
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
  for(int i=-1;i<27;i++){
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
  for(int i=-1;i<27;i++){
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
