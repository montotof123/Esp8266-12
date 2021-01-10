/*!
 *   \file    mcp45hv51.cpp
 *   \brief   test du potentiomètre et de la tension fourni par le LM2596
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    09/01/2021
 */
 
#include <MCP45HVX1.h>
#include <Adafruit_INA219.h>

/**
 *   \brief   Potentiomètre MCP45HV51
 */ 
MCP45HVX1 digiPot(0x3C);
/**
 *   \brief   Mesureur INA219
 */ 
Adafruit_INA219 ina219;

/**
 *   \brief   Commande du relai
 */ 
constexpr auto RELAIS_SORTIE = 15;

// *****************************************
//       ***** ***** ***** *   * *****
//       *     *       *   *   * *   *
//       ***** ****    *   *   * *****
//           * *       *   *   * *
//       ***** *****   *   ***** *
// *****************************************
void setup()
{  
	Serial.begin(115200);
	
	// Initialisation MCP45HV51
	digiPot.begin();  
	digiPot.connectTerminalB();
	digiPot.connectTerminalA();
	digiPot.connectWiper();
	
	// Initialisation INA219
	ina219.begin();
	
	// Initialisation Relai
	pinMode(RELAIS_SORTIE, OUTPUT);
	
	// Test relai
	digitalWrite(RELAIS_SORTIE, HIGH);
	delay(1000);
	digitalWrite(RELAIS_SORTIE, LOW);
	delay(1000);
	digitalWrite(RELAIS_SORTIE, HIGH);
	delay(1000);
	digitalWrite(RELAIS_SORTIE, LOW);
	delay(1000);
	digitalWrite(RELAIS_SORTIE, HIGH);
}

// ****************************************
//         *     ***** ***** *****
//         *     *   * *   * *   *
//         *     *   * *   * *****
//         *     *   * *   * *
//         ***** ***** ***** *
// ****************************************
void loop()
{
	float shuntvoltage = 0;
	float busvoltage = 0;
	float loadvoltage = 0;

	// Potentiomètre du minimum au maximum
	for(int compteur = 0; compteur != 256; compteur++) {
		digiPot.writeWiper(compteur); 
		
		shuntvoltage = ina219.getShuntVoltage_mV();
		busvoltage = ina219.getBusVoltage_V();
		loadvoltage = busvoltage + (shuntvoltage / 1000);
		
		Serial.print("Load Voltage:  "); 
		Serial.print(loadvoltage); 
		Serial.println(" V");
		Serial.print("readWiper: ");
		Serial.println(digiPot.readWiper());
		Serial.print("readTCon: ");
		Serial.println(digiPot.readTCON());
		
		delay(100);
	}
	// Potentiomètre du maximum au minimum
	for(int compteur = 255; compteur != -1; compteur--) {
		digiPot.writeWiper(compteur); 
		
		shuntvoltage = ina219.getShuntVoltage_mV();
		busvoltage = ina219.getBusVoltage_V();
		loadvoltage = busvoltage + (shuntvoltage / 1000);
		
		Serial.print("Load Voltage:  "); 
		Serial.print(loadvoltage); 
		Serial.println(" V");
		Serial.print("readWiper: ");
		Serial.println(digiPot.readWiper());
		Serial.print("readTCon: ");
		Serial.println(digiPot.readTCON());
		
		delay(100);
	}
} 
