#include <SPI.h>
#include "JY901.h"
#include "Adafruit_NeoPixel.h"    //引入头文件
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define nanopin0 2
#define nanopin1 3
#define LED_PIN    4     //定义信号输出引脚
#define LEDModePin0 5
#define LEDModePin1 6     // 译码法选择灯带显示模式
#define LEDModePin2 7     // 译码法选择灯带显示模式
#define LEDS_PER_GROUP 2
#define LED_COUNT 27      // 定义LED灯个数
#define ADD true
#define SUB false

const uint8_t rainbowColors[][3] = {
    {255, 0, 0},    // 红色
    {255, 165, 0},  // 橙色
    {255, 255, 0},  // 黄色
    {0, 128, 0},    // 绿色
    {0, 0, 255},    // 蓝色
    {75, 0, 130},   // 靛蓝色
    {238, 130, 238} // 紫色
};
static uint8_t hueIndex = 0;
float angle = 0;
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
long int cc = 0;                        // 记录整个路程，最后采用这个数据
volatile int EvenCheckLeft = 0;         // 偶检验变量
volatile int EvenCheckRight = 0;
// 当前灯珠指向
int16_t idx = 0;
//初始化将灯珠的等级保存于数组中
int16_t ArraySave[LED_COUNT][3] = {0};

// 函数列表：
void setLightMode();
void get_angle();
void fadeinout(int colorTemp, int patial = 5);
void forword(int sideColor);
void backword(int sideColor);
void tail(int sideColor);
void counter();
void rainbow(void);
void rainbow2(void);
void randomcolor(void);
uint8_t lerp(uint8_t a, uint8_t b, float t);

void setup(void)
{
  // 开始串口通讯
  //注意：此串口与SPI通信没有任何关系，只是为了程序演示输出SPI接收到的字节。
  Serial.begin(115200);      
  strip.begin();           
  strip.show();

  pinMode(LEDModePin0, INPUT);
  pinMode(LEDModePin1, INPUT);
  pinMode(LEDModePin2, INPUT);

  digitalWrite(SS, HIGH);    // SS - pin 10
  digitalWrite(MISO, INPUT);
  digitalWrite(MOSI, OUTPUT);
  SPI.begin();              // SPI通讯初始化配置
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  attachInterrupt(0, counter, CHANGE);
  
}


void loop (void)
{
  setLightMode();

  mode = 5;
  digitalWrite(SS, LOW);    // SS - pin 10
  // 循环发送字节，实现字符串的发送
  for(int i = 0; i < 20; i ++){
      get_angle();
      Send_Data(cc, angle);
      delay(4);
  }
/////////////////////////////////////////////////////////////////////////////////////////
  if(mode == 0){             //蓝色跑马灯+小角度摇晃，用于冰壶冰球中的人物
      digitalWrite(nanopin0, LOW);
      digitalWrite(nanopin1, LOW);
      forword(124);
      tail(0);
  }
  else if(mode == 1){           // 蓝色呼吸灯，电机停止
    fadeinout(124, 15);
    digitalWrite(nanopin0, HIGH);
    digitalWrite(nanopin1, LOW);
  }
  else if(mode == 2){          //红色呼吸灯+小角度摇晃，用于冰球人物
    digitalWrite(nanopin0, LOW);
    digitalWrite(nanopin1, LOW);
    fadeinout(0, 20);           
  }
  else if(mode == 3){           //彩虹渐变+大角度摇晃
    digitalWrite(nanopin0, HIGH);
    digitalWrite(nanopin1, HIGH);
    rainbow();
  }
  else if(mode == 4){            //红色呼吸灯+电机停止，用于被撞的冰壶
    digitalWrite(nanopin0, HIGH);
    digitalWrite(nanopin1, LOW);
    fadeinout(0, 20);
  }
  else if(mode == 5){           //升旗+彩虹渐变
    digitalWrite(nanopin0, LOW);
    digitalWrite(nanopin1, HIGH);
    rainbow2();
    delay(100000);
    digitalWrite(nanopin0, HIGH);
    digitalWrite(nanopin1, LOW);
  }
  else if(mode == 6){            //金色呼吸灯+电机停止，用于被推的冰壶、冰球
    digitalWrite(nanopin0, HIGH);
    digitalWrite(nanopin1, LOW);
    fadeinout(50, 15);
  }
  else if(mode == 7){             //随机变色+大角度摇晃
    digitalWrite(nanopin0, HIGH);
    digitalWrite(nanopin1, HIGH);
    randomcolor();
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


void get_angle(void)
{
  while(Serial.available())
  {
    JY901.CopeSerialData(Serial.read());
  }
  angle = (float)JY901.stcAngle.Angle[2] / 32768 * 180 + 180;
}


void rainbow(void)  //添加彩虹效果/116
{
  for (int i = 0; i < 7; i++)
  {
    // 设置当前颜色
    uint8_t red = rainbowColors[i][0];
    uint8_t green = rainbowColors[i][1];
    uint8_t blue = rainbowColors[i][2];

    // 逐个点亮灯珠
    for (int j = 0; j < LED_COUNT; j++)
    {
      strip.setPixelColor(j, red, green, blue);
      strip.show();
      delay(10); // 控制流动的速度
    }
  }
}


void rainbow2(void){
 for (int group = 0; group < LED_COUNT / LEDS_PER_GROUP; group++) {
    // 计算当前组的彩虹色索引
    uint8_t colorIndex = (hueIndex + group) % 7;
    
    // 获取当前组的彩虹色
    uint8_t red = rainbowColors[colorIndex][0];
    uint8_t green = rainbowColors[colorIndex][1];
    uint8_t blue = rainbowColors[colorIndex][2];
    
    // 循环设置当前组的灯珠颜色
    for (int i = 0; i < LEDS_PER_GROUP; i++) {
      // 设置当前灯珠的颜色
      strip.setPixelColor(group * LEDS_PER_GROUP + i, red, green, blue);
    }
  }
  
  // 灯串显示
  strip.show();
  
  // 延迟一段时间，控制流动速度
  delay(2);
  
  // 彩虹色索引递增
  hueIndex++;
}

void randomcolor(void){
  
  uint8_t red = random(256);   // 生成0到255的随机红色值
  uint8_t green = random(256); // 生成0到255的随机绿色值
  uint8_t blue = random(256);  // 生成0到255的随机蓝色值

  // 设置灯串颜色
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i, red, green, blue);
  }

  strip.show();
  delay(1000); // 控制颜色变化的速度
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

uint8_t lerp(uint8_t a, uint8_t b, float t)
{
  return (1.0 - t) * a + t * b;
}

void counter()
{
  if (EvenCheckLeft == 0)
  {
    cc++;
    EvenCheckLeft = 1 - EvenCheckLeft;
  }
  else
    EvenCheckLeft = 1 - EvenCheckLeft;
}
