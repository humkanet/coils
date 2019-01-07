#include <avr/io.h>
#include "coils.h"
#include "pre.h"

#define drv_in13_high()  PORT(DRV_IN13_PORT) |= _BV(PINx(DRV_IN13_PORT, DRV_IN13_PIN))
#define drv_in13_low()   PORT(DRV_IN13_PORT) &= ~_BV(PINx(DRV_IN13_PORT, DRV_IN13_PIN))
#define drv_in24_high()  PORT(DRV_IN24_PORT) |= _BV(PINx(DRV_IN24_PORT, DRV_IN24_PIN))
#define drv_in24_low()   PORT(DRV_IN24_PORT) &= ~_BV(PINx(DRV_IN24_PORT, DRV_IN24_PIN))

#define forward()        drv_in13_high(); drv_in24_low()
#define reverse()        drv_in13_low(); drv_in24_high()


inline void coils_init()
{
	// Настраиваем пины (IN)
	PORT(DRV_IN13_PORT) &= ~_BV(PINx(DRV_IN13_PORT, DRV_IN13_PIN));
	PORT(DRV_IN24_PORT) &= ~_BV(PINx(DRV_IN24_PORT, DRV_IN24_PIN));
	DDR(DRV_IN13_PORT)  |= _BV(PINx(DRV_IN13_PORT, DRV_IN13_PIN));
	DDR(DRV_IN24_PORT)  |= _BV(PINx(DRV_IN24_PORT, DRV_IN24_PIN));
	// Настраиваем пины (DRV1_)
	PORT(DRV1_ENA_PORT)  &= ~_BV(PINx(DRV1_ENA_PORT, DRV1_ENA_PIN));
	PORT(DRV1_ENB_PORT)  &= ~_BV(PINx(DRV1_ENB_PORT, DRV1_ENB_PIN));
	DDR(DRV1_ENA_PORT)   |= _BV(PINx(DRV1_ENA_PORT, DRV1_ENA_PIN));
	DDR(DRV1_ENB_PORT)   |= _BV(PINx(DRV1_ENB_PORT, DRV1_ENB_PIN));
	// Настраиваем пины (DRV2_)
	PORT(DRV2_ENA_PORT)  &= ~_BV(PINx(DRV2_ENA_PORT, DRV2_ENA_PIN));
	PORT(DRV2_ENB_PORT)  &= ~_BV(PINx(DRV2_ENB_PORT, DRV2_ENB_PIN));
	DDR(DRV2_ENA_PORT)   |= _BV(PINx(DRV2_ENA_PORT, DRV2_ENA_PIN));
	DDR(DRV2_ENB_PORT)   |= _BV(PINx(DRV2_ENB_PORT, DRV2_ENB_PIN));
}


void coil1_forward()
{
	forward();
	PORT(DRV1_ENA_PORT) |= _BV(PINx(DRV1_ENA_PORT, DRV1_ENA_PIN));
}


void coil1_reverse()
{
	reverse();
	PORT(DRV1_ENA_PORT) |= _BV(PINx(DRV1_ENA_PORT, DRV1_ENA_PIN));
}


inline void coil1_off()
{
	PORT(DRV1_ENA_PORT) &= ~_BV(PINx(DRV1_ENA_PORT, DRV1_ENA_PIN));
}


inline void coil2_forward()
{
	forward();
	PORT(DRV1_ENB_PORT) |= _BV(PINx(DRV1_ENB_PORT, DRV1_ENB_PIN));
}


void coil2_reverse()
{
	reverse();
	PORT(DRV1_ENB_PORT) |= _BV(PINx(DRV1_ENB_PORT, DRV1_ENB_PIN));
}


void coil2_off()
{
	PORT(DRV1_ENB_PORT) &= ~_BV(PINx(DRV1_ENB_PORT, DRV1_ENB_PIN));
}


void coil3_forward()
{
	forward();
	PORT(DRV2_ENA_PORT) |= _BV(PINx(DRV2_ENA_PORT, DRV2_ENA_PIN));
}


void coil3_reverse()
{
	reverse();
	PORT(DRV2_ENA_PORT) |= _BV(PINx(DRV1_ENA_PORT, DRV2_ENA_PIN));
}


inline void coil3_off()
{
	PORT(DRV2_ENA_PORT) &= ~_BV(PINx(DRV2_ENA_PORT, DRV2_ENA_PIN));
}



inline void coil4_forward()
{
	forward();
	PORT(DRV2_ENB_PORT) |= _BV(PINx(DRV2_ENB_PORT, DRV2_ENB_PIN));
}


void coil4_reverse()
{
	reverse();
	PORT(DRV2_ENB_PORT) |= _BV(PINx(DRV2_ENB_PORT, DRV2_ENB_PIN));
}


void coil4_off()
{
	PORT(DRV2_ENB_PORT) &= ~_BV(PINx(DRV2_ENB_PORT, DRV2_ENB_PIN));
}
