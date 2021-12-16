# ECE5725-Self-Balanced-Robot
These are the codes of self-balanced Robot for the ECE 5725 Design with Embedded Operating Systems in Cornell University.

## First You Need to Know

**Components Need:** 

Raspberry Pi *1

MPU6050 *1

12V motors with encoder *2

TB6612 *1 (Suggestion: Prepare more than 1, it is easily to burn )*

Pi Camera  * 1

Gimbal (2 Servos that help Camera to move ) *1

Bread board and some pin-hole wires



The balanced robot is a really complicated system and you need much time and patience! Good Luck

By the way, feel **Free** to contact us! Our email are yp284@cornell.edu and yl2237@cornell.edu. ( We only can see the email that ends in edu )

## How to start with CODE?

I will display the code step by step to show how to work.

You need to connect the Raspberry Pi to all the components like the picture shown below.

# Raspberry Pi code

This is our Self-Balanced Robot core control program.  We write two version of control program in **C** and **Python**.

The C code works successfully to balanced robot so I will follow the C code to tell you how to start.

We didn't success with the python code but we also put our python code that maybe you can improve it!

## C code

## Step 1: Install **bcm2835**  and **libi2c-dev**

We provide a bcm2835 library in the Library folder and you can also download it from official website

```shell
#Make Sure You are now in ../bcm2835-1.64
./configure
make
sudo make check
sudo make install
```

libi2c-dev is default installed on your Linux kernel.

## Step2: Load **encoder** module

We suppose you are familiar with Linux module programing.

```shell
#Make Sure You apt is the latest
sudo apt-get upgrade
#Then install the headrs
sudo apt-get install raspberrypi-kernel-headers
```

With the kernel updated, the header will also changed. You can check your headers in the /usr/src/linux-headers-x.xx.xx and then modify the Makefile file to your kernel version.

```shell
#Make sure you are now in ../Libary/encoder_driver

obj-m += encoder.o
KERNEL :=/usr/src/linux-headers-4.19.66-v7+/
all:
		make -C $(KERNEL) M=$(shell pwd) modules
clean:
		make -C $(KERNEL) M=$(shell pwd) clean

#Change the KERNEL :=/usr/src/linux-headers-4.19.66-v7+/ to your KERNEL :=/usr/src/linux-headers-x.xx.xxxx/
```

Once you set, use the command to compile the **encoder** module

```shell
sudo make clean
sudo make all
sudo make
```

After compiling, we need to load our module by the following command.

```shell
sudo insmod encoder.ko
```

And we can use the command to make sure the encoder module is successfully loaded 

```shell
sudo ismod
```

![image-20211215182541134](\Pictures\lsmod encoder.png)

## Step3: Compile C Program

Now, all the pre-requirement are set! Now we can run the control program.

```shell
#Make sure you are now in ../C/CODE
sudo make clean
sudo make all
sudo make
sudo ./main
```

# Code details 
