#include "key.h"
void key_init()
{
    int res,fd;
    char gpio_num[]="24";
    res =access("/sys/class/gpio/gpio24/value",F_OK);
    if(res<0)
    {
        printf("no gpio24\n");
        fd =open("/sys/class/gpio/export",O_WRONLY);
        write(fd,gpio_num,2);
        close(fd);
    }
    char gpio_num1[]="25";
    res =access("/sys/class/gpio/gpio25/value",F_OK);
    if(res<0)
    {
        printf("no gpio25\n");
        fd =open("/sys/class/gpio/export",O_WRONLY);
        write(fd,gpio_num1,2);
        close(fd);
    }
    //低电平触发
    char dir[]="in";
    fd= open("/sys/class/gpio/gpio24/direction",O_WRONLY);
    write(fd,dir,sizeof(dir));
    close(fd);
    fd= open("/sys/class/gpio/gpio25/direction",O_WRONLY);
    write(fd,dir,sizeof(dir));
    close(fd);
    char edge[]="both";
    fd= open("/sys/class/gpio/gpio24/edge",O_WRONLY);
    write(fd,edge,sizeof(edge));
    close(fd);
    fd= open("/sys/class/gpio/gpio25/edge",O_WRONLY);
    write(fd,edge,sizeof(edge));
    close(fd);
    bcm2835_gpio_set_pud(KEYL,BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(KEYR,BCM2835_GPIO_PUD_UP);
    
}
void key1_things_to_do()
{
    on_flag=!on_flag;
}
void key_process()
{
    int res,n1=0,n2=0;
    struct timeval time1,time2,time3,time4;
    int8_t ksign1=0,ksign2=0;
    struct pollfd fdset[2];
    char val;
    int p1= open("/sys/class/gpio/gpio24/value",O_RDWR);
    int p2= open("/sys/class/gpio/gpio25/value",O_RDWR);
    fdset[0].fd=p1;
    fdset[0].events = POLLPRI;
    fdset[0].revents = 0;
    fdset[1].fd=p2;
    fdset[1].events = POLLPRI;
    fdset[1].revents = 0;
    
    while(1){           
        res = poll(fdset,2,-1);
        if(res > 0)
        {
            if(fdset[0].revents!=0)
            {
                lseek(fdset[0].fd,0,SEEK_SET);
                read(fdset[0].fd,&val,1);
                
                if(!ksign1&&val=='0')
                {
                    ksign1=1;
                    gettimeofday(&time1,NULL);
                }
                if(val=='1')
                {
                    if(ksign1)
                    {
                        gettimeofday(&time2,NULL);
                        if(time2.tv_sec*1000+time2.tv_usec/1000-time1.tv_sec*1000-time1.tv_usec/1000<100)
                            continue;
                        printf("key1 pressed %d\n",n1++);
                        ksign1=0;
                        key1_things_to_do();
                    }
                    
                }
                
            }
            if(fdset[1].revents!=0)
            {
                lseek(fdset[1].fd,0,SEEK_SET);
                read(fdset[1].fd,&val,1);
                if(!ksign2&&val=='0')
                {
                    ksign2=1;
                    gettimeofday(&time3,NULL);
                }
                if(val=='1')
                {
                    if(ksign2)
                    {
                        
                        gettimeofday(&time4,NULL);
                        if(time4.tv_sec*1000+time4.tv_usec/1000-time3.tv_sec*1000-time3.tv_usec/1000<100)
                            continue;
                        printf("key2 pressed %d\n",n2++);
                        ksign2=0;
                    }
                    
                }
                
            }
    
        }
        
    }
}
