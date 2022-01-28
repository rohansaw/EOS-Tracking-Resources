#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;

// Die serielle Verbindung zum GPS Modul
SoftwareSerial ss(16, 17);

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println("Starting GPS");
}

void loop() {
  while (ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      // Breitengrad mit 3 Nachkommastellen
      Serial.print("Breitengrad= ");
      Serial.print(gps.location.lat(), 3);
      // Längengrad mit 3 Nachkommastellen
      Serial.print(" Längengrad= ");
      Serial.println(gps.location.lng(), 3);
    }
  }
}
