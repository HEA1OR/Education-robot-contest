#include "ledMatrix.h"

SoftwareSerial ledMatrixSerial(5, 6);  //digital DTR-RST  点阵屏tx接d5，rx接d6

void ledMatrixInit()
{
	ledMatrixSerial.begin(9600);
}

void sendSignal(byte num)
{
  ledMatrixSerial.write(num);
}
