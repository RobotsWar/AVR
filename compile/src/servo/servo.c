#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h> 
#include <uart/uart.h>
#include <avr/sleep.h>

__attribute__((constructor))
void servo_init()
{
    cli();
   
    // 50Hz
    TCCR1A = _BV(COM1A1) | _BV(WGM11);
    TCCR1B = _BV(WGM13) | _BV(CS11) | _BV(WGM12);
    ICR1H = 156;
    ICR1L = 64;

    sei();
}

void servo_enable()
{
    DDRB |= _BV(PB1);
}

void servo_disable()
{
    DDRB &= ~_BV(PB1);
}

void servo_set_duty(int duty)
{
    OCR1AH = (duty>>8)&0xff;
    OCR1AL = (duty)&0xff;
}
