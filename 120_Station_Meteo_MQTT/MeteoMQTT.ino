// ********************
// Module MQTT Meteo
// totof 2020/03/25
// ********************
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// Box
const char* ssid = "dlink-4212";
const char* password =  "nhyyi53680";

// Serveur MQTT
const char* mqttServer = "192.168.1.27";
const int   mqttPort = 1883;
const char* mqttUser = "montotof";
const char* mqttPassword = "trucmuche";
 
// WiFi
WiFiClient espClient;

// MQTT
PubSubClient client(espClient);

// BME280 en I2C
Adafruit_BME280 bme;

// *****************************************
//       ***** ***** ***** *   * *****
//       *     *       *   *   * *   *
//       ***** ****    *   *   * *****
//           * *       *   *   * *
//       ***** *****   *   ***** *
// *****************************************
void setup() {
	// Parametres serie
	// Serial.begin(115200);
	// Serial.setTimeout(2000);
	// while(!Serial) { }

	// Initialisation BME
	if (! bme.begin(0x76)) {
		// Serial.println("Could not find a valid BME280 sensor, check wiring!");
		while (1);
	}

	// Connexion au Wifi
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		// Serial.println("Connecting to WiFi..");
	}
	// Serial.println("Connected to the WiFi network");
 
	// Connexion au serveur MQTT
	client.setServer(mqttServer, mqttPort);
	while (!client.connected()) {
		// Serial.println("Connecting to MQTT...");
		if (client.connect("ESP8266Client1", mqttUser, mqttPassword )) {
			// Serial.println("connected");  
      delay(1);
		} else {
			// Serial.print("failed with state ");
			// Serial.print(client.state());
			delay(2000);
		}
	}
	// Mesures, mise en forme et envoi
  // Température
	char mesure[50];
	char message[50];
	dtostrf(bme.readTemperature(), 5, 2, mesure);
	sprintf(message, "Temperature = %s - unité = degC", mesure);
	client.publish("meteo", message);
	// Serial.println(message);  

  //Pression brute
  float pressure_hPa = bme.readPressure() / 100.0F;
	dtostrf(pressure_hPa, 5, 2, mesure);
	sprintf(message, "Pression = %s - unité = hPa", mesure);
	client.publish("meteo", message);
	// Serial.println(message);  

  // Pression ramenéau niveau de la mer
  dtostrf(bme.seaLevelForAltitude(115.0F, pressure_hPa), 5, 2, mesure);
  sprintf(message, "Pression niveau mer = %s - unité = hPa", mesure);
  client.publish("meteo", message);
  // Serial.println(message);  

  // Altitude si pression au niveau de la mer = 1013.25hPa
	dtostrf(bme.readAltitude(SEALEVELPRESSURE_HPA), 5, 2, mesure);
	sprintf(message, "Altitude approximative = %s - unité = m", mesure);
	client.publish("meteo", message);
	// Serial.println(message);  

  //Humidité
	dtostrf(bme.readHumidity(), 5, 2, mesure);
	sprintf(message, "Humidite = %s - unité = %", mesure);
	client.publish("meteo", message);
	// Serial.println(message);  

  // Envoi des messages
  client.subscribe("meteo");

	// Deep sleep mode pour 60s
	// Serial.println("Dodo pour 60s");
	ESP.deepSleep(60e6); 
}

// ****************************************
//         *     ***** ***** *****
//         *     *   * *   * *   *
//         *     *   * *   * *****
//         *     *   * *   * *
//         ***** ***** ***** *
// ****************************************
// Ne rien mettre dedans car le programme n'y vient jamais il s'arrête au deepSleep du setup
void loop() {
}
