# MiniGPS-Info-Multi-OLED
ESP8266, NEO-6M GPS, OLED 0.96" (SSD1306) oder 1.3" (SH1106)


<a href="https://youtu.be/z9Ir-hZvLQg">ESP8266 mit einen NEO-6M GPS und OLED 0.96" oder 1.3" DIsplay</a>


Folgende Libs werden benötigt (brzo i2c), (TinyGPS++), (SoftwareSerial)
Für 0.96 oder 1.3 Zoll OLED Display geeignet, entsprechnde 2 Zeilen löschen, auskommentieren
seltsmerweise laufen die 1.3 OLED auch auf der 0x3c Adresse obwohl hinten 0x78 steht ???
manchmal läßt sich der ESP nicht beschreiben, wenn das GPS Modul dran ist >> einfach VCC von GPS abziehen
Funktionsprüfung: GPS Modul mit strom versorgen (bei mir 3.3V), wenn es blink, bekommt es Daten. Falls nichts erscheint (nicht ein Mal Uhrzeit) >> RX, TX tauschen

![001](https://user-images.githubusercontent.com/35377000/34887293-43c720e6-f7c6-11e7-91c8-a552c8d1847b.jpg)

![002](https://user-images.githubusercontent.com/35377000/34887318-5f641c96-f7c6-11e7-8bf4-2821acfe8d32.jpg)

*ToDo Liste:

