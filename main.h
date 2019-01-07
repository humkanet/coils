#ifndef _MAIN_H
#define _MAIN_H

#define START_PORT  C
#define START_PIN   2

#define DELAY_PORT  C
#define DELAY_PIN   0
#define DELAY_ADC   0x00
#define DELAY_MIN   500
#define DELAY_MAX   2000

#define ADC_MARGIN_LEFT   5
#define ADC_MARGIN_RIGHT  6
#define ADC_WIDTH         (255-ADC_MARGIN_LEFT-ADC_MARGIN_RIGHT)

#endif
