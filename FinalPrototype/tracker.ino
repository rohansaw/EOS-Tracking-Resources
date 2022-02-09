#include <SoftwareSerial.h>

SoftwareSerial sfModule(10, 11);
const int buttonPin = 2; // Make sure that this is the interrupt 0 pin on the board!!
const int vibrationPin = 2; // Make sure that this is the interrupt 0 pin on the board!!
boolean trackingMode = true;

void sleep() {
  //Disable brownout detection
  MCUCR |= (3 << 5); //set both BODS and BODSE at the same time
  MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); //then set the BODS bit and clear the BODSE bit at the same time

  //actually go to sleep with inline assembler
  __asm__  __volatile__("sleep");
}

// isr to wakeup on watchdog timer done
ISR(WDT_vect){
}

void enableWatchdogTimer(){
  //watchdom timer setup as interrupt
  WDTCSR = (24);//change enable and WDE - also resets
  WDTCSR = (33);//prescalers only - get rid of the WDE and WDCE bit
  WDTCSR |= (1<<6);//enable interrupt mode
}

void disableWatchdogTimer(){
  // ToDo
}

void buttonInterrupt() {
  Serial.println("btn pressed");
  trackingMode = !trackingMode;
}

void vibrationInterrupt() {
  Serial.println("vibration detected");
}

void setup() {
   Serial.begin(9600);
    sfModule.begin(9600);
    delay(1000);
    Serial.println("started module");
  /*for (int i = 0; i < 20; i++) {
    if(i != 2 || i!= 3 || i != 10 || i != 11)
    pinMode(i, OUTPUT);
  } */
  
   pinMode(buttonPin, INPUT_PULLUP);
   pinMode(vibrationPin, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);
   attachInterrupt(digitalPinToInterrupt(vibrationPin), vibrationInterrupt, FALLING);

  //enableWatchdogTimer();

  //disable ADC to save lots of power
  ADCSRA &= ~(1 << 7);

  //enable sleep mode
  SMCR |= (1 << 2); //power down mode
  SMCR |= 1;//enable sleep

  // Slow down Clock
  //CLKPR = 0x80;
  //CLKPR = 0x01;
  delay(3000);
}

String getData(){
  String data = "";
  char output;

  while (!sfModule.available()){
    Serial.println("sigfox module not available");
  }

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

String getPosition() {
  return "0123CAFE";
}

void sendPosition(String pos) {
  sfModule.print("AT$SF=");
  sfModule.print(pos);
  sfModule.print("\n");
  delay(2000);
  String res = getData();
}
int c = 0;
void loop() {
  Serial.println("Awake");
  if(c == 0){
    //String pos = getPosition();
    //sendPosition(pos);
    c++;
  }
  
  for(int i = 0; i < 10; i++) {
    //sleep();
  }
}
