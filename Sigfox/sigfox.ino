#include <SoftwareSerial.h>

// Define RX, TX Pins
SoftwareSerial sfModule(10, 11);

String getData(){
  // Receive Data from Module
  String data = "";
  char output;

  while (!sfModule.available()){
    // blink
    digitalWrite(LED_BUILTIN, 1);   // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(LED_BUILTIN, 0);    // turn the LED off by making the voltage LOW
    delay(50);
  }

  // The Module has a buffer from which we can read if data is available
  while(sfModule.available()){
    Serial.println("receiving data!");
    output = sfModule.read();
    if ((output != 0x0A) && (output != 0x0D)){//0x0A Line feed | 0x0D Carriage return
      data += output;
      }

    delay(10);
  }

  Serial.print("Data: ");
  Serial.println(data);

  return data;
}

String getID(){
  sfModule.print("AT$I=10\r");
  String res = getData();

  Serial.print("ID: ");
  Serial.println(res);

  return res;
}

String checkCommunication() {
  sfModule.print("AT\r");
  String res = getData();
  
  Serial.println(res);
  
  return res;
}

String getPAC(){
  sfModule.print("AT$I=11\r");
  String res = getData();

    Serial.print("PAC: ");
    Serial.println(res);

  return res;
}

boolean sendMessage(uint8_t payload[12]) {
  sfModule.print("AT$SF=");
  for(int i = 0; i < sizeof payload; i++) {
    sfModule.print(payload[i]);
  }
  sfModule.print("\r");

  return checkMessageSuccess();
}

boolean sendStringMessage(String payload) {
  Serial.println("Sending message");
  sfModule.print("AT$SF=");
  sfModule.print(payload);
  sfModule.print("\r");
  return checkMessageSuccess();
}

void sendSampleMessage() {
  Serial.println("Sending sample message");
  sfModule.print("AT$SF=0123CAFE\n");
  delay(2000);
  String res = getData();
}

boolean checkMessageSuccess() {
  String res = getData();
  if(res.indexOf("OK") >= 0) {
    return true;
  }
  return false;
}

void lightSleep(){
  Serial.println("light sleep start");
  sfModule.print("AT$P=1\n");
  String res = getData();
}

void deepSleep(){
   Serial.println("deep sleep start");
  sfModule.print("AT$P=2\n");
  String res = getData();
}

void wakeLightSleep(){
  Serial.println("light sleep end");
  sfModule.print("\r");
}

void wakeDeepSleep() {
  // Module needs a Low-Flanke on specified GPIO, to wake from deepsleep
  Serial.println("deep sleep end");
  digitalWrite(9, LOW);
  delay(200);
  digitalWrite(9, HIGH);
  delay(200);
}
  
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(9, OUTPUT);
    sfModule.begin(9600);
    Serial.begin(9600);
    delay(3000);
    // checkCommunication();
    Serial.println("Init finished");
}
  
void loop() {
  delay(5000); // 5s
  sendSampleMessage();
  delay(5000);
  lightSleep();
  delay(5000);
  wakeLightSleep();
  delay(5000);
  deepSleep();
  delay(5000);
  wakeDeepSleep();
}
