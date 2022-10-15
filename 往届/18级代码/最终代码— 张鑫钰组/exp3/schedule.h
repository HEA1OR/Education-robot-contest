#ifndef _SCHEDULE_H
#define _SCHDULE_H


#include "ledMatrix.h"
#include "xbee.h"

#define ledpin 15

void scheduleInit();
void schedule();
void command_execute(byte c);
void turnRound(int a);
void flash(int times);

#endif // !_SCHEDULE_H
