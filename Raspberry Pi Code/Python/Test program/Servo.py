from time import sleep
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

def setServoAngle(servo, angle):
	pwm = GPIO.PWM(servo, 50)
	pwm.start(8)
	dutyCycle = angle / 18. + 3.
	pwm.ChangeDutyCycle(dutyCycle)
	sleep(0.3)
	pwm.stop()
	
if __name__ == '__main__':
  servo = 22
  while(True):
    angle = int(input("please input an angle:"))
    GPIO.setup(servo,GPIO.OUT)
    setServoAngle(servo, angle)
	
