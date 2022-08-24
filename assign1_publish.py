import serial
import time
import string
import paho.mqtt.publish as publish

#the sender rfcomm0

ser = serial.Serial("/dev/rfcomm0", 9600)
ser.write(str.encode('Start\r\n'))

while True:
    if ser.in_waiting > 0:
        rawserial = ser.readline()
        cookedserial = rawserial.decode('UTF-8').strip('\r\n')
        print(cookedserial)
        publish.single("ifn649", cookedserial, hostname="13.211.136.173")