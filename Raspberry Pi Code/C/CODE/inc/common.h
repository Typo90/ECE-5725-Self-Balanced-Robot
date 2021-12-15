#ifndef __COMMON_H
#define __COMMON_H    


#include <bcm2835.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <poll.h>
#include <termios.h>
#include <signal.h>
#include <sys/select.h>


#include "iic.h"


#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"

#include "motor.h"
#include "control.h"
#include "encoder.h"
#include "eint.h"
#include "key.h"


/*
 *  GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
 */
#define INP_GPIO(g) *(bcm2835_gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(bcm2835_gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(bcm2835_gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

/* sets bits which are 1 ignores bits which are 0 */
#define GPIO_SET *(bcm2835_gpio+7)
/* clears bits which are 1 ignores bits which are 0 */
#define GPIO_CLR *(bcm2835_gpio+10)

//#define GPIO_GET_VAL(pin) ((*(bcm2835_gpio+13+(pin)/32))&(1<<((pin)%32)))?1:0

extern uint8_t Way_Angle,Bi_zhang;  
extern uint8_t Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu;  
extern int Temperature; 
extern float Distance;
extern int Encoder_Left,Encoder_Right;                     //左右编码器的脉冲计数
extern int Moto1,Moto2;                                     //电机PWM变量 应是motor的 向moto致敬  
extern float Angle_Balance,Gyro_Balance,Gyro_Turn;           //平衡倾角 平衡陀螺仪 转向陀螺仪
extern float Acceleration_Z;

void do_sth_before_exit();


#endif
