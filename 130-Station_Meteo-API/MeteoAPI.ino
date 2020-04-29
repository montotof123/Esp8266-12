// ********************
// Module API Meteo
// totof 2020/04/29
// ********************
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// Box
const char* ssid = "dlink-4212";
const char* password =  "nhyyi53680";

// WiFi
WiFiClient espClient;

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
 
	// Mesures, mise en forme et envoi
	DynamicJsonDocument root(2048);
	root["temperature"] = bme.readTemperature();
	float pressure_hPa = bme.readPressure() / 100.0F;
	root["pression_brute"] = pressure_hPa;
	root["pression_niveau_mer"] = bme.seaLevelForAltitude(115.0F, pressure_hPa);
	root["altitude"] = bme.readAltitude(SEALEVELPRESSURE_HPA);
	root["humidite"] = bme.readHumidity();  

	String json;
	serializeJson(root, json);
	// Serial.println(json);
	
	HTTPClient http;    //Declare object of class HTTPClient
	http.begin("http://192.168.1.100:8081/api/meteo");      //Specify request destination
    http.addHeader("Content-Type", "application/json");
    http.addHeader("auth-key", "My_authentication_key");	
	http.POST(json);
	// Serial.println(http.getString());
	http.end();  //Close connection

	// Deep sleep mode pour 5mn
	// Serial.println("Dodo pour 5mn");
	ESP.deepSleep(300e6); 
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
