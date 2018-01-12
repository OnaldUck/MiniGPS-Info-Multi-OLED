# MiniGPS-Info-Multi-OLED
ESP8266, NEO-6M GPS, OLED 0.96" (SSD1306)  oder 1.3" (SH1106)

Folgende Libs werden benötigt (brzo i2c), (TinyGPS++), (SoftwareSerial)
Für 0.96 oder 1.3 Zoll OLED Display geeignet, entsprechnde 2 Zeilen löschen, auskommentieren
seltsmerweise laufen die 1.3 OLED auch auf der 0x3c Adresse obwohl hinten 0x78 steht ???
manchmal läßt sich der ESP nicht beschreiben, wenn das GPS Modul dran ist >> einfach VCC von GPS abziehen
Funktionsprüfung: GPS Modul mit strom versorgen (bei mir 3.3V), wenn es blink, bekommt es Daten. Falls nichts erscheint (nicht ein Mal Uhrzeit) >> RX, TX tauschen
https://youtu.be/z9Ir-hZvLQg
