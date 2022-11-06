/*!
 *   \file    alimProg.cpp
 *   \brief   Alimentation programmable
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    10/01/2021
 */
 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <RTC.h>

#include <MCP45HVX1.h>
#include <Adafruit_INA219.h>

#include <Adafruit_MCP23017.h>
#include "Chiffres7seg.h"

#include <SPI.h>
#include <SRAM_23LC.h>
#define SPI_PERIPHERAL		SPI
#define CHIP_SELECT_PIN		15

#include "connect.h"

/**
 *   \brief   SSID de la Box (à mettre dans le fichier connect.h)
 */ 
const char* ssid = SSID; 

/**
 *   \brief   PASSWORD de la Box (à mettre dans le fichier connect.h)
 */ 
const char* password = PASSWORD; 

/**
 *   \brief   Horloge DS1307
 */ 
static DS1307 RTC;

/**
 *   \brief   Potentiomètre MCP45HV51
 */ 
MCP45HVX1 digiPot(0x3C);

/**
 *   \brief   Mesureur INA219
 */ 
Adafruit_INA219 ina219;

/**
 *   \brief   expander MCP23017
 */ 
Adafruit_MCP23017 mcp;

/**
 *   \brief   Serveur web sur le port 80
 */ 
ESP8266WebServer server(80); 
void handleNotFound();

/**
 *   \brief   Commande du relai
 */ 
constexpr auto RELAIS_SORTIE = 16;

/**
 *   \brief   Position afficheur 3641BS
 */ 
constexpr auto AFFICHEUR_MILLIERS  = 0x0100;
constexpr auto AFFICHEUR_CENTAINES = 0x0200;
constexpr auto AFFICHEUR_DIZAINES  = 0x0400;
constexpr auto AFFICHEUR_UNITES    = 0x0800;

/**
 *    \brief   Données à afficher
 *    \note    Tension par défaut
 *    
 *    0: current
 *    1: power
 *    2: tension
 */
constexpr auto CURRENT = 0;
constexpr auto POWER   = 1;
constexpr auto TENSION = 2;
constexpr auto OFF = 3;
uint8_t affiche = TENSION; 

/**
 *     \brief   Maximum de mémoire du 23LC1024
 *	   \note (128ko int de 131072 / 5 octets (heure, minute, seconde, courant sur 2 octets)
 */
constexpr auto MAX_UTIL_MEMORY = 131070; 

/**
 *	   \brief  Valeur de d'utilisation par défaut de la mémoire 23LC1024
 *     \note   au delà le getcurve ne fonctionne plus d'un coup et l'ESP reboot
 *
 */
constexpr auto MAX_MEMORY = 20000;
uint32_t maxMemoryUsage = MAX_MEMORY; // Valeur d'utilisation de la mémoire par défaut

/**
 *	   \brief  Pointeur de la mémoire 23LC1024
 *     \note   au delà le getcurve ne fonctionne plus d'un coup et l'ESP reboot
 *
 */
uint32_t pointeur = 0; 

/**
 *	   \brief  Etat d'utilisation de la mémoire 23LC1024
 *     \note   Actif par défaut
 *
 */
constexpr auto MEMORY_ON = 1;
constexpr auto MEMORY_OFF = 0;
uint8_t memoryUsage = MEMORY_ON; 
constexpr auto MEMORY_CIRCLE = 1;
constexpr auto MEMORY_NO_CIRCLE = 0;
uint8_t memoryCircle = MEMORY_CIRCLE; 

/**
 *   \brief   Nombre de mesure par seconde
 *   \note    25 par défaut
 */
uint8_t nombreMesure = 25;
uint8_t rate = 2;    // Balayage sur les afficheurs (par defaut 2 par boucle loop)
uint8_t delayMs = 4;  // Delay d'affichage par afficheur (par defaut 4ms)

/**
 *   \brief   Mémoire série 23LC1024
 */
SRAM_23LC SRAM(&SPI_PERIPHERAL, CHIP_SELECT_PIN, SRAM_23LC1024);

/**
 *   \brief   Permet d'écrire une valeur 16 bits en 2 fois 8bits dans la mémoire
 */
union SRAMUData{
	uint16_t uSData;
	uint8_t uCData[2];
};

/**
 *   \brief   Horloge pour activation à un moment précis
 */
uint8_t jour = 0;
uint8_t mois = 0;
uint16_t annee = 0;
uint8_t heure = 0;
uint8_t minute = 0;
uint8_t seconde = 0;

/**
 *   \brief   Etat du relai
 *   \note    Inactif par défaut
 *
 *    0: Inactif
 *    1: Actif
 */
constexpr auto INACTIF = 0;
constexpr auto ACTIF   = 1;
uint8_t stateRelai = 0;


// *****************************************
//       ***** ***** ***** *   * *****
//       *     *       *   *   * *   *
//       ***** ****    *   *   * *****
//           * *       *   *   * *
//       ***** *****   *   ***** *
// *****************************************
void setup(void){
	// ************************************************************
	//                        Matériel
	// ************************************************************
	// Initialisation de l'horloge
	RTC.begin();
	
	// Initialisation MCP45HV51 pour démarrer avec la tension minimale
	digiPot.begin();  
	digiPot.connectTerminalB();
	digiPot.connectTerminalA();
	digiPot.connectWiper();
	digiPot.writeWiper(0); 
	
	// Initialisation INA219
	ina219.begin();
	
	// Initialisation Relai
	pinMode(RELAIS_SORTIE, OUTPUT);
	digitalWrite(RELAIS_SORTIE, HIGH);
	
	// Initialisation MCP23017
	mcp.begin();
	
	// Initialisation afficheurs
	mcp.pinMode(0, OUTPUT);
	mcp.pinMode(1, OUTPUT);
	mcp.pinMode(2, OUTPUT);
	mcp.pinMode(3, OUTPUT);
	mcp.pinMode(4, OUTPUT);
	mcp.pinMode(5, OUTPUT);
	mcp.pinMode(6, OUTPUT);
	mcp.pinMode(7, OUTPUT);

	mcp.pinMode(8, OUTPUT);
	mcp.pinMode(9, OUTPUT);
	mcp.pinMode(10, OUTPUT);
	mcp.pinMode(11, OUTPUT);

	mcp.writeGPIOAB(moins + AFFICHEUR_MILLIERS);
	
	// Initialisation mémoire et mise à 0
	SRAM.begin();
	uint8_t avance = 0;
	for(uint32_t compteur = 0; compteur <= MAX_UTIL_MEMORY; compteur++)
	{
		SRAM.writeByte(compteur, 0);
		if(compteur % 15000 == 0) {
			// Fait défiler un caractère moins sur les afficheurs à chaque bloc de mémoire effacé
			afficheAvance(avance);
			avance++;
			yield(); // Evite un reboot de l'ESP par le WatchDog si la commande dure trop longtemps
		}
	}

	// ************************************************************
	//                      Connexion Wifi
	// ************************************************************
	afficheAvance(avance);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		// Fait défiler un caractère moins sur les afficheurs à chaque test de connexion
		afficheAvance(avance);
		avance++;
		delay(200);
	}

	// *******************************************
	// Affichage du dernier nombre de l'adresse IP
	// *******************************************
	afficheIP(WiFi.localIP()[3]);
  
	// *************************************************
	// Initialisation de l'horloge par l'API worltimeapi
	// *************************************************
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
    long raw_offset = documentRoot[String("raw_offset")];
    long dst_offset = documentRoot[String("dst_offset")];
		
		// Programmation du DS1307
		RTC.setHourMode(CLOCK_H24);
		RTC.setEpoch(epoch + raw_offset + dst_offset);
		RTC.startClock();
	}
	http.end(); 

	// ************************************************************
	//                       URL WEB écoutées
	// ************************************************************
	// Explications
	server.on("/", []() {
		String info = "";
		info += "<table border='1'>";
		info += "<tr><td>/</td><td>Ce mode d'emploi</td></tr>";
	
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getTension' target='_blank'>/getTension</a></td><td>Donne la tension instantan&eacute;e (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getPower' target='_blank'>/getPower</a></td><td>Donne la puissance instantan&eacute;e (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getCurrent' target='_blank'>/getCurrent</a></td><td>Donne le courant instantan&eacute; (json)</td></tr>";
		
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setAffiche?data=current' target='_blank'>/setAffiche?data=current</a></td><td>Affiche le courant sur les afficheurs (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setAffiche?data=power' target='_blank'>/setAffiche?data=power</a></td><td>Affiche la puissance sur les afficheurs (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setAffiche?data=tension' target='_blank'>/setAffiche?data=tension</a></td><td>Affiche la tension sur les afficheurs (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setAffiche?data=off' target='_blank'>/setAffiche?data=off</a></td><td>Eteins les afficheurs (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getAffiche' target='_blank'>/getAffiche</a></td><td>Etat des afficheurs (json)</td></tr>";
		
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getHorloge' target='_blank'>/getHorloge</a></td><td>Donne la date et l'heure de l'horloge (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setReveil?date=dd/mm/yyyy&heure=hh:mm:ss' target='_blank'>/setReveil?date=dd/mm/yyyy&heure=hh:mm:ss</a></td><td>Positionne la date et l'heure d'allumage (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getReveil' target='_blank'>/getReveil</a></td><td>Donne la date et l'heure d'allumage (json)</td></tr>";
		
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setTension?valeur=nn.nn' target='_blank'>/setTension?valeur=nn.nn</a></td><td>Positionne la tension (nn.nn entre 2.00V et 11.00V) (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setRelai?state=on' target='_blank'>/setRelai?state=on</a></td><td>Active le relai (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setRelai?state=off' target='_blank'>/setRelai?state=off</a></td><td>D&eacute;sactive le relai (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getRelai' target='_blank'>/getRelai</a></td><td>Donne l'&eacute;tat du relai (json)</td></tr>";
		
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setMemory?state=on' target='_blank'>/setMemory?state=on</a></td><td>Active l'utilisation de la m&eacute;moire s&eacute;rie (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setMemory?state=off' target='_blank'>/setMemory?state=off</a></td><td>D&eacute;sactive l'utilisation de la m&eacute;moire s&eacute;rie (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getMemory' target='_blank'>/getMemory</a></td><td>Donne l'&eacute;tat de la m&eacute;moire s&eacute;rie (json)</td></tr>";

		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setMemoryCircle?state=on' target='_blank'>/setMemoryCircle?state=on</a></td><td>Lorsque la m&eacute;moire est &eacute;crite compl&egrave;tement, le pointeur repart &agrave; 0 (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setMemoryCircle?state=off' target='_blank'>/setMemoryCircle?state=off</a></td><td>Lorsque la m&eacute;moire est &eacute;crite compl&egrave;tement, l'&eacute;criture s'arr&ecirc;te (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getMemoryCircle' target='_blank'>/getMemoryCircle</a></td><td>Indique si la m&eacute;moire est &eacute;crite cycliquement ou non (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getMemoryPointer' target='_blank'>/getMemoryPointer</a></td><td>Donne la position du pointeur m&eacute;moire (json)</td></tr>";
		
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setMemoryUsage?valeur=nnnnnn' target='_blank'>/setMemoryUsage?valeur=nnnnnn</a></td><td>Positionne l'utilisation maximum de la m&eacute;moire s&eacute;rie entre 0 et 131070 (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getMemoryUsage' target='_blank'>/getMemoryUsage</a></td><td>Donne l'utilisation de la m&eacute;moire s&eacute;rie (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/resetMemory' target='_blank'>/resetMemory</a></td><td>Reset de la m&eacute;moire s&eacute;rie (json)</td></tr>";
		
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/setMesure?nombre=nn' target='_blank'>/setMesure?nombre=nn</a></td><td>Nombre de mesures m&eacute;moris&eacute;es par seconde dans la m&eacute;moire s&eacute;rie. Valeurs possibles: 160, 90, 72, 54, 40, 25 (d&eacute;faut), 13, 7, 4, 2, 1 (json)</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getMesure' target='_blank'>/getMesure</a></td><td>Donne le nombre de mesures m&eacute;moris&eacute;es par seconde dans la m&eacute;moire s&eacute;rie. Valeurs possibles: 160, 90, 72, 54, 40, 25 (d&eacute;faut), 13, 7, 4, 2, 1 (json)</td></tr>";

		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getFullCurve' target='_blank'>/getFullCurve</a></td><td>Donne le courant en fonction du temps sur toute la m&eacute;moire utilis&eacute;e</td></tr>";
		info += "<tr><td><a href='http://";
		info += WiFi.localIP().toString().c_str();
		info += "/getCurve?from=xxxxx&to=yyyyy' target='_blank'>/getCurve?from=xxxxx&to=yyyyy</a></td><td>Donne le courant en fonction du temps sur une plage de la m&eacute;moire (max 20000 points)</td></tr>";
		info += "</table>";
		setCrossOrigin();
		server.send(200, "text/html", info);
	}); 

	// Donne la tension
	server.on("/getTension", [](){
		float shuntvoltage = ina219.getShuntVoltage_mV();
		float busvoltage = ina219.getBusVoltage_V();
		float loadvoltage = busvoltage + (shuntvoltage / 1000);	
		DynamicJsonDocument root(2048);
		root["tension"] = loadvoltage;
		root["unit"] = "Volt";
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});
  
	// Donne la puissance
	server.on("/getPower", [](){
		DynamicJsonDocument root(2048);
		root["power"] = ina219.getPower_mW();
		root["unit"] = "mW";
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});
  
	// Donne le courant
	server.on("/getCurrent", [](){
		DynamicJsonDocument root(2048);
		root["current"] = ina219.getCurrent_mA();
		root["unit"] = "mA";
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});
  
	// Affichage
	server.on("/setAffiche", []() {
		String data = server.arg("data");
		DynamicJsonDocument root(2048);
		if (data == "current") {
			affiche = CURRENT;
			root["affiche"] = "current";
			root["unit"] = "mA";
		} else if (data == "power") {
			affiche = POWER;
			root["affiche"] = "power";
			root["unit"] = "mW";
		} else if (data == "tension") {
			affiche = TENSION;
			root["affiche"] = "tension";
			root["unit"] = "Volt";
		} else if (data == "off") {
			affiche = OFF;
			root["affiche"] = "eteins";
		}
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});
	
	// Donne l'état de l'afficheur
	server.on("/getAffiche", [](){
		DynamicJsonDocument root(2048);
		switch(affiche) {
			case CURRENT:
				root["state"] = "Courant";
				break;
			case POWER:
				root["state"] = "Puissance";
				break;
			case TENSION:
				root["state"] = "Tension";
				break;
			case OFF:
				root["state"] = "Eteins";
				break;
		}
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Donne l'horloge
	server.on("/getHorloge", [](){
		DynamicJsonDocument root(2048);
		root["year"] = RTC.getYear();
		root["month"] = RTC.getMonth();
		root["day"] = RTC.getDay();
		root["hour"] = RTC.getHours();
		root["minute"] = RTC.getMinutes();
		root["second"] = RTC.getSeconds();
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Positionne la tension (entre 2 et 11V)
	server.on("/setTension", []() {
		String valeur = server.arg("valeur");
		float val = atof(valeur.c_str());
		if(val < 2.0) { // La tension ne peut pas être inférieure à 2V
			val = 2.0;
		}
		val -= 2.0; // Tension minimale avec le potentiomètre à 0 (en fait 75ohms suivant le datasheet)
		val /= 0.07; // cohéficient résistance tension 70mV par pas du potentiomètre
		if(val > 255.0) { // La valeur du potentiomètre ne doit pas être supérieure à 255, sinon il y a dépassement de capacité de l'uint8_t
			val = 255.0;
		}
		digiPot.writeWiper((uint8_t)val); 
		DynamicJsonDocument root(2048);
		root["tension"] = valeur;
		root["unit"] = "Volt";
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	}); 

	// Positionne le réveil
	server.on("/setReveil", []() {
		String dateReveil = server.arg("date");
		String heureReveil = server.arg("heure");
		jour = atoi(dateReveil.substring(0, 2).c_str());
		mois = atoi(dateReveil.substring(3, 5).c_str());
		annee = atoi(dateReveil.substring(6, 10).c_str());
		heure = atoi(heureReveil.substring(0, 2).c_str());
		minute = atoi(heureReveil.substring(3, 5).c_str());
		seconde = atoi(heureReveil.substring(6, 8).c_str());
		DynamicJsonDocument root(2048);
		root["day"] = jour;
		root["month"] = mois;
		root["year"] = annee;
		root["hour"] = heure;
		root["minute"] = minute;
		root["second"] = seconde;
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	}); 

	// Donne le réveil
	server.on("/getReveil", [](){
		DynamicJsonDocument root(2048);
		root["year"] = annee;
		root["month"] = mois;
		root["day"] = jour;
		root["hour"] = heure;
		root["minute"] = minute;
		root["second"] = seconde;
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Active ou désactive le relai /setrelai?state=on /setrelai?state=off
	server.on("/setRelai", []() {
		String state = server.arg("state");
		if (state == "on") {
			digitalWrite(RELAIS_SORTIE, LOW);
			stateRelai = ACTIF;
		} else if (state == "off") {
			digitalWrite(RELAIS_SORTIE, HIGH);
			stateRelai = INACTIF;
		}
		DynamicJsonDocument root(2048);
		root["relai"] = state;
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Donne l'état du relai
	server.on("/getRelai", [](){
		DynamicJsonDocument root(2048);
		if(stateRelai == ACTIF) {
			root["state"] = "on";
		} else {
			root["state"] = "off";
		}
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Donne la courbe complète du courant
	server.on("/getFullCurve", [](){

		String result = "";
		uint8_t avance = 0;
		for(uint32_t compteur = 0; compteur <= maxMemoryUsage; compteur++)
		{
			if(compteur % 10000 == 0) {
				// Fait défiler un caractère moins sur les afficheurs à chaque bloc de mémoire lu
				afficheAvance(avance);
				avance++;
				yield(); // Evite un reboot de l'ESP par le WatchDog si la commande dure trop longtemps
			}			
			result += SRAM.readByte(compteur);
			result += ";";
		}		
		setCrossOrigin();
		server.send(200, "text/plain", result);
	});

	// Donne la courbe du courant sur une plage de la mémoire
	server.on("/getCurve", [](){
		String from = server.arg("from");
		String to = server.arg("to");
		uint32_t min = atoi(from.c_str());
		uint32_t max = atoi(to.c_str());
		String result = "";
		uint8_t avance = 0;
		for(uint32_t compteur = min; compteur <= max; compteur++)
		{
			if(compteur % 10000 == 0) {
				// Fait défiler un caractère moins sur les afficheurs à chaque bloc de mémoire lu
				afficheAvance(avance);
				avance++;
				yield(); // Evite un reboot de l'ESP par le WatchDog si la commande dure trop longtemps
			}			
			result += SRAM.readByte(compteur);
			result += ";";
		}		
		setCrossOrigin();
		server.send(200, "text/plain", result);
	});

	// Active ou désactive l'utilisation de la mémoire série /setMemory?state=on /setMemory?state=off
	server.on("/setMemory", []() {
		String state = server.arg("state");
		if (state == "on") {
			memoryUsage = MEMORY_ON; 
		} else if (state == "off") {
			memoryUsage = MEMORY_OFF; 
		}
		DynamicJsonDocument root(2048);
		root["memory"] = state;
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Donne l'état de la mémoire
	server.on("/getMemory", [](){
		DynamicJsonDocument root(2048);
		if(memoryUsage == MEMORY_ON) {
			root["state"] = "on";
		} else {
			root["state"] = "off";
		}
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Active ou désactive l'utilisation circulaire de la mémoire série /setMemoryCircle?state=on /setMemoryCircle?state=off
	server.on("/setMemoryCircle", []() {
		String state = server.arg("state");
		if (state == "on") {
			memoryCircle = MEMORY_CIRCLE; 
		} else if (state == "off") {
			memoryCircle = MEMORY_NO_CIRCLE; 
		}
		DynamicJsonDocument root(2048);
		root["circle"] = state;
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Donne l'état de l'utilisation de la mémoire en mode d'écriture circulaire
	server.on("/getMemoryCircle", [](){
		DynamicJsonDocument root(2048);
		if(memoryCircle == MEMORY_CIRCLE) {
			root["state"] = "on";
		} else {
			root["state"] = "off";
		}
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Donne la position du pointeur de la mémoire
	server.on("/getMemoryPointer", [](){
		DynamicJsonDocument root(2048);
		root["pointer"] = pointeur;
		root["unit"] = "octet";
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Reset mémoire série
	server.on("/resetMemory", [](){
		// Initialisation mémoire et mise à 0
		uint8_t avance = 0;
		for(uint32_t compteur = 0; compteur <= MAX_UTIL_MEMORY; compteur++)
		{
			if(compteur % 10000 == 0) {
				// Fait défiler un caractère moins sur les afficheurs à chaque bloc de mémoire effacé
				afficheAvance(avance);
				avance++;
				yield(); // Evite un reboot de l'ESP par le WatchDog si la commande dure trop longtemps
			}			
			SRAM.writeByte(compteur, 0);
		}
		pointeur = 0;
		DynamicJsonDocument root(2048);
		root["memory"] = "reset";
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});
  
	// Positionne l'utilisation max de la mémoire série
	server.on("/setMemoryUsage", []() {
		String valeur = server.arg("valeur");
		maxMemoryUsage = atoi(valeur.c_str());
		if(maxMemoryUsage > MAX_UTIL_MEMORY) {
			maxMemoryUsage = MAX_UTIL_MEMORY;
		}
		DynamicJsonDocument root(2048);
		root["usage"] = maxMemoryUsage;
		root["unit"] = "octet";
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	}); 

	// Donne l'utilisation de la mémoire
	server.on("/getMemoryUsage", [](){
		DynamicJsonDocument root(2048);
		root["usage"] = maxMemoryUsage;
		root["unit"] = "octet";
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// Nombre de mesure memorisee par seconde dans la memoire serie
	server.on("/setMesure", []() {
		String nombre = server.arg("nombre");
		nombreMesure = atoi(nombre.c_str());
		switch(nombreMesure) {
			case 160: rate = 1;  delayMs = 0; break;
			case 90 : rate = 1;  delayMs = 1; break;
			case 72 : rate = 1;  delayMs = 2; break;
			case 54 : rate = 1;  delayMs = 3; break;
			case 40 : rate = 1;  delayMs = 4; break;
			case 13 : rate = 4;  delayMs = 4; break;
			case 7  : rate = 7;  delayMs = 4; break;
			case 4  : rate = 15; delayMs = 4; break;
			case 2  : rate = 30; delayMs = 4; break;
			case 1  : rate = 60; delayMs = 4; break;
			default : rate = 2;  delayMs = 4; break;
		}
		
		DynamicJsonDocument root(2048);
		root["nombre"] = nombreMesure;
		root["frequence"] = rate;
		root["temporisation"] = delayMs;
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	}); 
	
	// Donne le nombre de mesure memorisee par seconde dans la memoire serie
	server.on("/getMesure", [](){
		DynamicJsonDocument root(2048);
		root["nombre"] = nombreMesure;
		root["frequence"] = rate;
		root["temporisation"] = delayMs;
		String json;
		serializeJson(root, json);
		setCrossOrigin();
		server.send(200, "application/json", json);
	});

	// ************************************************************
	//                      Erreur de route
	// ************************************************************
	server.onNotFound(handleNotFound);

	// ************************************************************
	//                       start serveur
	// ************************************************************
	server.begin();
}

// ****************************************
//         *     ***** ***** *****
//         *     *   * *   * *   *
//         *     *   * *   * *****
//         *     *   * *   * *
//         ***** ***** ***** *
// ****************************************
void loop(void){
	// a chaque iteration, on appelle handleClient pour que les requetes soient traitees
	server.handleClient();
	
	// Active le relais un jour à une heure donnée
	if(jour == RTC.getDay() && mois == RTC.getMonth() && annee == RTC.getYear() && 
	   heure == RTC.getHours() && minute == RTC.getMinutes() && seconde == RTC.getSeconds()) {
		digitalWrite(RELAIS_SORTIE, LOW);
		stateRelai = ACTIF;
	}
	
	// mesure du courant
	float current_mA = ina219.getCurrent_mA();

	// Mémorise l'heure et le courant dans la SRAM (10eme de mA sur 2 octets)
	if(memoryUsage == MEMORY_ON) { 
		SRAMUData current;
		current.uSData = (uint16_t)(current_mA * 10);
		
		SRAM.writeByte(pointeur, RTC.getHours());
		pointeur++;
		SRAM.writeByte(pointeur, RTC.getMinutes());
		pointeur++;
		SRAM.writeByte(pointeur, RTC.getSeconds());
		pointeur++;
		SRAM.writeByte(pointeur, current.uCData[1]);
		pointeur++;
		SRAM.writeByte(pointeur, current.uCData[0]);
		pointeur++;
		// Si on est au bout de la SRAM, on repart au début si on est en mode cyclique, sinon on bloque sur la fin de la mémoire
		if(pointeur >= maxMemoryUsage) {
			if(memoryCircle == MEMORY_CIRCLE) {
				pointeur = 0;
			} else {
				pointeur = maxMemoryUsage;
			}
		}
	}

  //*****************************************
	//           Gestion affichage
  //*****************************************
  // Mesure la valeur à afficher
	float valeur;
	switch(affiche) {
		case OFF: 
			valeur = 99999.0; 
			break;
		case CURRENT: 
			valeur = current_mA; 
			break;
		case POWER: 
			valeur = ina219.getPower_mW(); 
			break;
		default: 
			valeur = ina219.getBusVoltage_V() + (ina219.getShuntVoltage_mV() / 1000.0);
	}
	uint8_t v1;
	uint8_t v2;
	uint8_t v3;
	uint8_t v4;
	if(valeur > 10000.0) {
		// Eteins chaque digit "rate" fois pendant "delayMs" ms
		for(int compteur = 0; compteur != rate; compteur++) {
			mcp.writeGPIOAB(vide + AFFICHEUR_MILLIERS);
			delay(delayMs);
			mcp.writeGPIOAB(vide + AFFICHEUR_CENTAINES);
			delay(delayMs);
			mcp.writeGPIOAB(vide + AFFICHEUR_DIZAINES);
			delay(delayMs);
			mcp.writeGPIOAB(vide + AFFICHEUR_UNITES);
			delay(delayMs);
		}
	} else if(valeur >= 1000.0) {
		v1 = (uint16_t)valeur % 10;
		v2 = ((uint16_t)valeur / 10) % 10;
		v3 = ((uint16_t)valeur / 100) % 10;
		v4 = (uint16_t)valeur / 1000;
		// Affiche chaque digit "rate" fois pendant "delayMs" ms
		for(int compteur = 0; compteur != rate; compteur++) {
			mcp.writeGPIOAB(chiffres[v4] + AFFICHEUR_MILLIERS);
			delay(delayMs);
			mcp.writeGPIOAB(chiffres[v3] + AFFICHEUR_CENTAINES);
			delay(delayMs);
			mcp.writeGPIOAB(chiffres[v2] + AFFICHEUR_DIZAINES);
			delay(delayMs);
			mcp.writeGPIOAB(chiffres[v1] + AFFICHEUR_UNITES);
			delay(delayMs);
		}
	} else if(valeur >= 100.0) {
		v1 = (uint16_t)(valeur * 10) % 10;
		v2 = (uint16_t)valeur % 10;
		v3 = ((uint16_t)valeur / 10) % 10;
		v4 = (uint16_t)valeur / 100;
		// Affiche chaque digit "rate" fois pendant "delayMs" ms
		for(int compteur = 0; compteur != rate; compteur++) {
			mcp.writeGPIOAB(chiffres[v4] + AFFICHEUR_MILLIERS);
			delay(delayMs);
			mcp.writeGPIOAB(chiffres[v3] + AFFICHEUR_CENTAINES);
			delay(delayMs);
			mcp.writeGPIOAB(chiffresVirgule[v2] + AFFICHEUR_DIZAINES);
			delay(delayMs);
			mcp.writeGPIOAB(chiffres[v1] + AFFICHEUR_UNITES);
			delay(delayMs);
		}
	} else if(valeur >= 10.0) {
		v1 = (uint16_t)(valeur * 100) % 10;
		v2 = (uint16_t)(valeur * 10) % 10;
		v3 = (uint16_t)valeur % 10;
		v4 = ((uint16_t)valeur / 10) % 10;
		// Affiche chaque digit "rate" fois pendant "delayMs" ms
		for(int compteur = 0; compteur != rate; compteur++) {
			mcp.writeGPIOAB(chiffres[v4] + AFFICHEUR_MILLIERS);
			delay(delayMs);
			mcp.writeGPIOAB(chiffresVirgule[v3] + AFFICHEUR_CENTAINES);
			delay(delayMs);
			mcp.writeGPIOAB(chiffres[v2] + AFFICHEUR_DIZAINES);
			delay(delayMs);
			mcp.writeGPIOAB(chiffres[v1] + AFFICHEUR_UNITES);
			delay(delayMs);
		}
	} else {
		v1 = (uint16_t)(valeur * 1000) % 10;
		v2 = (uint16_t)(valeur * 100) % 10;
		v3 = (uint16_t)(valeur * 10) % 10;
		v4 = (uint16_t)valeur % 10;
		// Affiche chaque digit "rate" fois pendant "delayMs" ms
		for(int compteur = 0; compteur != rate; compteur++) {
			mcp.writeGPIOAB(chiffresVirgule[v4] + AFFICHEUR_MILLIERS);
			delay(delayMs);
			mcp.writeGPIOAB(chiffres[v3] + AFFICHEUR_CENTAINES);
			delay(delayMs);
			mcp.writeGPIOAB(chiffres[v2] + AFFICHEUR_DIZAINES);
			delay(delayMs);
			mcp.writeGPIOAB(chiffres[v1] + AFFICHEUR_UNITES);
			delay(delayMs);
		}
	}
}

// ********************************************************************
//         ***** *   * *   *  **** ***** *****  ***  *   *  ****
//         *     *   * **  * *       *     *   *   * **  * *    
//         **    *   * * * * *       *     *   *   * * * *   *
//         *     *   * *  ** *       *     *   *   * *  **     *
//         *      ***  *   *  ****   *   *****  ***  *   * ****
// ********************************************************************
/**
 * \brief Affiche la dernière valeur de l'adresse IP
 * \note  Affichage pendant 300 * 16ms = 4.8s
 *
 * \param pValeur la valeur à afficher
 * \attention entre 0 et 255
 */
void afficheIP(uint16_t pValeur) {
	uint8_t v2;
	uint8_t v3;
	uint8_t v4;
	if(pValeur >= 100) {
		v2 = pValeur % 10;
		v3 = (pValeur / 10) % 10;
		v4 = pValeur / 100;
		for(int rate = 0; rate != 300; rate++) {
			mcp.writeGPIOAB(vide + AFFICHEUR_MILLIERS);
			delay(4);
			mcp.writeGPIOAB(chiffres[v4] + AFFICHEUR_CENTAINES);
			delay(4);
			mcp.writeGPIOAB(chiffres[v3] + AFFICHEUR_DIZAINES);
			delay(4);
			mcp.writeGPIOAB(chiffres[v2] + AFFICHEUR_UNITES);
			delay(4);
		}
	} else if(pValeur >= 10) {
		v3 = pValeur % 10;
		v4 = (pValeur / 10) % 10;
		for(int rate = 0; rate != 300; rate++) {
			mcp.writeGPIOAB(vide + AFFICHEUR_MILLIERS);
			delay(4);
			mcp.writeGPIOAB(chiffres[0] + AFFICHEUR_CENTAINES);
			delay(4);
			mcp.writeGPIOAB(chiffres[v4] + AFFICHEUR_DIZAINES);
			delay(4);
			mcp.writeGPIOAB(chiffres[v3] + AFFICHEUR_UNITES);
			delay(4);
		}
	} else {
		v4 = pValeur % 10;
		for(int rate = 0; rate != 300; rate++) {
			mcp.writeGPIOAB(vide + AFFICHEUR_MILLIERS);
			delay(4);
			mcp.writeGPIOAB(chiffres[0] + AFFICHEUR_CENTAINES);
			delay(4);
			mcp.writeGPIOAB(chiffres[0] + AFFICHEUR_DIZAINES);
			delay(4);
			mcp.writeGPIOAB(chiffres[v4] + AFFICHEUR_UNITES);
			delay(4);
		}
	}
}

/**
 * \brief Affiche un moins sur un afficheur pour indiquer l'avance d'un traitement
 *
 * \param pAvance l'afficheur à activer
 * \attention l'afficheur réellement utilisé sera un modulo 4 de la valeur pAvance
 */
void afficheAvance(uint8_t pAvance) {
	switch(pAvance % 4){
		case 0: mcp.writeGPIOAB(moins + AFFICHEUR_MILLIERS); break;
		case 1: mcp.writeGPIOAB(moins + AFFICHEUR_CENTAINES); break;
		case 2: mcp.writeGPIOAB(moins + AFFICHEUR_DIZAINES); break;
		case 3: mcp.writeGPIOAB(moins + AFFICHEUR_UNITES); break;
	}
}

/**
 * \brief Entête des réponses http (évite l'erreur cors)
 * \note https://www.mischianti.org/2020/07/15/how-to-create-a-rest-server-on-esp8266-or-esp32-cors-request-option-and-get-part-4/
 *
 */
void setCrossOrigin(){
    server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
    server.sendHeader(F("Access-Control-Max-Age"), F("600"));
    server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
    server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
};

/**
 * \brief Manage not found URL
 * \note https://www.mischianti.org/2020/07/15/how-to-create-a-rest-server-on-esp8266-or-esp32-cors-request-option-and-get-part-4/
 *
 */
void handleNotFound() {
  String message = "URL error\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  setCrossOrigin();
  server.send(404, "text/plain", message);
}
