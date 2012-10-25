#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef NO_TERMINAL
#include <terminal/terminal.h>
#include <util/delay.h>
#endif
#include <util/out.h>
#include "adc.h"

volatile unsigned int adcValues[ADC_NBCHANNELS];
volatile static int currentAdc;
volatile static int freeMode;

#ifndef ADATE
#define ADATE ADFR
#endif

#ifdef ADC_DYNCHANNELS
#define ADC_NBCHANNELS 8
volatile unsigned char adcNbChannels = ADC_NBCHANNELS;
#endif

ISR(ADC_vect)
{
    adcValues[currentAdc] = (ADCL&0xff)|((ADCH&0xff)<<8);

    //this is supposed to be a %
    if (ADC_ROTATECHANNELS == 4)
	currentAdc = (currentAdc+1)&0b11;
    else {
	currentAdc++;

	if (currentAdc >= ADC_ROTATECHANNELS) {
	    currentAdc = 0;
        }
    }

    ADMUX = currentAdc;

    if (freeMode) {
        ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADIE);
    }
}

#ifndef NO_TERMINAL
void print_adc()
{
    int i;

    for (i=0; i<ADC_NBCHANNELS; i++) {
	out_str("ADC");
	out_int(i);
        out_str(" = ");
        out_int(adcValues[i]);
        out_str("\r\n");
    }
}

TERMINAL_COMMAND(adc, "View the ADC value")
{
    print_adc();
}

TERMINAL_COMMAND(adcfree, "View the ADC")
{
    while (1) {
        print_adc();
        _delay_ms(100);
    }
}
#endif

void adc_run(int free)
{
    freeMode = free;
    ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADIE);
}

__attribute__((constructor))
void adc_init()
{
return;
    // Initializing ADC, free running mode
    currentAdc = 0;
    freeMode = 0;
    ADMUX = 0;
#ifdef ADCSRB
    ADCSRB = 0;
#endif
}
