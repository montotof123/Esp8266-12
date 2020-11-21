#include "GestionADXL362.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <EEPROM.h> 

// Broche d'activation du SPI
int pinCS = 2;
int pinError = 4;


// Box
const char* ssid = "Livebox-zzzz";
const char* password =  "abcdefghijklmnopq42";

GestionADXL362 adxl362(pinCS);

// WiFi
WiFiClient espClient;

// Adresse de l'identifiant dans l'EEPROM
int addr_id = 0;
// Max 200 caractères
int sizeEEPROM = 200;
// Caractère § indiquant un caractère inutilisé
int emptyChar = 167;

// *****************************************
//       ***** ***** ***** *   * *****
//       *     *       *   *   * *   *
//       ***** ****    *   *   * *****
//           * *       *   *   * *
//       ***** *****   *   ***** *
// *****************************************
void setup() {
	// Init du sérial
	Serial.begin (115200);

	// ID de l'IOT
	EEPROM.begin(sizeEEPROM);
	String id;
	for (int k = addr_id; k < addr_id + sizeEEPROM; ++k) {
		if(EEPROM.read(k) == emptyChar){
			break;
		} else {
			id += char(EEPROM.read(k));
		}
	}
	Serial.println("");
	Serial.print("ID: ");
	Serial.println(id);
	EEPROM.end();
  
	// Reset de l'accelerometre
	adxl362.softReset();
	// Information de l'accéléromètre
	// Sur un IOT actif, les print peuvent être retirés
	Serial.println((int)adxl362.getDevId(), HEX);
	Serial.println((int)adxl362.getMicroElectroMechanicalSystemId(), HEX);
	Serial.println((int)adxl362.getPartId());
	Serial.println((int)adxl362.getRevId(), HEX);
	Serial.println(adxl362.isADXL362Device());

	// Programmation de l'accéléromètre pour générer une interruption
	adxl362.sampleInit2();

	// Connexion au Wifi
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	}

	// Mise en forme
	DynamicJsonDocument root(2048);
	root["id"] = id;
	String json;
	serializeJson(root, json);

	// Envoi
	// Attention: il y aura un premier envoi à l'allumage du module
	HTTPClient http;    
	http.begin("http://192.168.1.100:8082/api/eventiot");      
	http.addHeader("Content-Type", "application/json");
	http.addHeader("auth-key", "My_authentication_key42");  
	http.POST(json);
	http.end();  

	// Information de l'accéléromètre
	// Sur un IOT actif, les print peuvent être retirés
	Serial.println(adxl362.getXAxisG());
	Serial.println(adxl362.getYAxisG());
	Serial.println(adxl362.getZAxisG());

	// Permet de détecter une erreur d'initialisation
	// En cas d'erreur, la broche passe 5s à l'état haut
	//   permettant d'allumer une LED pendant ce laps de temps
	pinMode(pinError, OUTPUT);
	digitalWrite(pinError, LOW);
	if(adxl362.getTemperatureCelcius() == 0.00F){
		Serial.println("erreur");
		digitalWrite(pinError, HIGH);
		delay(5000);
	}

	// Reprogramme l'accéléromètre
	// Semble éviter un blocage de l'accéléromètre au bout de quelques mesures
	adxl362.sampleInit2();
	adxl362.spiStop();

	// Temposisation afin de permettre aux signaux de se stabiliser
	delay(500); // 0.5s

	// Dodo pour préserver la batterie
	// l'ESP consomme moins d'1mA dans se mode au lieu des 140mA en fonctionnement normal
	// La consommation peut être réduite en enlevant l'envoi des données en sérial qui fait clignoter la LED
	//   et en minimisant le temps où l'ESP est réveillé (delay, mesure de l'accéléromètre inutile etc...)
	ESP.deepSleep(0);
}

// ****************************************
//         *     ***** ***** *****
//         *     *   * *   * *   *
//         *     *   * *   * *****
//         *     *   * *   * *
//         ***** ***** ***** *
// ****************************************
// Ne rien mettre dedans car le programme n'y vient jamais il s'arrête au deepSleep du setup et repart au début
void loop() {
}
