import RPi.GPIO as GPIO
import time
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

#PWMA
GPIO.setup(12,GPIO.OUT)
#AIN1
GPIO.setup(20,GPIO.OUT)
#AIN2
GPIO.setup(21,GPIO.OUT)

#PWMB
GPIO.setup(10,GPIO.OUT)
#BIN1
GPIO.setup(11,GPIO.OUT)
#BIN2
GPIO.setup(9,GPIO.OUT)


pwm = GPIO.PWM(12,50)
pwm2 = GPIO.PWM(10,50)

pwm.start(0)
pwm2.start(0)

pwm2.ChangeDutyCycle(0)
pwm.ChangeDutyCycle(0)



#time.sleep(2)







GPIO.output(20,GPIO.LOW)
GPIO.output(21,GPIO.LOW)
GPIO.output(11,GPIO.LOW)
GPIO.output(9,GPIO.LOW)
GPIO.cleanup()

