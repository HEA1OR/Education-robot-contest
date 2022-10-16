#pragma once
#ifndef _ULT_WALL_H
#define _ULT_WALL_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "motor.h"

#define TRIG_LEFT		16//A2
#define ECHO_LEFT		17//A3
#define MeasureNoise_R 0.11
#define ProcessNiose_Q 0.06

void ultrasonic_init();			//��������ʼ��
void getDistance(void);	//��������ຯ��������ֵ��λΪmm
void kalmanfilter_r(float *z_measure);

#endif
