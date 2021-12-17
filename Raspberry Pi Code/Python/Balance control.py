#!/usr/bin/python

import smbus
import math
import time
import RPi.GPIO as GPIO

# 电源管理寄存器地址
power_mgmt_1 = 0x6b
power_mgmt_2 = 0x6c

def read_byte(adr):
    return bus.read_byte_data(address, adr)

def read_word(adr):
    high = bus.read_byte_data(address, adr)
    low = bus.read_byte_data(address, adr+1)
    val = (high << 8) + low
    return val

def read_word_2c(adr):
    val = read_word(adr)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val

def dist(a,b):
    return math.sqrt((a*a)+(b*b))
    #math.sqrt(x) 方法返回数字x的平方根。

def get_y_rotation(x,y,z):
    radians = math.atan2(x, dist(y,z))
    #math.atan2(y, x) 返回给定的 X 及 Y 坐标值的反正切值。
    return -math.degrees(radians)
    #math.degrees(x) 将弧度x转换为角度。

def get_x_rotation(x,y,z):
    radians = math.atan2(y, dist(x,z))
    return math.degrees(radians)


bus = smbus.SMBus(1) # or bus = smbus.SMBus(1) for Revision 2 boards
address = 0x68       # This is the address value read via the i2cdetect command

# Now wake the 6050 up as it starts in sleep mode
bus.write_byte_data(address, power_mgmt_1, 0)

#motor part
GPIO.setmode(GPIO.BCM)
GPIO.setup(18,GPIO.OUT)
GPIO.setup(6,GPIO.OUT)
GPIO.setup(5,GPIO.OUT)

GPIO.setup(19,GPIO.OUT)
GPIO.setup(13,GPIO.OUT)
GPIO.setup(26,GPIO.OUT)

pwm = GPIO.PWM(18,80)
pwm2 = GPIO.PWM(19,80)


pwm.start(0)
pwm2.start(0)


def Motor(speed):
    if(speed>0):
        if(speed>=55):
            speed=55
        pwm.ChangeDutyCycle(speed)
        pwm2.ChangeDutyCycle(speed)
        GPIO.output(6, False)
        GPIO.output(5, True)
        GPIO.output(26, False)
        GPIO.output(13,True)
    elif{speed<0}:
        if(speed<=-55):
            speed=-55
        pwm.ChangeDutyCycle(-speed)
        pwm2.ChangeDutyCycle(-speed)
        GPIO.output(6, True)
        GPIO.output(5, False)
        GPIO.output(26, True)
        GPIO.output(13, False)
    else:
        GPIO.output(6, False)
        GPIO.output(5, False)
        GPIO.output(26, False)
        GPIO.output(13, False)



#p = 20.0
#p = 2.5
#p = 3.4
p = 4.2
d = 0
midle_Value=-2
ratio = 15
last_gyro = 0.0

while True:
    
    time.sleep(0.02)
    start = time.time()
    

    
    gyro_xout = read_word_2c(0x43)
    gyro_yout = read_word_2c(0x45)
    gyro_zout = read_word_2c(0x47)
    
    print (' ')
    print ("gyro_xout : ", gyro_xout, " scaled: ", (gyro_xout / 131)) #倍率：±250°/s
    #print ("gyro_yout : ", gyro_yout, " scaled: ", (gyro_yout / 131))
    #print ("gyro_zout : ", gyro_zout, " scaled: ", (gyro_zout / 131))

    accel_xout = read_word_2c(0x3b)
    accel_yout = read_word_2c(0x3d)
    accel_zout = read_word_2c(0x3f)

    accel_xout_scaled = accel_xout / 16384.0 #倍率：±2g
    accel_yout_scaled = accel_yout / 16384.0
    accel_zout_scaled = accel_zout / 16384.0

    print ("accel_xout: ", accel_xout, " scaled: ", accel_xout_scaled)
    print ("accel_yout: ", accel_yout, " scaled: ", accel_yout_scaled)
    #print ("accel_zout: ", accel_zout, " scaled: ", accel_zout_scaled)

    print ("x rotation: " , get_x_rotation(accel_xout_scaled, accel_yout_scaled, accel_zout_scaled))
    #print ("y rotation: " , get_y_rotation(accel_xout_scaled, accel_yout_scaled, accel_zout_scaled))
    
    #==============================================================
    #pid part
    #==============================================================
    
    
    
    angle=get_x_rotation(accel_xout_scaled, accel_yout_scaled, accel_zout_scaled)
    last_x = angle

    
    #angle -100 +100
    #acc -10 +10

    gyro = accel_yout_scaled
    
    print("speed")
    speed = (midle_Value+angle)*p+(gyro-last_gyro)*d*ratio
    
    last_gyro = gyro
    
    speed = speed
    print(speed)

    Motor(speed)

    
    print("time")
    end = time.time()
    print(end-start)
 
