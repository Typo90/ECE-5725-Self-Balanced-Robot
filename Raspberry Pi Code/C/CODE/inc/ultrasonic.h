#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H               
#include "common.h"

#define ULTRASONIC_TRIG 4
#define ULTRASONIC_ECHO 17


void ultrasonic_init();
float get_distance();
#endif
