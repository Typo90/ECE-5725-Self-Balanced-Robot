obj-m += encoder.o
KERNEL :=/usr/src/linux-headers-4.19.66-v7+/
all:
		make -C $(KERNEL) M=$(shell pwd) modules
clean:
		make -C $(KERNEL) M=$(shell pwd) clean

