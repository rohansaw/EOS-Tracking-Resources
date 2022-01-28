#include <SoftwareSerial.h>

SoftwareSerial ss(16,17);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte gpsdata = ss.read();
  Serial.write(gpsdata);
}
