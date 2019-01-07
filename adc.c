#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"


#define ADC_FREQ  150000
#if   (F_CPU/2)<ADC_FREQ
	#define ADC_PS  0x00
#elif (F_CPU/4)<ADC_FREQ
	#define ADC_PS  0x02
#elif (F_CPU/8)<ADC_FREQ
	#define ADC_PS  0x03
#elif (F_CPU/16)<ADC_FREQ
	#define ADC_PS  0x04
#elif (F_CPU/32)<ADC_FREQ
	#define ADC_PS  0x05
#elif (F_CPU/64)<ADC_FREQ
	#define ADC_PS  0x06
#elif (F_CPU/128)<ADC_FREQ
	#define ADC_PS  0x07
#else
	#error "F_CPU to HIGH"
#endif


struct {
	uint8_t  channel;
} adc;


inline void adc_init()
{
	adc.channel = 0;
	// Настраиваем АЦП
	ADCSRA = ADC_PS;
	ADMUX  = _BV(ADLAR) | _BV(REFS0) | adc.channel;
}


uint8_t adc_read(uint8_t channel)
{
	// Устанавливаем канал
	channel = channel&0x03;
	if (channel!=adc.channel){
		adc.channel = channel;
		ADMUX = _BV(ADLAR) | _BV(REFS0) | channel;
		_delay_ms(0.2);
	}
	// Измеряем
	ADCSRA |= _BV(ADSC);
	while(bit_is_set(ADCSRA, ADSC));
	// Возвращаем результат
	return ADCH;
}
