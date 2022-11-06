#ifndef _MOTOR_H
#define _MOTOR_H

#include "Servo.h"
#include "encoderLED.h"

#define pinL 7  // the number of pin
#define pinR 8
#define left 0
#define right 1

void motorInit();
void alongLine(int setDistance, int mode = 0, int setTime = 10000, int reverse = 0, float setAngle = -1, float setBias = 0, float angleToTurn = 0);
void alongCurve(int setDistance, float setBias, float angleToTurn, int mode = 0);
void turn(float angletoturn, int mode, bool smoothTurn = false);
void standBy();
void walk(float left_speed, float right_speed);
//void pureTurn(float aimAngle, int mode = 0);

#endif // !_MOTOR_H
