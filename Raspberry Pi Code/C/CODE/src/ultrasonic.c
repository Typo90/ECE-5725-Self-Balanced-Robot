#include "ultrasonic.h"

void ultrasonic_init()
{     
    bcm2835_gpio_fsel(ULTRASONIC_ECHO, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(ULTRASONIC_TRIG, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_set_pud(ULTRASONIC_ECHO, BCM2835_GPIO_PUD_DOWN);
    bcm2835_gpio_write(ULTRASONIC_TRIG, LOW);
}



float get_distance()
{
        float dis;
        long dtime;
        struct timeval time1,time2;
           
        bcm2835_gpio_write(ULTRASONIC_TRIG, HIGH);
        bcm2835_delayMicroseconds(10);
        bcm2835_gpio_write(ULTRASONIC_TRIG, LOW);        
        
        
        while(bcm2835_gpio_lev(ULTRASONIC_ECHO)==LOW)
        {}
        gettimeofday(&time1,NULL);
        while(bcm2835_gpio_lev(ULTRASONIC_ECHO)==HIGH)
        {}
        gettimeofday(&time2,NULL);

        
        dtime = (time2.tv_sec * 1000000 + time2.tv_usec)-(time1.tv_sec * 1000000 + time1.tv_usec);
        dis = (float)dtime/ 1000000 * 34000 / 2;
           // printf("get distance %f\n",dis);
        return dis;
}
    /*
{
    float dis;
    long dtime;
    struct timeval time1,time2;
     GPIO_SET=TRIG;
        // wait a bit 
     usleep(10);
        // turn it off 
     GPIO_CLR=TRIG;        
        // wait a bit 
        
        while(GPIO_GET_VAL(ECHO)==LOW)
        {}
        gettimeofday(&time1,NULL);
        while(GPIO_GET_VAL(ECHO)==HIGH)
        {}
        gettimeofday(&time2,NULL);
        
        dtime = (time2.tv_sec * 1000000 + time2.tv_usec)-(time1.tv_sec * 1000000 + time1.tv_usec);
        dis = (float)dtime/ 1000000 * 34000 / 2;
        printf("get distance %f\n",dis);
        return dis;        
    }
*/
