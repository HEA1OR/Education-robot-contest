#ifndef _MOTOR_H
#define _MOTOR_H

#include "Servo.h"
#include "compass.h"


#define pinL 7  // the number of pin
#define pinR 8
#define left 0
#define right 1

void motorInit();
void alongLine(int setTime, int mode = 0,float setAngle = -1);
//void alongWall(float setDistance, int setTime, int setWallDistance);
void turn(float angletoturn, int mode);
void smoothTurn(float angletoturn, int mode);
void standBy();
void walk(float left_speed, float right_speed);
//void adjust(float aim_angle);
void circle(int mode);

#endif // !_MOTOR_H
