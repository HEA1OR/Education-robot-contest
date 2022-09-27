#ifndef _SCHEDULE1_H   //防止一个头文件被include两次
#define _SCHEDULE1_H



#if defined(ARDUINO) && ARDUINO >= 100  //假如在前面定义过 ARDUINO 这个符号，并且其大于等于100
	#include "arduino.h"
#else
	#include "WProgram.h"  //如果ARDUINO版本过老，没有arduino.h，只有WProgram.h
#endif

#include "encoder.h"
#include "motor.h"
#include "ult_wall.h"
#include "compass.h"
#include "xbee.h"
#include "led_matrix.h"
#define ledpin 9

void schedule_init();
void schedule();
void command_execute(byte c);//命令执行函数，内部调用
void flash(int delayTime,int times);


#endif
