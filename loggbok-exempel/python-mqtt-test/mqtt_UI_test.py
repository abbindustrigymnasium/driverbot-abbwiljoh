import mqtt_test as m

stop = False

print('*Use WASD to turn\n*Write ´stop´ to stop program, enter to brake\n(Not case-sensitive)')

while stop == False:
    a = input('>')
    a= a.upper()
    if a== 'W':
        m.publish(msg='f1000')
    elif a== 'A':
        m.publish(msg= 'r90')
    elif a== 'S':
        m.publish(msg='b1000')
    elif a == 'D':
        m.publish(msg= 'l90')
    elif a == 'STOP':
        m.publish(msg= 'f0')
        stop == True
        m.client.disconnect()
        break
    else:
        m.publish(msg= 'f0')       
    