import os
import time
import numpy as np
import RPi.GPIO as GPIO
import traceback
import threading
from multiprocessing import Process, Queue
from subprocess import call
import subprocess
import socket
from threading import Thread
import base64
import os
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

def setServoAngle(servo, angle):
	pwm = GPIO.PWM(servo, 50)
	pwm.start(8)
	dutyCycle = angle / 18. + 3.
	pwm.ChangeDutyCycle(dutyCycle)
	time.sleep(0.3)
	pwm.stop()
	


def getLocalIp():

    '''Get the local ip'''

    try:

        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        s.connect(('8.8.8.8', 80))

        ip = s.getsockname()[0]

    finally:

        s.close()

    return ip



listensocket = socket.socket()

Port = 7654

maxConnections = 999

IP = socket.gethostname()



listensocket.bind((getLocalIp(),Port))

listensocket.listen(maxConnections)

print("Server started at " + IP + " on port " + str(Port))

# TCP server

angle_up_down = 50
angle_left_right = 50

move_flag = " "
def connectonProcess(clientsocket,queueLogin:Queue):

    message = clientsocket.recv(1024).decode()  # Receives Message

    global angle_up_down
    global angle_left_right
    if message == "Down":
        angle_up_down = angle_up_down + 10
        print(angle_up_down)
        servo = 17
        GPIO.setup(servo,GPIO.OUT)
        setServoAngle(servo, angle_up_down)
    elif message == "Up":
        angle_up_down = angle_up_down - 10
        print(angle_up_down)
        servo = 17
        GPIO.setup(servo,GPIO.OUT)
        setServoAngle(servo, angle_up_down)
    elif message == "Left":
        angle_left_right = angle_left_right + 10
        print(angle_left_right)
        servo = 22
        GPIO.setup(servo,GPIO.OUT)
        setServoAngle(servo, angle_left_right)
    elif message == "Right":
        angle_left_right = angle_left_right - 10
        print(angle_left_right)
        servo = 22
        GPIO.setup(servo,GPIO.OUT)
        setServoAngle(servo, angle_left_right)
    elif message == "Move1":
        move_flag = "Move1"
    elif message == "Move2":
        move_flag = "Move2"
    # Prints Message

    print(message)

def rpi_TCPServer(queueLogin:Queue):

    while True:

        clientsocket, address = listensocket.accept()
        threading.Thread(target=connectonProcess(clientsocket, queueLogin), name="userName").start()


if __name__ == '__main__':

    try:

        q = Queue()

        queueLogin = Queue()


        print("TCP Server")

        process_TCP_Server = Process(target=rpi_TCPServer,args=(queueLogin,))


        process_TCP_Server.start()
        
    except BaseException:

        traceback.print_exc()


