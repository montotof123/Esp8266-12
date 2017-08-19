//============================
// Name        : telemetre Web
// Author      : totof
// Version     :
// Copyright   : Free
// Description : telemetre Web
//============================

#define TRIGGER 5
#define ECHO    4
#define ONE_WIRE_BUS 2
#define ADRESSE 0
#define PIN_CS 15

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include "GestionHCSR04.h"
#include "GestionAffichage.h"

GestionHCSR04 mesureDistance(TRIGGER, ECHO);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
GestionAffichage affichage(ADRESSE, PIN_CS);

const char* ssid = "dlink-4212"; // remplacer par le SSID de votre WiFi
const char* password = "nhyyi53680"; // remplacer par le mot de passe de votre WiFi
ESP8266WebServer server(80); // on instancie un serveur ecoutant sur le port 80

void setup() {	
	// Initialisation serial
	Serial.begin (115200);
	Serial.println("Télémesure");
	
	 // on demande la connexion au WiFi
	WiFi.begin(ssid, password);
	Serial.println("");

	// on attend d'etre connecte au WiFi avant de continuer
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	// on affiche l'adresse IP qui nous a ete attribuee
	Serial.println("");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	
	// Mesure et affichage temperature pour correction
	DS18B20.begin();
	DS18B20.requestTemperatures(); 
	mesureDistance.setTemperature(DS18B20.getTempCByIndex(0));
	affichage.affiche(DS18B20.getTempCByIndex(0), 2);
	delay(5000);
	affichage.eteindre();
	delay(2000);
	
	// Lire le thermometre
	server.on("/thermometre", []() {
		float temperature = DS18B20.getTempCByIndex(0);
		char temperatureString[6];
		dtostrf(temperature, 2, 2, temperatureString);
		server.send(200, "text/plain", temperatureString);
	});
	
	// Lire le telemetre
	server.on("/telemetre", []() {
		float mesureCM = mesureDistance.getDistance() * 100.0;
		char mesureCMString[6];
		dtostrf(mesureCM, 2, 2, mesureCMString);
		server.send(200, "text/plain", mesureCMString);
	});
	
	// on commence a ecouter les requetes venant de l'exterieur
	server.begin();
}

void loop() {
	// Mesure distance en cm et affichage 
	float distanceCM = mesureDistance.getDistance() * 100.0;
	affichage.affiche(distanceCM, 1);
	
	// distance a l'ecran
	char distanceString[6];
	dtostrf(distanceCM, 2, 2, distanceString);
	Serial.println(distanceString);

	// a chaque iteration, on appelle handleClient pour que les requetes soient traitees
	server.handleClient();
  
	delay(1000);
}

	
