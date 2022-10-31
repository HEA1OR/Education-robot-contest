#include <Wire.h>
#include "Arduino.h"
#include <avr/pgmspace.h>
#include <time.h>
#include "colorduino.c"void setup()
{
  _IO_Initial();           //Init IO
  _LED_Init();          //Init LED Hardware
  _TC2_Init();          //Init Timer/Count2
  Serial.begin(9600);
}

void loop()
{
    showPlane();
}

void setup()
{
  _IO_Initial();           //Init IO
  _LED_Init();          //Init LED Hardware
  _TC2_Init();          //Init Timer/Count2
  Serial.begin(9600);
}

void loop()
{
    showPlane();
}
