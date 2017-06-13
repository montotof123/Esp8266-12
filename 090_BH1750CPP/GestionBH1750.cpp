/*
 * GestionBH1750.cpp
 *
 *  Created on: 5 may 2017
 *      Author: totof
 * Controle un module BH1750
 */

#include <Wire.h>
#include <Arduino.h>
#include "GestionBH1750.h"

namespace std {
  
// *************************
// Constructeur
// @param adresse du circuit 
// *************************
GestionBH1750::GestionBH1750(Adresse pAddress) {
	adresse = pAddress;
	Wire.begin(); 
	setState(BH1750_POWER_ON);
	setState(BH1750_RESET);
}

// ********************
// Activation d'un état
// @param l'état
// ********************
void GestionBH1750::setState(ModeState mode) {
	Wire.beginTransmission(adresse);
	Wire.write(mode);
	Wire.endTransmission();
}

// *************************
// Lecture de la mesure
// @param le mode de mesure
// @return la valeur mesuree
// *************************
float GestionBH1750::readMinResolutionLightLevel(ModeMesure mode) {
	i2cData data;
	float valeur;
	// Sensibilité max (0001_1111)
	Wire.beginTransmission(adresse);
	Wire.write(0x40); // 01000_000
	Wire.endTransmission();
	Wire.beginTransmission(adresse);
	Wire.write(0x7F); // 011_11111
	Wire.endTransmission();
	Wire.beginTransmission(adresse);
	Wire.write(mode); 
	Wire.endTransmission();

	// Temps de mesure
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2:
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE: delay(70); break;
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: delay(8); break;
	}
	
	// Mesure
	Wire.requestFrom(adresse, 2); // Deux octets sont requis
	if (2 <= Wire.available()) {
		data.uCData[1] = Wire.read();  // Octet de poids fort
		data.uCData[0] = Wire.read();  // Octet de poids faible
	}

	// Mise à l'échelle
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2: valeur = (float)data.uSData / 1.08; break;
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: valeur = (float)data.uSData / 0.54; break;
	}
	return valeur;
}

// *************************
// Lecture de la mesure
// @param le mode de mesure
// @return la valeur mesuree
// *************************
float GestionBH1750::readLightLevel(ModeMesure mode) {
	i2cData data;
	float valeur;
	// Sensibilité standard (0100_0101)
	Wire.beginTransmission(adresse);
	Wire.write(0x42); // 01000_010
	Wire.endTransmission();
	Wire.beginTransmission(adresse);
	Wire.write(0x65); // 011_00101
	Wire.endTransmission();
	Wire.beginTransmission(adresse);
	Wire.write(mode); 
	Wire.endTransmission();

 	// Temps de mesure
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2:
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE: delay(150); break;
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: delay(20); break;
	}
	
	// Mesure
	Wire.requestFrom(adresse, 2); // Deux octets sont requis
	if (2 <= Wire.available()) {
		data.uCData[1] = Wire.read();  // Octet de poids fort
		data.uCData[0] = Wire.read();  // Octet de poids faible
	}
	
	// Mise à l'échelle
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2: valeur = (float)data.uSData / 2.4; break;
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: valeur = (float)data.uSData / 1.2; break;
	}
	return valeur;
}

// *************************
// Lecture de la mesure
// @param le mode de mesure
// @return la valeur mesuree
// *************************
float GestionBH1750::readDoubleResolutionLightLevel(ModeMesure mode) {
	i2cData data;
	float valeur;
	// Sensibilité double (1000_1010)
	Wire.beginTransmission(adresse);
	Wire.write(0x44); // 01000_100
	Wire.endTransmission();
	Wire.beginTransmission(adresse);
	Wire.write(0x6A); // 011_01010
	Wire.endTransmission();
	Wire.beginTransmission(adresse);
	Wire.write(mode); 
	Wire.endTransmission();

	// Temps de mesure
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2:
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE: delay(300); break;
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: delay(40); break;
	}
	
	// Mesure
	Wire.requestFrom(adresse, 2); // Deux octets sont requis
	if (2 <= Wire.available()) {
		data.uCData[1] = Wire.read();  // Octet de poids fort
		data.uCData[0] = Wire.read();  // Octet de poids faible
	}
	
	// Mise à l'échelle
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2: valeur = (float)data.uSData / 4.8; break;
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: valeur = (float)data.uSData / 2.4; break;
	}
	return valeur;
}

// *************************
// Lecture de la mesure
// @param le mode de mesure
// @return la valeur mesuree
// *************************
float GestionBH1750::readMaxResolutionLightLevel(ModeMesure mode) {
	i2cData data;
	float valeur;
	// Sensibilité max (1111_1110)
	Wire.beginTransmission(adresse);
	Wire.write(0x47); // 01000_111
	Wire.endTransmission();
	Wire.beginTransmission(adresse);
	Wire.write(0x7E); // 011_11110
	Wire.endTransmission();
	Wire.beginTransmission(adresse);
	Wire.write(mode); 
	Wire.endTransmission();

	// Temps de mesure
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2:
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE: delay(570); break;
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: delay(76); break;
	}
	
	// Mesure
	Wire.requestFrom(adresse, 2); // Deux octets sont requis
	if (2 <= Wire.available()) {
		data.uCData[1] = Wire.read();  // Octet de poids fort
		data.uCData[0] = Wire.read();  // Octet de poids faible
	}
	
		// Mise à l'échelle
	switch(mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2: valeur = (float)data.uSData / 9.12; break;
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE:
		case BH1750_ONE_TIME_LOW_RES_MODE: valeur = (float)data.uSData / 4.56; break;
	}
	return valeur;
}

// *************************
// Destructeur
// *************************
GestionBH1750::~GestionBH1750() {
	setState(BH1750_RESET);
	setState(BH1750_POWER_DOWN);
}

}
