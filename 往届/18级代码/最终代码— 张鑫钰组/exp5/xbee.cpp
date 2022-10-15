#include "xbee.h"
void xbee_init()
{
	Serial.begin(9600);
	Serial.flush();
}
void sendCommand(byte command)
{
	Serial.flush();
	Serial.write(command);
	Serial.flush();
}
byte getCommand()
{
	byte command = -1;
	Serial.flush();
	if (Serial.available())
		command = Serial.read();
	return command;
}


