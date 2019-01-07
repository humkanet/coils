WINAVR=C:/usr/winavr
CC=$(WINAVR)/bin/avr-gcc
OBJCOPY=$(WINAVR)/bin/avr-objcopy
SIZE=$(WINAVR)/bin/avr-size

FREQ=8000000UL
MCU=atmega8

OBJS=main.o coils.o clock.o adc.o
NAME=coils

DEPFLAGS = -MT $@ -MMD -MP
CFLAGS   = -mmcu=$(MCU) -std=c11 -DF_CPU=$(FREQ) -Os -ffunction-sections -fdata-sections -g -Wl,--gc-sections

all: ${NAME}.hex

${NAME}.hex: ${NAME}.elf
	$(OBJCOPY) -R .eeprom -O ihex $< $@

${NAME}.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	$(SIZE) --format=avr --mcu=attiny13 $@

%.o: %.c
%.o: %.c %.d
	$(CC) $(CFLAGS) $(DEPFLAGS) -o $@ -c $<

%.d: ;
.PRECIOUS: %.d

clean:
	rm -f $(NAME).elf $(NAME).hex $(OBJS) $(OBJS:.o=.d)


include $(OBJS:.o=.d)
