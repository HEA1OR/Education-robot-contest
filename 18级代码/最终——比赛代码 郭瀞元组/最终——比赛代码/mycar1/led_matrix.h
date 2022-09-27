#ifndef _LED_MATRIX_H
#define _LED_MATRIX_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SoftwareSerial.h>
#define RX2 5
#define TX2 6		
 
#define redHeart      0       //红心
#define escortFlash   1       //护航信号
#define greenSmile    2       //绿色笑脸
#define blueShield    3       //蓝盾
#define patrolFlash   4       //巡逻信号
#define redArrow      5       //红色箭头
#define greenS        6       //粗S
#define sos           7       //红色SOS
#define greenInput    8      //输入，表救援动作  
#define charA         9       //A
#define charC         10      //C
#define charH         11      //H
#define charI         12      //I
#define charJ         13      //J
#define charN         14      //N
#define charU         15      //U
#define CHINA         16      //CHINA
#define scrollArrow   17      //绿色滚动箭头
#define seventy       18      //70
#define areaPatrol    19      //区域巡逻

#define escortFlashTime 4000
#define patrolFlashTime 4000
#define sosTime       4000




void led_matrix_init();
void open_flash(byte index);
void close_flash();
int flash_over_judge();

#endif
