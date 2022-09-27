#include "led_matrix.h"
SoftwareSerial led_matrix_serial(RX2, TX2);//RX,TX

void sendData2(byte data)
{
	led_matrix_serial.flush();
	led_matrix_serial.write(data);
	led_matrix_serial.flush();
}
byte getData2()
{
	byte data = -1;
	led_matrix_serial.flush();
	if (led_matrix_serial.available())
		data = led_matrix_serial.read();
	return data;
}

void led_matrix_init()
{
	led_matrix_serial.begin(9600);
	led_matrix_serial.flush();
}
void open_flash(byte index)
{
	sendData2(index);
}
void close_flash()
{
	sendData2(0xFF);
}
int flash_over_judge()
{
	if (getData2() != 0xFF)
		return 1;
	else
		return 0;
}

