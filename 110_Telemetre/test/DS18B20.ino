// Including DS18B20 librairies
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin D1 on the ESP8266 12-E - GPIO 12
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature DS18B20(&oneWire);

// only runs once on boot
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);
  delay(10);
  DS18B20.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
}

// runs over and over again
void loop() {
	DS18B20.requestTemperatures(); 
	float tempC  = DS18B20.getTempCByIndex(0);
	char temperatureCString[6];
	dtostrf(tempC, 2, 2, temperatureCString);
    Serial.print("Temperature celcius = ");
    Serial.print(temperatureCString);
    Serial.println("°");
    delay(1000);
}  
