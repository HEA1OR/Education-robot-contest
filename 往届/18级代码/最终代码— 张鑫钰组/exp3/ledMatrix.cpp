#include "ledMatrix.h"

SoftwareSerial ledMatrixSerial(5, 6);  //A1, A2

void ledMatrixInit()
{
	ledMatrixSerial.begin(9600);
}

void sendSignal(byte num)
{
  ledMatrixSerial.write(num);
}
