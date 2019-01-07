#ifndef _CLOCK_H
#define _CLOCK_H

#include <stdint.h>

#define CLOCK_TICK_MSEC  1

void      clock_init(void);
uint16_t  clock_msec(void);
void      clock_delay(uint16_t msec);

#endif
