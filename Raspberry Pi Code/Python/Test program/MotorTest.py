import RPi.GPIO as GPIO
import time
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

#PWMA
GPIO.setup(18,GPIO.OUT)
#AIN1
GPIO.setup(6,GPIO.OUT)
#AIN2
GPIO.setup(5,GPIO.OUT)

#PWMB
GPIO.setup(19,GPIO.OUT)
#BIN1
GPIO.setup(13,GPIO.OUT)
#BIN2
GPIO.setup(26,GPIO.OUT)


pwm = GPIO.PWM(18,50)
pwm2 = GPIO.PWM(19,50)

pwm.start(0)
pwm2.start(0)



#time.sleep(2)


#clockwise
GPIO.output(5,GPIO.LOW)
GPIO.output(6,GPIO.HIGH)
GPIO.output(13,GPIO.LOW)
GPIO.output(26,GPIO.HIGH)

pwm.ChangeDutyCycle(50)
pwm2.ChangeDutyCycle(50)
time.sleep(3)
pwm2.ChangeDutyCycle(100)
pwm.ChangeDutyCycle(100)
time.sleep(3)


pwm.start(0)
pwm2.start(0)
#counter-clockwise
GPIO.output(6,GPIO.HIGH)
GPIO.output(5,GPIO.LOW)
GPIO.output(26,GPIO.HIGH)
GPIO.output(13,GPIO.LOW)

pwm.ChangeDutyCycle(50)
pwm2.ChangeDutyCycle(50)
time.sleep(3)
pwm2.ChangeDutyCycle(100)
pwm.ChangeDutyCycle(100)
time.sleep(3)




GPIO.output(5,GPIO.LOW)
GPIO.output(6,GPIO.LOW)
GPIO.output(13,GPIO.LOW)
GPIO.output(26,GPIO.LOW)
GPIO.cleanup()

