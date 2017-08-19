/***********************
  Test HC-SR04
  Created on: 14/08/2017
  Author: totof
***********************/

#define TRIGGER 5
#define ECHO    4
#define ONE_WIRE_BUS 2

#include <OneWire.h>
#include <DallasTemperature.h>
#include "GestionHCSR04.h"

GestionHCSR04 mesureDistance(TRIGGER, ECHO);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

void setup() {	
	Serial.begin (115200);
	Serial.println("Init");
	DS18B20.begin();
	DS18B20.requestTemperatures(); 
	mesureDistance.setTemperature(DS18B20.getTempCByIndex(0));
	char temperatureString[6];
	dtostrf(mesureDistance.getTemperature(), 2, 2, temperatureString);
	Serial.print("Temperature: ");
	Serial.print(temperatureString);
	Serial.println(" °");
}

void loop() {
	float distanceCM = mesureDistance.getDistance() * 100.0;
	char distanceString[6];
	dtostrf(distanceCM, 2, 2, distanceString);
	Serial.print("Distance: ");
	Serial.print(distanceString);
	Serial.println(" cm");
	delay(1000);
}

