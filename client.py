from email import message
import paho.mqtt.client as mqtt
import serial
import time
import string

ser = serial.Serial("/dev/rfcomm1", 9600)
def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT");
    print("Connection returned result: " + str(rc));

    client.subscribe("ifn649")

def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload));
    ser.write(str.encode('LED ON'))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("13.211.136.173", 1883, 60)

client.loop_forever()  