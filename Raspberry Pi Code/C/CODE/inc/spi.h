#ifndef __SPI_H
#define __SPI_H

#include "common.h"
typedef struct spi_dev{
	uint8_t mode;
	uint8_t BPW;
	uint16_t delay;

	uint32_t max_clock;
	int fd;
} spi_dev_t;


void spi_init(char *spi_device,int max_clock);
int spi_data_rw(unsigned char * tx, unsigned char * rx, int len);


#endif

//------------------End of File----------------------------
