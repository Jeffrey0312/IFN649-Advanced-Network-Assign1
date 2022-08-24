from email import message
import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT");
    print("Connection returned result: " + str(rc));

    client.subscribe("ifn649")

def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload));

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("13.211.136.173", 1883, 60)

client.loop_forever()