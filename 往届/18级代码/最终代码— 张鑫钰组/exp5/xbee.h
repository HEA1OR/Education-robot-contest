#ifndef _XBEE_H
#define _XBEE_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void xbee_init();
void sendCommand(byte command);
byte getCommand();



#endif

