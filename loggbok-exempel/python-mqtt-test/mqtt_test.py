import paho.mqtt.client as mqtt
import time

def on_connect(client, userdata, flags, rc):
    if rc== 0:
        print('Connected OK')
    else:
        print('Bad connection. returned code', rc)

def on_log(client, userdata, level, buf):
    print('Log: '+ buf)

def on_disconnect(client, userdata, flags, rc= 0):
    print('Disconnected result code '+str(rc))

def on_message(client, userdata, msg):
    topic= msg.topic
    m_decode= str(msg.payload.decode('utf-8'))
    print('Message received\nTopic:',topic, m_decode)

broker = 'maqiatto.com'
client = mqtt.Client(client_id='hejHEJ', transport='websockets')

client.ws_set_options()
client.username_pw_set(username='william.johansson@abbindustrigymnasium.se', password='creativetalk')
client.will_set('william.johansson@abbindustrigymnasium.se/direction', 'f0')

client.on_connect= on_connect   #Callback funktioner,kallade
client.on_disconnect= on_disconnect
client.on_log= on_log
client.on_message= on_message

print('Connecting to broker', broker)
client.connect(host = broker, port=8883)

client.loop_start()
client.publish('william.johansson@abbindustrigymnasium.se/direction', 'f0')

def publish(prefix= 'william.johansson@abbindustrigymnasium.se',topic= '/direction', msg= 'f0'):
    client.publish(prefix+topic, msg)


client.loop_stop()
# client.disconnect()