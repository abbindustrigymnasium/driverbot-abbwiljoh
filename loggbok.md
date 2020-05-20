# LOGGBOK TEKNIK DISTANSSTUDIER
#### William Johansson

Bilen i sitt tidiga stadie: 
![alt-text](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/blob/master/loggbok-exempel/BilBildCropped.png "Williams Bild")


-------------

## Måndag 23/3 (12.05-16.10)
Jag har jobbat med bilen: kopplat servot till NodeMCU:n och försökt få bilen att svänga och köra samtidigt. 
Har stött på problem med att TT-Motorn tjuter utan att köra, och har påbörjat en felsökning för att se vad det kan bero på. 

-------------

## Tisdag 24/3 (8.10-10.55)
Ellära och beräkningar. Det gick bra

## Tisdag 24/3 (12.05-16.10)
Bilen, den lever och kan köra! Testade koppla in den i en powerbank för att styra genom MaQiaTTo:s WebSocketClient och är glad
att se att bilen svarar på MQTT-kommandon som den ska. Det finns förstås mycket att ändra på MQTT-sidan och jag har ännu inte riktigt börjat på hemsidan, men det här är en bra början!

-------------

## Fredag 27/3 (12.55-15.00)
Jag har jobbat med att försöka fixa ett eget sätt att skicka mqtt-värden. Jag har mest läst på om hur man gör och har bara börjat lite med tester.

-------------

## Måndag 30/3 (12.05-14.15)
Har gjort fortsättnigen på räkneuppgifterna enligt Kirchhoffs ström- och spänningslagar och om seriekopplade motstånd. Det gick bra, blev klar tidigt så jag fortsatte jobba på bilen. Då jag inte känner mig jättesäker på Vue och MQTT genom javascript hade jag börjaat kolla på en klient till Python (Paho MQTT), och nu har jag en fungerande klient som kan styra bilen med ett enkelt python-script.
 
 ###### [Kod finns här](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/tree/master/loggbok-exempel/python-mqtt-test "Test-kod")

-------------

## Tisdag 31/3 (9.50-10.55)
Har uppdaterat GitHuben, lagt till kod, fixat lite bilder och annat smått och gott. Måste tacka Adam Pritchard för sin [`Markdown Cheatsheet`](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet#lists "Fusklapp för markdown"). Jag har också planerat vad jag vill göra med bilen, och jag ska fortsätta och försöka överföra dessa kunskaper till hemsidan jag ska försöka göra. Jag känner mig inte riktigt klar med programmeringsprojektet så jag har planerat vad för sorts gobitar jag vill lägga till.

-------------

## Tisdag 31/3 (12.05-16.10)
Har jobbat med programmeringsprojektet. Känner mig relativt klar med mitt projekt, och har dessutom kommenterat all kod i projektet. Bilen har inte fått lika mycket uppmärksamhet idag, men jag har kikat lite på koden för att se vad för egenheter jag vill lägga till.

---

## Måndag 20/4 (8.10-9.30, 12.05-16.10)
Laddat upp Python-projektet på GitHuben (med kommentarer). Har arbetat med lite roliga metoder att styra på, utöver själva hemsidan, då jag vill ha lite olika alternativ för styrning.

---
## Tisdag 21/4 (14.35-16.10)
Har läst dokumentation för att bli bättre på frontend-sidan. Har också på sidan experimenterat med styrning via ett spel eller liknande för att få lite roliga alternativ för styrning.

---

## Tisdag 28/4 (12.05-16.10)
Vi hade ttf på morgonen så jag tog mig lite tid att leka lite med programmeringen och gjorde sedan på eftermiddagagen klart ett spel där man kan styra bilen med piltangenterna. Det var en sidoidé jag kom på någon gång på fritiden om det skulle visa sig att vue-projektet blev dåligt. Den finns [här](https://github.com/abbindustrigymnasium/driverbot-abbwiljoh/tree/master/python-control "pygame-car").
Annars har jag arbetat mycket med vue, som jag fortfarande inte känner mig helt säker på, men jag blir bättre för varje lektion jag jobbar med det!

---

## Måndag 11/5 (8.10-9.30)
Har jobbat med Pytho-projektet, försökt snygga till GitHuben och readme:n. Projektet är nu slutfört, det finns en video och repository för projektet som kan hittas [här](https://github.com/abbindustrigymnasium/programmering-1-miniprojekt-abbwiljoh "programmering-1-miniprojekt-abbwiljoh").

## Månadg 11/5 (12.05-16.10)
Jag har tyckt att den kod som finns i kodbanken är adekvat, och jag har hittills bara gjort små kosmetiska ändringar av just den anledningen. Däremot finns det saker jag känner kan läggas till, som att loggern så att den tar MQTT-värden från bilen, vilket är något jag har hållit på med idag. Arduinokoden har uppdaterats att skicka en uppdatering till hemsidan varje gång något ändras. Jag har också fixat ett problem som uppstod då servot var uppochned. Det var lätt att bara byta plats på "directions"-variabeln i Arduinokoden för mer hållbar styrning. 
Har läst och försökt få meddelanden först och främst att visas på loggern, men också hitta var jag ska sätta funktionen för att få uppdaterade meddelanden, men jag har en idé jag tänker testa nästa gång jag har tid.

---

## Tisdag 12/5 (12.05-16.10)
Har jobbat med beräkningar och ellära. Fortsättningen på Kirchhoffs och Ohms äventyr!

---

## Måndag 18/5 (14.35-16.10)
Ellära och beräkningar. Det gick bra, skönt med en lugn beräkningslektion efter kursprovet in matematik.
