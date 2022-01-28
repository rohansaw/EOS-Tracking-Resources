#include <SoftwareSerial.h>

SoftwareSerial sim800l(3,2);

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);
}

void loop() {
  while (Serial.available()) {
      delay(1);
      sim800l.write(Serial.read());
  }
  while (sim800l.available()) {
       Serial.write(sim800l.read());
  }
}
