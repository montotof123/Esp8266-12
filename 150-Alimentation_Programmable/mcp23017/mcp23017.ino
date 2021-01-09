#include <Wire.h>
/*!
 *   \file    mcp23017.cpp
 *   \brief   Affichage de nombre sur des afficheurs 3641BS
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    09/01/2021
 */
 
#include <Adafruit_MCP23017.h>
#include "Chiffres7seg.h"

#define AFFICHEUR_MILLIERS  0x0100
#define AFFICHEUR_CENTAINES 0x0200
#define AFFICHEUR_DIZAINES  0x0400
#define AFFICHEUR_UNITES    0x0800

/**
 *   \brief   expander MCP23017
 */ 
Adafruit_MCP23017 mcp;

/**
 *   \brief   nombres à afficher
 */ 
float valeur []  = {
  61.52,
  123.4,
  98.7,
  1.236,
  0.2,
  8426.36,
  0.569,
  9.56,
  0.001,
  96.30,
  0,
  5
};
  
// *****************************************
//       ***** ***** ***** *   * *****
//       *     *       *   *   * *   *
//       ***** ****    *   *   * *****
//           * *       *   *   * *
//       ***** *****   *   ***** *
// *****************************************
void setup() {  
	mcp.begin();      // use default address 0

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
}

// ****************************************
//         *     ***** ***** *****
//         *     *   * *   * *   *
//         *     *   * *   * *****
//         *     *   * *   * *
//         ***** ***** ***** *
// ****************************************
void loop() {
	uint8_t v1;
	uint8_t v2;
	uint8_t v3;
	uint8_t v4;
	for(int val = 0; val != 12; val++) {
		if(valeur[val] >= 1000.0) {
			v1 = (uint16_t)valeur[val] % 10;
			v2 = ((uint16_t)valeur[val] / 10) % 10;
			v3 = ((uint16_t)valeur[val] / 100) % 10;
			v4 = (uint16_t)valeur[val] / 1000;
			for(int rate = 0;rate != 800; rate++) {
				mcp.writeGPIOAB(chiffres[v4] + AFFICHEUR_MILLIERS);
				delay(1);
				mcp.writeGPIOAB(chiffres[v3] + AFFICHEUR_CENTAINES);
				delay(1);
				mcp.writeGPIOAB(chiffres[v2] + AFFICHEUR_DIZAINES);
				delay(1);
				mcp.writeGPIOAB(chiffres[v1] + AFFICHEUR_UNITES);
				delay(1);
			}
		} else if(valeur[val] >= 100.0) {
			v1 = (uint16_t)(valeur[val] * 10) % 10;
			v2 = (uint16_t)valeur[val] % 10;
			v3 = ((uint16_t)valeur[val] / 10) % 10;
			v4 = (uint16_t)valeur[val] / 100;
			for(int rate = 0;rate != 800; rate++) {
				mcp.writeGPIOAB(chiffres[v4] + AFFICHEUR_MILLIERS);
				delay(1);
				mcp.writeGPIOAB(chiffres[v3] + AFFICHEUR_CENTAINES);
				delay(1);
				mcp.writeGPIOAB(chiffresVirgule[v2] + AFFICHEUR_DIZAINES);
				delay(1);
				mcp.writeGPIOAB(chiffres[v1] + AFFICHEUR_UNITES);
				delay(1);
			}
		} else if(valeur[val] >= 10.0) {
			v1 = (uint16_t)(valeur[val] * 100) % 10;
			v2 = (uint16_t)(valeur[val] * 10) % 10;
			v3 = (uint16_t)valeur[val] % 10;
			v4 = ((uint16_t)valeur[val] / 10) % 10;
			for(int rate = 0;rate != 800; rate++) {
				mcp.writeGPIOAB(chiffres[v4] + AFFICHEUR_MILLIERS);
				delay(1);
				mcp.writeGPIOAB(chiffresVirgule[v3] + AFFICHEUR_CENTAINES);
				delay(1);
				mcp.writeGPIOAB(chiffres[v2] + AFFICHEUR_DIZAINES);
				delay(1);
				mcp.writeGPIOAB(chiffres[v1] + AFFICHEUR_UNITES);
				delay(1);
			}
		} else {
			v1 = (uint16_t)(valeur[val] * 1000) % 10;
			v2 = (uint16_t)(valeur[val] * 100) % 10;
			v3 = (uint16_t)(valeur[val] * 10) % 10;
			v4 = (uint16_t)valeur[val] % 10;
			for(int rate = 0;rate != 800; rate++) {
				mcp.writeGPIOAB(chiffresVirgule[v4] + AFFICHEUR_MILLIERS);
				delay(1);
				mcp.writeGPIOAB(chiffres[v3] + AFFICHEUR_CENTAINES);
				delay(1);
				mcp.writeGPIOAB(chiffres[v2] + AFFICHEUR_DIZAINES);
				delay(1);
				mcp.writeGPIOAB(chiffres[v1] + AFFICHEUR_UNITES);
				delay(1);
			}
		}
	}
}
