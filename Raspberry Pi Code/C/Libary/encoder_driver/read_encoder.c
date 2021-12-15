#include<stdio.h>
#include<sys/fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/unistd.h>
int main()
{
    int p,encoder[2];
    p= open("/dev/encoder1",O_RDONLY);
    printf("file op %d\n",p);
    while(1){
            read(p,encoder,8);
            printf("get encoder left %4d right %4d\r",encoder[0],encoder[1]);
            usleep(10000);
    }
    close(p);
    return 0;
}
