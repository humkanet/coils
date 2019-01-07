#ifndef _ADC_H
#define _ADC_H

#include <stdint.h>

#define adc_on()   ADCSRA |= _BV(ADEN)
#define adc_off()  ADCSRA &= ~_BV(ADEN)

void     adc_init(void);
uint8_t  adc_read(uint8_t channel);

#endif
