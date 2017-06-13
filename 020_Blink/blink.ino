
/*
 ESP8266 Blink
 Blink the blue LED on the ESP-12 module
 
 The blue LED on the ESP-12 module is connected to GPIO2 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time) 
*/
 
#define LED 2   //Define connection of LED
 
void setup() {
  pinMode(LED, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}
 
// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
 // but actually the LED is on; this is because 
 // it is active low on the ESP-12)
  delay(1000);              // Wait for a second
  digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000); // Wait for two seconds (to demonstrate the active low LED)
}

