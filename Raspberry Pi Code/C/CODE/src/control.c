#include "control.h"    
#include "filter.h" 

int Balance_Pwm=0,Velocity_Pwm=0;
int8_t Flag_Target=0,on_flag=1;


void ctrl(void) 
{    
        Get_Angle(Way_Angle);  
            
        //printf("flag = %d\n",Flag_Target);
        if(Flag_Target)                                 
        {   

            Read_Encoder(&Encoder_Left,&Encoder_Right); 
            Balance_Pwm =balance(Angle_Balance,Gyro_Balance);                   //===ƽ��PID����  
            
            //Encoder_Left = Encoder_Right;
            //Encoder_Right = Encoder_Left;
            
            Velocity_Pwm=velocity(Encoder_Left,Encoder_Right);          //===�ٶȻ�PID����     ��ס���ٶȷ�����������������С�����ʱ��Ҫ����������Ҫ���ܿ�һ
            
            //Turn_Pwm    =turn(Encoder_Left,Encoder_Right,Gyro_Turn);
            //��Ϊ��
            
            printf("encoder left %3d,encoder right %3d\n",Encoder_Left,Encoder_Right);
            Moto1=Balance_Pwm - Velocity_Pwm;                            //===�������ֵ������PWM
            Moto2=Balance_Pwm - Velocity_Pwm;                            //===�������ֵ������PWM
            //printf("pwm %5d %5d\r",Moto1,Moto2);
            Xianfu_Pwm();
            if(on_flag&&(Turn_Off_check(Angle_Balance,0)==0))
                Set_Pwm(Moto1,Moto2);                                                           
            else
                Set_Pwm(0,0); 
             
           //printf("m1 m2 %d %d angle %f gyro %f\n",Moto1,Moto2,Angle_Balance,Gyro_Balance);
        }
        Flag_Target=!Flag_Target;   
} 

float kp=82,kd=0.4;
//float kp=72,kd=0.4;
//float kp=90, kd=0.2;
//float kp=90, kd=0.3;
//float kp=85, kd=0.3;
//float kp=85, kd=0.8;

//float kp=50, kd=1.0;

//float kp=130, kd=0.15;
//float kp=110, kd=1.2;

//float kp=70, kd=0.8;
int balance(float Angle,float Gyro)
{  
   float Bias;
     int balance;
     Bias=Angle-ZHONGZHI;       
     balance=(int)(kp*Bias+Gyro*kd);   
     //printf("%.3f %.3f %.3f %.3f %.3f\r",Bias,Angle,Gyro,kp,kd);
     return balance;
}

int velocity(int encoder_left,int encoder_right)
{  
     //encoder_left = encoder_right;
     static float Velocity,Encoder_Least,Encoder,Movement;
     static float Encoder_Integral,Target_Velocity;
     float kp=28,ki=0.14;
      

       

   //=============�ٶ�PI������=======================// 
        Encoder_Least =(encoder_left+encoder_right)-Movement;                    //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩 
        Encoder *= 0.8;                                                     //===һ�׵�ͨ�˲���       
        Encoder += Encoder_Least*0.2;                                       //===һ�׵�ͨ�˲���    
        Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
        Encoder_Integral=Encoder_Integral;                       //===����ң�������ݣ�����ǰ������
        if(Encoder_Integral>2000)      Encoder_Integral=2000;             //===�����޷�
        if(Encoder_Integral<-2000)      Encoder_Integral=-2000;              //===�����޷� 
        Velocity=Encoder*kp+Encoder_Integral*ki;                          //===�ٶȿ��� 
        if(!on_flag)   Encoder_Integral=0;
      return Velocity;
      //return 0.0;
}
void turn_off_motor()
{
    Set_Pwm(0,0);
    
}
void Set_Pwm(int moto1,int moto2)
{
        if(moto1>0)         
            GPIO_CLR=1<<AIN2,GPIO_SET=1<<AIN1;
        else           
            GPIO_SET=1<<AIN2,GPIO_CLR=1<<AIN1;
        PWMA=myabs(moto1);
        if(moto2>0) 
            GPIO_CLR=1<<BIN1,GPIO_SET=1<<BIN2;
        else        
            GPIO_SET=1<<BIN1,GPIO_CLR=1<<BIN2;
        PWMB=myabs(moto2);  
}


void Xianfu_Pwm(void)
{   
    int Amplitude=2000;    
    if(Moto1<-Amplitude) Moto1=-Amplitude;  
    if(Moto1>Amplitude)  Moto1=Amplitude;   
    if(Moto2<-Amplitude) Moto2=-Amplitude;  
    if(Moto2>Amplitude)  Moto2=Amplitude;           
}


uint8_t Turn_Off_check(float angle, int voltage)
{
    uint8_t temp;
    if(angle<-40||angle>40) // angle >40 shutdown motor
    {                       
        temp=1;  
        on_flag = 0;
        GPIO_CLR=1<<AIN1;                                            
        GPIO_CLR=1<<AIN2;
        GPIO_CLR=1<<BIN1;
        GPIO_CLR=1<<BIN2;
    }
    else
        temp=0;
    return temp;            
}

void Get_Angle(uint8_t way)
{ 
    float Accel_Y,Accel_Angle,Accel_Z,Gyro_X,Gyro_Z;
    Temperature=Read_Temperature();      //===��ȡMPU6050�����¶ȴ��������ݣ����Ʊ�ʾ�����¶ȡ�
    if(way==1)                           //===DMP�Ķ�ȡ�����ݲɼ��ж϶�ȡ���ϸ���ѭʱ��Ҫ��
    {   
        Read_DMP();                      //===��ȡ���ٶȡ����ٶȡ����
        Angle_Balance=Roll;             //===����ƽ�����
        Gyro_Balance=gyro[0];            //===����ƽ����ٶ�
        Gyro_Turn=gyro[2];               //===����ת����ٶ�
        Acceleration_Z=accel[2];         //===����Z����ٶȼ�
    }           
    else
    {
        Gyro_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //��ȡY��������
        Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //��ȡZ��������
        Accel_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //��ȡX����ٶȼ�
        Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //��ȡZ����ٶȼ�
        if(Gyro_X>32768)  Gyro_X-=65536;                       //��������ת��  Ҳ��ͨ��shortǿ������ת��
        if(Gyro_Z>32768)  Gyro_Z-=65536;                       //��������ת��
        if(Accel_Y>32768) Accel_Y-=65536;                      //��������ת��
        if(Accel_Z>32768) Accel_Z-=65536;                      //��������ת��
        Gyro_Balance= -Gyro_X;                                  //����ƽ����ٶ�
        Accel_Angle=atan2(Accel_Y,Accel_Z)*180/PI;                 //�������   
        Gyro_X=Gyro_X/16.4;                                    //����������ת�� 
        if(Way_Angle==2)            Kalman_Filter(Accel_Angle,Gyro_X);//�������˲�  
        else if(Way_Angle==3)       Yijielvbo(Accel_Angle,Gyro_X);    //�����˲�
        Angle_Balance=-angle;                                   //����ƽ�����
        Gyro_Turn=Gyro_Z;                                      //����ת����ٶ�
        Acceleration_Z=Accel_Z;                                //===����Z����ٶȼ� 
    }
}

int myabs(int a)
{          
    int temp;
    if(a<0)  
        temp=-a;  
    else 
        temp=a;
    return temp;
}



