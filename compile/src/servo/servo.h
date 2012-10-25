#ifndef SERVO_H
#define SERVO_H

/**
 * Enables the servo
 */
void servo_enable();

/**
 * Disable the servo
 */
void servo_disable();

/**
 * Sets the servo duty (0~4000)
 */ 
void servo_set_duty(int duty);

#endif // SERVO_H
