#!/bin/sh

echo "out" > "/sys/class/gpio/gpio21/direction"

while [ 1 ]
do
        echo 1 > "/sys/class/gpio/gpio21/value"
        sleep 0.005
        echo 0 > "/sys/class/gpio/gpio21/value"
        sleep 0.005
        echo "gpio out"
done
