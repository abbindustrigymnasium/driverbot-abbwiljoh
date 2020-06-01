#include "EspMQTTClient.h"  //Installera bibliotek av samma namn
#include <Servo.h>

Servo servo;

void onConnectionEstablished();

EspMQTTClient client(
  "famjohansson",                                    // Wifi ssid
  "Nyttis98",                                       // Wifi password
  "maqiatto.com",                                  // MQTT broker ip
  1883,                                           // MQTT broker port
  "william.johansson@abbindustrigymnasium.se",   // MQTT username
  "creativetalk",                               // MQTT password
  "williamRacer",                              // Client name
  onConnectionEstablished,                    // Connection established callback
  true,                                      // Enable web updater
  true                                      // Enable debug messages
);


#define motorPinDir  0//D2  De "blå hålen" på Motorshielden
#define motorPinSpeed 5//D1

void setup() {
  servo.attach(14); //D5 på NodeMCU
  pinMode(motorPinDir, OUTPUT);
  pinMode(motorPinSpeed, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);         // Ledlampan på Esp:n

  Serial.begin(115200);
  servo.write(90);                   // Servot ska utgå från en rak position (Det skulle vara tråkigt om den bara svängde)
  digitalWrite(LED_BUILTIN, LOW);   // Lampan ska utgå från att vara avstängd

  delay(2000);
}

//bool off = false;
String address = "william.johansson@abbindustrigymnasium.se/";
String Direction = "Framåt";


void turn(bool left, int degrees) {
  if (left == true)
  { 
    degrees -= 90;

    if (degrees < 0)
    {
      degrees = 0;
      digitalWrite(motorPinDir, 1);
      analogWrite(motorPinSpeed, 900);
    }
    servo.write(degrees);
    Serial.println("Åker Höger!");
    client.publish(address+"directionlog","Bil: Åker Höger!");
  }
  else
  {

    degrees += 90;
    if (degrees > 180)
    {
      degrees = 180;
      digitalWrite(motorPinDir, 1);
      analogWrite(motorPinSpeed, 900);
    }
    servo.write(degrees);
    Serial.println("Åker Vänster");
    client.publish(address+"directionlog","Bil: Åker Vänster!");
  }


}

void drive(bool dir, int speed) {

  //Om du vill åka rakt fram eller bak
  servo.write(90);

  Serial.println("Åk!");

  Serial.println(speed);
  digitalWrite(motorPinDir, dir);
  analogWrite(motorPinSpeed, speed);

  digitalWrite(LED_BUILTIN, dir);

  if (!dir){
    Direction= "Bakåt";
  }
  else if (dir){
    Direction = "Framåt";
  }
  if (speed>0){
  Serial.println("Åker "+Direction+" med hastighet "+ speed);
  client.publish(address+"directionlog","Bil: Åker "+Direction+" med hastighet "+ speed);
  }
  else {
  Serial.println("Stannad");
  client.publish(address+"directionlog","Bil: Stannad");
  }
}

void onConnectionEstablished()
{

  client.subscribe(address+"direction", [] (const String & payload)
  {

    char info = payload.charAt(0);
    int length = payload.length();
    String value = payload.substring(1, length);  // Ändra till 2
    int speed = value.toInt();
    if (speed < 850){
      speed = 850;
    }
    if (info == 'f' || info == 'b'  )
    {
      bool dir = false;
      if (info == 'f'){
        dir = true;}
      drive(dir, speed);
    }
    else if (info == 'r' || info == 'l'  )
    {
      bool dir = false;
      if (info == 'r'){
        dir = true;}
      turn(dir, speed);
    }
    Serial.println(payload);

    if(payload.indexOf("har anslutits") > 0){
      client.publish(address + 'direction', payload);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      client.publish(address + 'directionlog', payload);
    }

  });

  client.publish(address + "direction", "This is a message");
}


void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
}