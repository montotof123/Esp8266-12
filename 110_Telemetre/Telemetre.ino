//========================
// Name        : telemetre
// Author      : totof
// Version     :
// Copyright   : Free
// Description : telemetre
//========================

#define TRIGGER 5
#define ECHO    4
#define ONE_WIRE_BUS 2
#define ADRESSE 0
#define PIN_CS 15

#include <OneWire.h>
#include <DallasTemperature.h>
#include "GestionHCSR04.h"
#include "GestionAffichage.h"

GestionHCSR04 mesureDistance(TRIGGER, ECHO);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
GestionAffichage affichage(ADRESSE, PIN_CS);

void setup() {	
	Serial.begin (115200);
	Serial.println("Télémesure");
	DS18B20.begin();
	DS18B20.requestTemperatures(); 
	mesureDistance.setTemperature(DS18B20.getTempCByIndex(0));
	affichage.affiche(DS18B20.getTempCByIndex(0), 2);
	delay(5000);
	affichage.eteindre();
	delay(2000);
}

void loop() {
	// Mesure distance en cm et affichage 
	float distanceCM = mesureDistance.getDistance() * 100.0;
	affichage.affiche(distanceCM, 1);
	
	// distance a l'ecran
	char distanceString[6];
	dtostrf(distanceCM, 2, 2, distanceString);
	Serial.println(distanceString);

	delay(1000);
}

	
