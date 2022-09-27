#ifndef _MOTOR_H
#define _MOTOR_H

#include "Servo.h"
#include "compass.h"
#include "encoder.h"
#include "ult_wall.h"

#define pinL 7  // the number of pin
#define pinR 8
#define left 0
#define right 1

void motorInit();
void alongLine(float setDistance);
void alongWall(float setDistance);
void turn(float angletoturn, int mode);
void standBy();
void walk(int left_speed, int right_speed);
void adjust(float aim_angle);

#endif // !_MOTOR_H
