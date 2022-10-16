#include <SPI.h>
#include "Adafruit_NeoPixel.h"    //引入头文件
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define LED_PIN    4     //定义信号输出引脚
#define LED_COUNT 14      //定义LED灯个数  
#define ADD true
#define SUB false
boolean stat1 = true;     //呼吸状态反转标志
int val = 130;            //呼吸亮度变量
int color = 0;            //色彩改变变量
int count = 0;            //灯珠熄灭时间控制
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);//创建灯条对象
uint32_t hsvcolor = strip.ColorHSV(0*256,255, val); //控制颜色

void tail(int);

void setup(){
  strip.begin();           
  strip.show();
}

void loop(void){
  tail(color);
  delay(80);
}

void tail(int sideColor){
  
  for(int i = 0; i < LED_COUNT; i ++){
    hsvcolor = strip.ColorHSV(sideColor*256, 255, 100);
    strip.setPixelColor(i, hsvcolor);
    sideColor += 5;
  }
  if(val>=140)
    stat1 = SUB;
  else if(val<=4){
    stat1 = ADD; 
  }       
  color += 10;
  strip.show();
  //delay(20);
  if(stat1==SUB) val -= 5;
  else if(stat1==ADD) val += 5;  
}
