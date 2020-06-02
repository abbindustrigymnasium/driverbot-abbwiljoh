#include "EspMQTTClient.h"  //Installera bibliotek av samma namn
#include <Servo.h>

Servo servo;

void onConnectionEstablished();

EspMQTTClient client(
  "",                                                // Wifi ssid
  "",                                               // Wifi password
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
String address = "william.johansson@abbindustrigymnasium.se/";  // Enklare för att använda mqtt
String Direction = "Framåt"; // Används i meddelanden


void turn(bool right, int degrees) {
  if (right == true)
  { 
    degrees -= 90;  // Servot på min bil är uppochned så höger är negativ riktning i vårt fall.

    if (degrees < 0) // Om servot svänger för mycket kan det skadas när det möts av motstånd från svängmekanismen.
    {
      degrees = 0;
      digitalWrite(motorPinDir, 1); // Bilen kör framåt när den svänger som standard, men den kan backa och svänga samtidigt
      analogWrite(motorPinSpeed, 900); // Bilen saktar ned i svängarna
    }
    servo.write(degrees); // Servot svänger alltså ett visst antal grader till höger
    Serial.println("Åker Höger!");
    client.publish(address+"directionlog","Bil: Åker Höger!");  //Skickar ett meddelande till loggern på hemsidan
  }
  else
  {
                      //| |                                           | |
    degrees += 90;    //v v   Samma som höger, fast åt andra hållet   v v
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

void drive(bool dir, int speed) { // dir = Framåt eller bakåt?  speed= hastighet

  //Om du vill åka rakt fram eller bak återställs servot till utgångspositionen (rakt)
  servo.write(90);

  Serial.println("Åk!");

  Serial.println(speed);
  digitalWrite(motorPinDir, dir);
  analogWrite(motorPinSpeed, speed);    //Ganska enkelt, framåt/bakåt och hastighet

  digitalWrite(LED_BUILTIN, dir);   // En liten "billykta"

  if (!dir){              // Om dir är false backar bilen och då vill vi att den ska säga det
    Direction= "Bakåt";
  }
  else if (dir){          // Det fanns en bugg där bilen sa att den backade hela tiden, denna rad är här för att förhindra det
    Direction = "Framåt";
  }
  if (speed>0){
  Serial.println("Åker "+Direction+" med hastighet "+ speed);
  client.publish(address+"directionlog","Bil: Åker "+Direction+" med hastighet "+ speed);   //Skickar till loggern på hemsidan
  }
  else {
  Serial.println("Stannad");
  client.publish(address+"directionlog","Bil: Stannad");    //Skickar när den är stannad till loggern
  }
}

void onConnectionEstablished()
{

  client.subscribe(address+"direction", [] (const String & payload)  
  {           //För att få in instruktionerna från hemsidan

    char info = payload.charAt(0);    //I exemplet f1000 är "f" den första charen som säger framåt, bakåt, höger, vänster
    int length = payload.length();
    String value = payload.substring(1, length);  //I f1000 är "1000" den hastighet eller gradtal vi vill veta
    int speed = value.toInt();    // Måste ha en int för funktionerna.
    if (speed < 850){         // Om hastigheten är under ~850 tjuter bara motorn och rör sig inte, därför måste hastigheten vara högre
      speed = 850;
    }
    if (info == 'f' || info == 'b'  ) //Framåt eller bakåt
    {
      bool dir = false;
      if (info == 'f'){
        dir = true;}
      drive(dir, speed);    //Kallar funktionen för att köra framåt eller bakåt med en viss hastighet
    }
    else if (info == 'r' || info == 'l'  ) //Höger eller vänster
    {
      bool dir = false;
      if (info == 'r'){
        dir = true;}
      turn(dir, speed); // Kallar funktionen för att svänga
    }
    Serial.println(payload);

    if(payload.indexOf("har anslutits") > 0){             //Letar i meddelandet efter anslutningsmeddelandet från hemsidan
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      client.publish(address + 'directionlog', payload);  //Skickar meddelande till hemsidan så att man vet att bilen är ansluten!
    }

  });

  client.publish(address + "direction", "Bil: Hej från bilen");
}


void loop() {
  // put your main code here, to run repeatedly:
  client.loop();      //Processen loopar
}
