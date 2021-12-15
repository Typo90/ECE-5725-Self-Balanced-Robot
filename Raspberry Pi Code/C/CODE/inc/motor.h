#ifndef __MOTOR_H
#define __MOTOR_H
#include "common.h"


//motor
#define AIN2   	5
#define AIN1   	6
#define BIN1   	13
#define BIN2   	26

#define PWMA_PIN	18
#define PWMB_PIN	19

#define PWMA   *(bcm2835_pwm+5) //channel 0
#define PWMB   *(bcm2835_pwm+9) //channel 1

void motor_init(void);

#endif
