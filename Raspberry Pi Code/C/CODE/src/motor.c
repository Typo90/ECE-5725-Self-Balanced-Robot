#include "motor.h"


void PWM_init(void)
{
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_2);
    bcm2835_pwm_set_mode(0, 1, 1);
    bcm2835_pwm_set_mode(1, 1, 1);
    bcm2835_pwm_set_range(0, 2000);
    bcm2835_pwm_set_range(1, 2000);
    bcm2835_pwm_set_data(0, 0);
    bcm2835_pwm_set_data(1, 0);
}

void motor_init()
{
	 //motor
    INP_GPIO(AIN1);
    OUT_GPIO(AIN1);
    INP_GPIO(BIN1);
    OUT_GPIO(BIN1);
    INP_GPIO(AIN2);
    OUT_GPIO(AIN2);
    INP_GPIO(BIN2);
    OUT_GPIO(BIN2);
    bcm2835_gpio_fsel(PWMA_PIN, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_gpio_fsel(PWMB_PIN, BCM2835_GPIO_FSEL_ALT5);
	
	PWM_init();
}


