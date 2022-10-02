// Folgende Libs werden benötigt (brzo i2c), (TinyGPS++), (SoftwareSerial)
// Für 0.96 oder 1.3 Zoll OLED Display geeignet, entsprechnde 2 Zeilen löschen, auskommentieren
// seltsmerweise laufen die 1.3 OLED auch auf der 0x3c Adresse obwohl hinten 0x78 steht ???
// manchmal läßt sich der ESP nicht beschreiben, wenn das GPS Modul dran ist >> einfach VCC von GPS abziehen
// Funktionsprüfung: GPS Modul mit strom versorgen (bei mir 3.3V), wenn es blink, bekommt es Daten. Falls nichts erscheint (nicht ein Mal Uhrzeit) >> RX, TX tauschen

#include <TinyGPS++.h>                  // Tiny GPS Plus Library
#include <SoftwareSerial.h>            // Software Serial Library so we can use other Pins for communication with the GPS module
//#include "SH1106Brzo.h"               // (3,1) wenn das Display direct am NodMCU steckt  - SH1106 = 0.96" OLED
//SH1106Brzo  display(0x3c, 3, 1);      // (3,1) wenn das Display direct am NodMCU steckt (Daniel Eichhoff)

#include "SSD1306Brzo.h"                // (3,1) wenn das Display direct am NodMCU steckt   - SH1306 = 1.3" OLED
SSD1306Brzo  display(0x3c, 5, 4);      // (5,4) WeMos inc 0.96 Display, 18650 Batterie und Knopf (ADDRESS, SDA, SCL)

TinyGPSPlus gps;                      // Create an Instance of the TinyGPS++ object called gps
SoftwareSerial ss(D3, D4);             // (3, 15) (2,0) RX, TX Pins for serial connection to the GPS device - über Kreuz !

#define DEMO_DURATION 5000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;

void setup() {
  // initialize dispaly
  display.init();
  display.clear();
  display.display();
  display.setFont(ArialMT_Plain_10);
  //display.setTextAlignment(TEXT_ALIGN_LEFT);
  //display.flipScreenVertically();
  //display.setContrast(1);
  ss.begin(9600);
}

 // This custom version of delay() ensures that the gps object is being "fed".
static void smartDelay(unsigned long ms){unsigned long start = millis(); do  {while (ss.available()) gps.encode(ss.read());} while (millis() - start < ms);}

// function for digital clock display: prints leading 0
String twoDigits(int digits){if(digits < 10) {String i = '0'+String(digits); return i;} else {return String(digits);}}

unsigned long Distance_To_Home = (unsigned long)TinyGPSPlus::distanceBetween(gps.location.lat(),gps.location.lng(),49.96675, 7.8992) / 1000;    // hier kommten die Home Koordinaten

String course( double bearing ) {
  if (bearing >=    0.0  && bearing < 11.25  ) return "N";
  if (bearing >=  11.25  && bearing < 33.75 )  return "NNO";
  if (bearing >=  33.75  && bearing < 56.25 )  return "NO";
  if (bearing >=  56.25  && bearing < 78.75 )  return "ONO";
  if (bearing >=  78.75  && bearing < 101.25 ) return "O";
  if (bearing >=  101.25 && bearing < 123.75 ) return "OSO";
  if (bearing >=  123.75 && bearing < 146.25 ) return "SO";
  if (bearing >=  146.25 && bearing < 168.75 ) return "SSO";
  if (bearing >=  168.75 && bearing < 191.25 ) return "S";
  if (bearing >=  191.25 && bearing < 213.75 ) return "SSW";  
  if (bearing >=  213.75 && bearing < 236.25 ) return "SW";
  if (bearing >=  236.25 && bearing < 258.25 ) return "WSW";
  if (bearing >=  258.25 && bearing < 281.25 ) return "W";
  if (bearing >=  281.25 && bearing < 303.75 ) return "WNW";
  if (bearing >=  303.75 && bearing < 326.25 ) return "NW";
  if (bearing >=  326.25 && bearing < 348.75 ) return "NNW";
  if (bearing >=  348.75 && bearing < 360.00 ) return "N";
  else return "N";   }

void drawIntroDemo() {
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "===|Mini GPS Info|===");
    display.drawString(0, 16, "Mit der freundlichen");
    display.drawString(0, 24, "Unterstützung von");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 32, "PeterK");
    }
  
void drawGPSTimeDemo() {
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Time");
    display.drawString(0, 32, "Date");
    display.drawString(82, 0, "(Sats: " + String(gps.satellites.value()) + ")");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 8, twoDigits(gps.time.hour()+1) +  ":" + twoDigits(gps.time.minute()) +  ":" + twoDigits(gps.time.second()));
    display.drawString(0, 40, twoDigits(gps.date.day()) +  "." + twoDigits(gps.date.month()) +  "." + String(gps.date.year()));
  }

void drawGPSDemo() {
   display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Latitude:");
    display.drawString(0, 32, "Longitude:");
   display.setFont(ArialMT_Plain_24);
    display.drawString(0, 8, String(gps.location.lat(),6) + " °");
    display.drawString(0, 40, String(gps.location.lng(),6) + " °");
}

void drawGPS2Demo() {
   display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0,"Altitude:");
    display.drawString(0, 32,"Speed:");
   display.setFont(ArialMT_Plain_24);
    display.drawString(0, 8, String(gps.altitude.meters()) + " m");
    display.drawString(0, 40, String(gps.speed.kmph()) +  " km/h");
    }

void drawGPS3Demo() {
   display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Distance To Home:");
    display.drawString(0, 32, "Course:");
   display.setFont(ArialMT_Plain_24);
    display.drawString(0, 8, String(Distance_To_Home) + " km");
    display.drawString(0, 40, String(gps.course.deg()) + "° " +  course( gps.course.deg()));
    }

  
Demo demos[] = {drawGPSTimeDemo, drawGPSDemo, drawGPS2Demo, drawGPS3Demo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;

void loop() {
  smartDelay(500);                       // Run Procedure smartDelay
  display.clear();
  demos[demoMode]();
  display.display();

//diesen Abschnitt braucht man für den Seitenwechsel
    if (millis() - timeSinceLastModeSwitch > DEMO_DURATION) {
    demoMode = (demoMode + 1)  % demoLength;
    timeSinceLastModeSwitch = millis();
  }
  counter++;
  delay(10);
}
