#include "common.h"

int encoderp;
void Encoder_Init()
{
    encoderp= open("/dev/encoder1",O_RDONLY);
    if(encoderp<0)
        printf("open encoder failed\n");
    }


void Read_Encoder(int *left,int *right)
{
    int buf[2];
    read(encoderp,buf,8);
    *left = buf[0];
    *right = buf[1];   
   // printf("left %d,right %d\n",buf[0],buf[1]);
    
}
