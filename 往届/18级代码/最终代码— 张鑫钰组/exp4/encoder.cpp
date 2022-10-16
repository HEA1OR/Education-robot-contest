#include "encoder.h"

volatile int countLeft, countRight;

void encoderInit()
{
	pinMode(2, INPUT);  //编码器引脚模式配置
	pinMode(3, INPUT);
	countLeft = 0;
	countRight = 0;
	attachInterrupt(0, blinkLeft, CHANGE);
	attachInterrupt(1, blinkRight, CHANGE);
}

void blinkLeft() {
	countLeft++;
}

void blinkRight() {
	countRight++;
}
