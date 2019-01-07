#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "main.h"
#include "clock.h"
#include "coils.h"
#include "adc.h"
#include "pre.h"

#define U16(x)  ((uint16_t) (x))
#define U32(x)  ((uint32_t) (x))

#define STAGE_IDLE           0x00
#define STAGE_COIL1_FORWARD  0x01
#define STAGE_COIL2_FORWARD  0x02
#define STAGE_COIL3_FORWARD  0x03
#define STAGE_COIL4_FORWARD  0x04
#define STAGE_COIL4_REVERSE  0x05
#define STAGE_COIL3_REVERSE  0x06
#define STAGE_COIL2_REVERSE  0x07
#define STAGE_COIL1_REVERSE  0x08
#define STAGE_FINISH         0xFF


inline void setup()
{	
	// Отключаем компаратор
	ACSR |= _BV(ACD);
	// Настраиваем пины
	PORT(START_PORT) &= ~_BV(PINx(START_PORT, START_PIN));
	DDR(START_PORT)  &= ~_BV(PINx(START_PORT, START_PIN));
	PORT(DELAY_PORT) &= ~_BV(PINx(DELAY_PORT, DELAY_PIN));
	DDR(DELAY_PORT)  &= ~_BV(PINx(DELAY_PORT, DELAY_PIN));
	//
	coils_init();
	clock_init();
	adc_init();
}


uint8_t adc_margin(uint8_t channel)
{
	uint8_t adc = adc_read(channel);
	if      (adc<=ADC_MARGIN_LEFT)        return 0;
	else if (adc>=(255-ADC_MARGIN_RIGHT)) return ADC_WIDTH;
	else return adc-ADC_MARGIN_LEFT;
}


void main()
{
	cli();
	setup();
	sei();

	// Настраиваем сон
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();

	uint8_t   stage = STAGE_FINISH;
	uint16_t  delay = 1000;
	uint16_t  ts;
	for(;;){
		uint16_t  msec = clock_msec();

		switch (stage){
			case STAGE_IDLE:
				if (bit_is_set(PIN(START_PORT), PINx(START_PORT, START_PIN))){
					uint16_t adc = 0;
					// Считываем паузу
					adc_on();
					for (char n=0; n<4; n++){
						adc += adc_margin(DELAY_ADC);						
					}
					adc_off();
					delay = U32(adc>>2)*(DELAY_MAX-DELAY_MIN)/ADC_WIDTH + DELAY_MIN;
					// Включаем первую катушку
					stage = STAGE_COIL1_FORWARD;
					ts    = msec;
					coil1_forward();
				}
				break;
			case STAGE_COIL1_FORWARD:
				if (U16(msec-ts)>=delay){
					coil1_off();
					coil2_forward();
					ts    = msec;
					stage = STAGE_COIL2_FORWARD;
				}
				break;
			case STAGE_COIL2_FORWARD:
				if (U16(msec-ts)>=delay){
					coil2_off();
					coil3_forward();
					ts    = msec;
					stage = STAGE_COIL3_FORWARD;
				}
				break;
			case STAGE_COIL3_FORWARD:
				if (U16(msec-ts)>=delay){
					coil3_off();
					coil4_forward();
					ts    = msec;
					stage = STAGE_COIL4_FORWARD;
				}
				break;
			case STAGE_COIL4_FORWARD:
				if (U16(msec-ts)>=delay){
					coil4_reverse();
					ts    = msec;
					stage = STAGE_COIL4_REVERSE;
				}
				break;
			case STAGE_COIL4_REVERSE:
				if (U16(msec-ts)>=delay){
					coil4_off();
					coil3_reverse();
					ts    = msec;
					stage = STAGE_COIL3_REVERSE;
				}
				break;
			case STAGE_COIL3_REVERSE:
				if (U16(msec-ts)>=delay){
					coil3_off();
					coil2_reverse();
					ts    = msec;
					stage = STAGE_COIL2_REVERSE;
				}
				break;
			case STAGE_COIL2_REVERSE:
				if (U16(msec-ts)>=delay){
					coil2_off();
					coil1_reverse();
					ts    = msec;
					stage = STAGE_COIL1_REVERSE;
				}
				break;
			case STAGE_COIL1_REVERSE:
				if (U16(msec-ts)>=delay){
					coil1_off();
					stage = STAGE_FINISH;
				}
				break;
			case STAGE_FINISH:
				coil1_off();
				coil2_off();
				coil3_off();
				coil4_off();
				stage = STAGE_IDLE;
				break;
		}

		// Спим
		sleep_cpu();
	}

}
