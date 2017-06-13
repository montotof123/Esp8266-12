#include <time.h>

const byte interruptPin = 5;
volatile byte interruptCounter = 0;
int numberOfInterrupts = 0;
int horloge;
 
void setup() {
  Serial.begin(115200);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
  horloge = millis();
}
 
void handleInterrupt() {
  if(millis() > horloge + 200) {
    interruptCounter++;
    horloge = millis();
  }
}
 
void loop() {
  if(interruptCounter>0){
 
      interruptCounter--;
      numberOfInterrupts++;
 
      Serial.print("An interrupt has occurred. Total: ");
      Serial.println(numberOfInterrupts);

  }
}
