#include "eint.h"


void eint_init()
{
	char gpio_num[]="23";
	int fd =access("/sys/class/gpio/gpio23/value",F_OK);
	if(fd<0)
	{
		printf("no file value\n");
		fd =open("/sys/class/gpio/export",O_WRONLY);
		write(fd,gpio_num,2);
		close(fd);
	}
	//下降沿触发
	fd= open("/sys/class/gpio/gpio23/edge",O_WRONLY);
	char edge[]="falling";
	write(fd,edge,sizeof(edge));
	close(fd);
}

pthread_t p_cb;
int out_level=HIGH;
void *p_eint(void *args)
{
	int res;
	struct pollfd fdset;
	char val;
	int p= open("/sys/class/gpio/gpio23/value",O_RDWR);
	fdset.fd=p;
	fdset.events = POLLPRI;
	fdset.revents = 0;
	callback cb=args;
	bcm2835_gpio_fsel(RPI_GPIO_P1_26, BCM2835_GPIO_FSEL_OUTP);
	while(1){			
		res = poll(&fdset,1,3000);
		lseek(fdset.fd,0,SEEK_SET);
		read(fdset.fd,&val,1);
		//printf("val %c events %d %d\n",val,fdset.events,fdset.revents);
		bcm2835_gpio_write(RPI_GPIO_P1_26,out_level);
		out_level=!out_level;
		if(res>0)
			cb();
		else if(res ==0)
			printf("eint poll timeout\n");
		else
			printf("eint poll error\n");
    }
    close(p);
	return 0;
}

void register_eint_callback(callback cb)
{
	int	err = pthread_create(&p_cb,NULL,p_eint,cb);
	if(err != 0)
	{
		printf("create p_cb failed\n");
	}
	
}