#include"spi.h"
#include <linux/spi/spidev.h>

spi_dev_t spi_data;

void spi_init(char *spi_device,int max_clock)
{
    //device
    int ret = 0; 
	int fd;
    if((fd = open(spi_device, O_RDWR )) < 0)  {
        perror("Failed to open SPI device.\n");  
        exit(1); 
    } else {
        printf("open : %s\r\n", spi_device);
    }
	
    spi_data.mode = 0;
	spi_data.max_clock = max_clock;
	spi_data.fd = fd;
	spi_data.BPW = 8;
	spi_data.delay = 0;

	if (ioctl (fd, SPI_IOC_WR_BITS_PER_WORD, &spi_data.BPW) < 0) return NULL;
	if (ioctl (fd, SPI_IOC_RD_BITS_PER_WORD, &spi_data.BPW) < 0) return NULL;

	if (ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_data.max_clock)   < 0) return NULL;
	if (ioctl (fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_data.max_clock)   < 0) return NULL;
	
	if (ioctl (fd, SPI_IOC_WR_MODE, &spi_data.mode)         < 0) return NULL;
	if (ioctl (fd, SPI_IOC_RD_MODE, &spi_data.mode)         < 0) return NULL;
}


int spi_data_rw(unsigned char * tx, unsigned char * rx, int len)
{
	struct spi_ioc_transfer spi;
    memset(&spi,0,sizeof(spi));

	spi.tx_buf        = (unsigned long)tx;
	spi.rx_buf        = (unsigned long)rx;
	spi.len           = len ;
	spi.delay_usecs   = spi_data.delay;
	spi.speed_hz      = spi_data.max_clock;
	spi.bits_per_word = spi_data.BPW ;


	return ioctl (spi_data.fd, SPI_IOC_MESSAGE(1), &spi);
}

