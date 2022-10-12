#include "xbee.h"
void xbee_init()
{
	Serial.begin(9600);
	//Serial.flush();
 while(Serial.read()>= 0);
}


// byte 字节
void sendCommand(byte command)
{
	//Serial.flush();
 while(Serial.read()>= 0);
	Serial.write(command);
	//Serial.flush();
 while(Serial.read()>= 0);
}

//得到Serial的数据
byte getCommand()
{
	byte command = -1;
	Serial.flush();
	if (Serial.available())
		command = Serial.read();
	return command;
}
