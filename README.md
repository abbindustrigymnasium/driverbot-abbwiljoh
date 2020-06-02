# Driverbot-William Johansson

### Videogenomgång!
* [Redovisning av kod](https://www.youtube.com/watch?v=j-S3EtqVBAM&feature=youtu.be "YouTube")
* [Redovisning av konstruktion](https://youtu.be/Zw0bGkSxXyo "YouTube")

#### Innehåll:
   * [Kod för bil](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/Arduino-Bil/RacerMQTT1/RacerMQTT1.ino "Racer MQTT1")
   
      - [Python-stryning](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/python-control/pygame_car.py "pygame_car.py")
           * [Python Test](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/tree/master/loggbok-exempel/python-mqtt-test "Test-kod")
      
      - [Vue-styrning](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/tree/master/vue "vue")
      
      
   * [Loggbok för lektionerna](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/loggbok.md "Loggbok")


### Hemsida för styrning:
[Länk](https://www.youtube.com/watch?v=dQw4w9WgXcQ "Hemsidan är ännu ej uppe!") (Hemsidan är ej ännu uppe!)

### Kommenterad kod:
Eftersom det finns så många filer har jag endast kommenterat de viktigaste filerna och dem jag jobbat som mest med. De finns här:
  * [Arduinokod](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/Arduino-Bil/RacerMQTT1/RacerMQTT1.ino "RacerMQTT1")
  * [Joystick](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/tree/master/python-control "Python-Stryning")
  * [Store](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/vue/src/store/store.js "store.js")
  * [Buttons](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/vue/src/components/Buttons.vue "Buttons.vue") (Det finns två versioner men jag tycker det räcker med en kommenterad fil.)
  * [App](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/vue/src/App.vue "App.vue")

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
![alt_text](https://raw.githubusercontent.com/abbindustrigymnasium/driverbot-abbwiljoh/master/Bilder/Cargame_bild.jpg "`Spelet´")

### Hemsida/Vue-styrning
![alt_text](https://raw.githubusercontent.com/abbindustrigymnasium/driverbot-abbwiljoh/master/Bilder/Startsida_bild.jpg "Startsida")

Hemsidan är gjord med hjälp av Vue, och bygger starkt på den kod som kan hittas [här](https://github.com/abbindustrigymnasium/Driverbot/tree/master/Hemsida "Driverbot"). Grunden till hemsidan fungerar mycket väl, så jag har inte gjort så många ändringar när det kommer till de grundläggande funktionella, men jag har lagt till vissa saker som ska förbättra funktionen och gör hemsidan lite snyggare. 

Man börjar på startsidan, där man möts av en knapp där man kan välja att ansluta. Klickar man den och anslutningen till MQTT-brokern lyckas kommer man vidare till styrsidan, som består av en kontrollpanel och en logger. Kontrollpanelen är ganska enkel att förstå: Klickar du framåt så åker bilen framåt! Det viktigaste jag tycker jag har bidragit med är ```SubscribeLog()```, en funktion som tar meddelanden från bilen och lägger till dem i loggern, vilket inte skedde i den ursprungliga hemsidan.

Jag har inte jobbat med Vue så mycket under våra projekt, jag har mest hållit på i backenden och "lekt" med arduinokod, så det här blir mitt första officella projekt med Vue. Ja, jag kunde ha gjort en hemsida från grunden,och den hade antagligen haft de grundläggande funktioner som behövs för bilen. Men att använda en grund har gett mig lite bättre förståelse för hur Vue fungerar, och jag tror inte jag skulle kunnat fördjupa mig med en hemsida gjord från grunden, så i slutändan är jag ändå nöjd med det jag gjort.

![alt_text](https://raw.githubusercontent.com/abbindustrigymnasium/driverbot-abbwiljoh/master/Bilder/Logger_bild.jpg "Styrsida + logger")
##### [CSS Gradient Generator](https://cssgradient.io "Här finns riktigt snygga övergångsfärger!")

### Problem & Svårigheter
* Servoplacering
  - Servot fungerar väl, och har nog med styrka och grepp för att kunna svänga väl. Problemet är att den printade delen som håller servot på plats på legot, men något jag inte tänkte på var mellanrummet mellan hålen. Detta har gjort att servot sitter förskjutet ett steg åt höger, den är inte centrerad. Detta gör att det blir svårare för servot att får hjulen att snurra och att den del som kopplar servot till axeln hoppar av efter några svängar.
  Några lösningar till detta problem skulle kunna vara att:
    - Rita om delen och båda sidor med det avstånd som behövs (7.97/2 mm per sida) så att den är centrerad.
    - Bygga en anordning där servot hänger fritt och kan justeras åt sidan för att centrera axeln.
   
* Svag motor:
  - Den analoga signal som går till motorn måste vara över ~850, annars står motorn bara och tjuter utan att göra något. Detta har dock åtgärdats rätt så enkelt genom att:
    - Begränsa hastigheten från 850-1000 i koden (utan att förstöra möjligheten att skicka nollvärden).
