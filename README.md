# Driverbot-William Johansson

#### Innehåll:
   * Kod för bil
   
      - [Python-stryning](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/python-control/pygame_car.py "pygame_car.py")
           * [Python Test](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/tree/master/loggbok-exempel/python-mqtt-test "Test-kod")
      
      - [Vue-styrning](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/tree/master/vue "vue")
      
      
   * [Loggbok för lektionerna](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/loggbok.md "Loggbok")


### Hemsida för styrning:
[Länk](https://www.youtube.com/watch?v=dQw4w9WgXcQ "Hemsidan är ännu ej uppe!") (Hemsidan är ej ännu uppe!)

### Externt innehåll:
  * [Pythonprojekt](https://github.com/abbindustrigymnasium/programmering-1-miniprojekt-abbwiljoh "Valsimulator")
  
## Bilen och dess styrning:
![alt-text](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/loggbok-exempel/BilBildCropped.png "Bilen")

Bilen går på en TT-motor och en sg90 servo och är byggd med lego och några 3D-printade delar. Bilen tar MQTT-värden från hemsidan eller pythonspelet och kör enligt de angivna instruktionerna. Stryningen sker från ett pythonspel där man får en "joystick" att röra sig som ett gammalt bilspel och använder tekniker man enkelt kan hitta på nätet. Hemsidan är skirven med hjälp av Vue, ett framework som gör det enklare att göra snygga hemsidor och bygger på en färdiggjord hemsida. Jag har inte ändrat på de grundläggande funktionerna hos hemsidan men jag har lagt till mina egna egenskaper utöver vissa kosmetiska ändringar.

### Arduinokod:
Arduinokodens funktion är att ta emot instruktioner, styra bilen enligt instruktionerna och sedan skicka ett meddelande tillbaka till hemsidan där det sägs vad bilen gjort. Enligt koden fortsätter bilen göra det den blivit tillsagd, tills den får nya direktiv eller stängs av manuellt, vilket är fördelaktigt hos en radiostyrd bil då det skulle vara jobbigt att behöva pumpa framåt-knappen hela tiden. Skulle vi designat en normal bil skulle det förstås vara en säkerhetsrisk, men eftersom det är en låtsasbil kommer vi undan med detta i det här fallet. 

### Konstruktion
På bilden kan man se att bilen är bil-formad, alltså att den har fyra hjul och ser ganska verklighetstrogen ut. Det finns 5 stycken 3D-printade delar: Två hållare som ska hålla motorn och servot, samtidigt som de är kompatibla med lego technic-bitar, en liten adapter som omvandlar servots axel till en lego axel, och två stycken adaptrar som sitter mellan motorns och hjulens axlar. Alla variationer av delar kan ses på bilden ovan.

### Python-styrning
##### För Python-styrning:
```
pip install paho-mqtt

pip install pygame
```
Pythonstyrningen var en idé jag fick efter att ha sett olika versioner av tetris och andra klassiska spel återskapade med pygame. Jag undrade om jag kunde få ett spel interagera med verkligheten, vilket det visade sig att jag kunde. En annan stor anledning var att jag gärna ville ha tillgång till piltangenterna, eftersom det skulle göra styrningen mycket smidigare ään att behöva dra en mus över skärmen. För att uppnå detta har jag följt dokumentationer och artiklar om hur Pygame och Paho-MQTT fungerar för python. Det är inte ett imponerande spel, men det fyller sin funktion och det fyller den väl.

### Hemsida/Vue-styrning
To be continued...

....
....

### Problem
* Servot
* Motorn <800
* ...?
