#include "common.h"

uint8_t Way_Angle=2,Bi_zhang=0;   
int Temperature=366;                            //显示温度
float Distance=20; 
int Encoder_Left,Encoder_Right;             //
int Moto1,Moto2;                            //  
float Angle_Balance,Gyro_Balance,Gyro_Turn;           //平衡倾角 平衡陀螺仪 转向陀螺仪
float Acceleration_Z;


struct timeval time1,time2;
int dt;


void sig_handler(int arg)
{
    printf("get sigint signal\n");
    turn_off_motor();
    //do_sth_before_exit();
    exit(0);
}

void signal_init()
{
    struct sigaction act,oact;
    act.sa_handler = sig_handler;
    sigemptyset(&act.sa_mask); 
    act.sa_flags = SA_RESTART;
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
    sigaction(SIGINT,&act,&oact);
}

int main(void)
{      
        int err; 
        
        bcm2835_init();
        int file=i2c_init();    

        
        MPU6050_init();        
        
        motor_init();  
        
        Encoder_Init();
        
;
        
        key_init();
        
        signal_init();
        //sensor
        eint_init();
        register_eint_callback(ctrl);   

        
        while(1)
        {       
            key_process();
            //sleep(1);     
            
        } 
        do_sth_before_exit();
}
