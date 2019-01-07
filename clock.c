#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "clock.h"

#define U16(x)  ((uint16_t) (x))

#define CLOCK_TMR        ((F_CPU/1000)*CLOCK_TICK_MSEC)
#if CLOCK_TMR<=256
	#define TMR_CS     0x01
	#define CLOCK_DIV  1
#elif CLOCK_TMR<=(256*8)
	#define TMR_CS     0x02
	#define CLOCK_DIV  8
#elif CLOCK_TMR<=(256*32)
	#define TMR_CS     0x03
	#define CLOCK_DIV  32
#elif CLOCK_TMR<=(256*64)
	#define TMR_CS     0x04
	#define CLOCK_DIV  64
#elif CLOCK_TMR<=(256*128)
	#define TMR_CS     0x05
	#define CLOCK_DIV  128
#elif CLOCK_TMR<=(256*256)
	#define TMR_CS     0x06
	#define CLOCK_DIV  256
#elif CLOCK_TMR<=(256*1024)
	#define TMR_CS     0x07
	#define CLOCK_DIV  1024
#else
	#error "CLOCK_TICK_MSEC to HIGH"
#endif

struct {
	volatile uint16_t msec;
} clock;


ISR(TIMER2_COMP_vect)
{
	clock.msec += CLOCK_TICK_MSEC;
}


inline void clock_init()
{
	clock.msec = 0;
	// Настраиваем таймер
	ASSR  &= ~_BV(AS2);
	TCCR2  = _BV(WGM21);
	TCNT2  = 0;
	OCR2   = (CLOCK_TMR/CLOCK_DIV)-1;	
	// Настраиваем прерывания
	TIFR  &= _BV(OCF2);
	TIMSK |= _BV(OCIE2);
	// Запускаем таймер
	TCCR2 |= TMR_CS;	
}


uint16_t clock_msec()
{
	uint16_t msec = clock.msec;
	while(msec!=clock.msec){
		msec = clock.msec;
	}
	return msec;
}


void clock_delay(uint16_t msec)
{
	uint16_t start = clock_msec();
	uint8_t  sm    = MCUCR & (_BV(SM0) | _BV(SM1) | _BV(SM2));
	// Настраиваем сон
	set_sleep_mode(SLEEP_MODE_IDLE);
	// Ждем
	while(U16(clock_msec()-start)<msec){
		sleep_cpu();
	}
	// Восстанавливаем режим сна
	set_sleep_mode(sm);
}
