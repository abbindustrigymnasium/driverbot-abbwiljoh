#include "EspMQTTClient.h"
//Install libraries PubSubClient and EspMQTTClient


void onConnectionEstablished();

EspMQTTClient client(
  "ABB_Indgym_Guest",           // Wifi ssid
  "Welcome2abb",           // Wifi password
  "maqiatto.com",  // MQTT broker ip
  8883,             // MQTT broker port
  "william.johansson@abbindustrigymnasium.se",            // MQTT username
  "Valross83",       // MQTT password
  "WiljamClient",          // Client name
  onConnectionEstablished, // Connection established callback
  true,             // Enable web updater
  true              // Enable debug messages
);



#define led_pin 14


void setup() {
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  Serial.begin(115200);
}

bool off = false;

void lampa() {
  if (off == true)
  {
    Serial.println("Släckt!");
    off = false;
  }
  else
  {
    off = true;

    Serial.println("Släckt!");
  }

  digitalWrite(led_pin, off);

}

void onConnectionEstablished()
{
  client.subscribe("william.johansson@abbindustrigymnasium.se/lamp", [] (const String & payload)
  {
    Serial.println(payload);
    if (payload == "on")
      //onlampa();
    lampa();
  });

  client.publish("william.johansson@abbindustrigymnasium.se/lamp", "This is a message");

  client.executeDelayed(5 * 1000, []() {
    client.publish("william.johansson@abbindustrigymnasium.se/lamp", "This is a message sent 5 seconds later");
  });
}


void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
}
