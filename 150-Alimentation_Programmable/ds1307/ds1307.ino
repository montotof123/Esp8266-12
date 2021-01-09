/*!
 *   \file    ds1307.cpp
 *   \brief   mise à l'heure et affichage de l'heure venant d'une horloge DS1307
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    09/01/2021
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <RTC.h>
#include "connect.h"

/**
 *   \brief   Horloge DS1307
 */ 
static DS1307 RTC;

/**
 *   \brief   SSID de la Box (à mettre dans le fichier connect.h)
 */ 
const char* ssid = SSID;
/**
 *   \brief   PASSWORD de la Box (à mettre dans le fichier connect.h)
 */ 
const char* password = PASSWORD;

// *****************************************
//       ***** ***** ***** *   * *****
//       *     *       *   *   * *   *
//       ***** ****    *   *   * *****
//           * *       *   *   * *
//       ***** *****   *   ***** *
// *****************************************
void setup() {
	// Initialisation
	Serial.begin(115200);
	WiFi.begin(ssid, password);
	RTC.begin();

	// Connexion à la box
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.println("Connecting...");
	}
	
	// Appel de l'API
	HTTPClient http; 
	http.begin("http://worldtimeapi.org/api/timezone/Europe/Paris");
	int httpCode = http.GET();
	
	// Traitement des données renvoyée par l'API                                                           
	if (httpCode > 0) {
		// Traitement JSON
		DynamicJsonDocument root(2048);
		deserializeJson(root, http.getString());
		JsonObject documentRoot = root.as<JsonObject>();
		long epoch = documentRoot[String("unixtime")];
		long offset = documentRoot[String("raw_offset")];
		
		// Affichage
		Serial.println(http.getString());
		for(JsonPair keyValue : documentRoot) {
			Serial.println(keyValue.key().c_str());
		}
		Serial.print("unixtime=");
		Serial.println(epoch);
		Serial.print("raw_offset=");
		Serial.println(offset);
		
		// Programmation du DS1307
		RTC.setHourMode(CLOCK_H24);
		RTC.setEpoch(epoch + offset);
		RTC.startClock();
	}
	http.end(); 
}

// ****************************************
//         *     ***** ***** *****
//         *     *   * *   * *   *
//         *     *   * *   * *****
//         *     *   * *   * *
//         ***** ***** ***** *
// ****************************************
void loop() {
	// Affichage de la date et de l'heure
	Serial.print(RTC.getDay());
	Serial.print("-");
	Serial.print(RTC.getMonth());
	Serial.print("-");
	Serial.print(RTC.getYear());
	Serial.print(" ");
	Serial.print(RTC.getHours());
	Serial.print(":");
	Serial.print(RTC.getMinutes());
	Serial.print(":");
	Serial.print(RTC.getSeconds());
	Serial.print("");
	if (RTC.getHourMode() == CLOCK_H12)
	{
		switch (RTC.getMeridiem()) {
			case HOUR_AM: Serial.print(" AM"); break;
			case HOUR_PM: Serial.print(" PM"); break;
		}
	}
	Serial.println("");
	
	delay(500);
}
