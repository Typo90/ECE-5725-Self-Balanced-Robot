#ifndef __CONTROL_H
#define __CONTROL_H
#include "common.h"
 
#define PI 3.14159265
#define ZHONGZHI -3
extern int8_t on_flag;
extern  int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
void ctrl(void);
int balance(float angle,float gyro);
int velocity(int encoder_left,int encoder_right);
int turn(int encoder_left,int encoder_right,float gyro);
void Set_Pwm(int moto1,int moto2);
void turn_off_motor();
void Xianfu_Pwm(void);
uint8_t Turn_Off_check(float angle, int voltage);
void Get_Angle(uint8_t);
int myabs(int a);
#endif
