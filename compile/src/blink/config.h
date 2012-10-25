#ifndef CONFIG_H
#define CONFIG_H

#include <avr/io.h>

/**
 * Port and pin to blink
 */
#define LED_PORT PORTC
#define LED_DDR  DDRC
#define LED_PIN  PC1

#endif // CONFIG_H
