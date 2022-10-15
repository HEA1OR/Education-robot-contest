#ifndef _LED_MATRIX_H
#define _LED_MATRIX_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SoftwareSerial.h>
#define RX2 4
#define TX2 5		
 

#define escortFlashTime 4000
#define patrolFlashTime 4000
#define sosTime       4000




void led_matrix_init();
void open_flash(byte index);
void close_flash();
int flash_over_judge();

#endif
