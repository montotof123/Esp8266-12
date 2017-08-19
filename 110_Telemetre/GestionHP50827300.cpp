/*
 * GestionHP50827300.cpp
 *
 *  Created on: 16 juillet 2017
 *      Author: totof
 * Controle de l'afficheur HP 5082-7300
*/
 
#include <stdint.h>
#include "GestionHP50827300.h"

// *******************************************************
// Constructeur vide
// *******************************************************
GestionHP50827300::GestionHP50827300() {
}

// *******************************************************
// Constructeur
// @param adresse du MCP23S17
// @param broche CS du MCP23S17
// @param input1 entree input1 de l'afficheur
// @param input2 entree input2 de l'afficheur
// @param input4 entree input4 de l'afficheur
// @param input8 entree input8 de l'afficheur
// @param decimalPoint entree point decimal de l'afficheur
// @param latchEnable entree verouillage de l'afficheur
// *******************************************************
GestionHP50827300::GestionHP50827300(uint8_t adresse, uint8_t cs, uint8_t latchEnable) {
	init(adresse, cs, latchEnable);
}

// *******************************************************
// Init si constructeur vide
// @param adresse du MCP23S17
// @param broche CS du MCP23S17
// @param input1 entree input1 de l'afficheur
// @param input2 entree input2 de l'afficheur
// @param input4 entree input4 de l'afficheur
// @param input8 entree input8 de l'afficheur
// @param decimalPoint entree point decimal de l'afficheur
// @param latchEnable entree verouillage de l'afficheur
// *******************************************************
void GestionHP50827300::init(uint8_t adresse, uint8_t cs, uint8_t latchEnable) {
	switch(latchEnable) {
		case 0: PinLatchEnable = 0x01; break;
		case 1: PinLatchEnable = 0x02; break;
		case 2: PinLatchEnable = 0x04; break;
		case 3: PinLatchEnable = 0x08; break;
		case 4: PinLatchEnable = 0x10; break;
		case 5: PinLatchEnable = 0x20; break;
		case 6: PinLatchEnable = 0x40; break;
		case 7: PinLatchEnable = 0x80; break;
		default: PinLatchEnable = 0x00; //rien ne bouge
	}
	iochip.init(adresse, cs);
	iochip.begin();
	iochip.pinMode(0x0000);
	
	iochip.byteWrite(GPIOB, 0xFF);
	
	setBlank();
	
	valeur = NOT_A_NUMBER;
	point = false;
}

// ***********************************************
// Incremente la valeur de l'afficheur
// @return true si OK, false si valeur trop grande
// ***********************************************
bool GestionHP50827300::increment() {
	bool result = true;
	if(valeur < 9 && valeur != NOT_A_NUMBER) {
		valeur++;
		if(point) {
			setValueWithPoint(valeur);
		} else {
			setValueWithoutPoint(valeur);
		}
	} else {
		result = false;
	}
	return result;
}

// ***********************************************
// Decremente la valeur de l'afficheur
// @return true si OK, false si valeur trop petite
// ***********************************************
bool GestionHP50827300::decrement() {
	bool result = true;
	if(valeur > 0 && valeur != NOT_A_NUMBER) {
		valeur--;
		if(point) {
			setValueWithPoint(valeur);
		} else {
			setValueWithoutPoint(valeur);
		}
	} else {
		result = false;
	}
	return result;
}

// **************************************************
// Incremente la valeur de l'afficheur plusieurs fois
// @param pNombre le nombre d'incrementation
// @return true si OK, false si valeur trop grande
// **************************************************
bool GestionHP50827300::increment(uint8_t pNombre) {
	bool result = true;
	if(pNombre < 1) {
		return false;
	}
	if(valeur + pNombre <= 9 && valeur != NOT_A_NUMBER) {
		valeur += pNombre;
		if(point) {
			setValueWithPoint(valeur);
		} else {
			setValueWithoutPoint(valeur);
		}
	} else {
		result = false;
	}
	return result;
}

// **************************************************
// Decremente la valeur de l'afficheur plusieurs fois
// @param pNombre le nombre de decrementation
// @return true si OK, false si valeur trop petite
// **************************************************
bool GestionHP50827300::decrement(uint8_t pNombre) {
	bool result = true;
	if(pNombre < 1) {
		return false;
	}
	if(valeur - pNombre >= 0 && valeur != NOT_A_NUMBER) {
		valeur -= pNombre;
		if(point) {
			setValueWithPoint(valeur);
		} else {
			setValueWithoutPoint(valeur);
		}
	} else {
		result = false;
	}
	return result;
}

// ************************************************
// Affiche une valeur entre 0 et 9 sans la virgule
// @return true si OK, false si valeur hors echelle
// ************************************************
bool GestionHP50827300::setValueWithoutPoint(uint8_t pValeur) {
	bool result = true;
	switch(pValeur) {
		case 0: setValue(ZERO); break;
		case 1: setValue(UN); break;
		case 2: setValue(DEUX); break;
		case 3: setValue(TROIS); break;
		case 4: setValue(QUATRE); break;
		case 5: setValue(CINQ); break;
		case 6: setValue(SIX); break;
		case 7: setValue(SEPT); break;
		case 8: setValue(HUIT); break;
		case 9: setValue(NEUF); break;
		default: result = false;
	}
	if(result) {
		valeur = pValeur;
		point = false;
	}
	return result;
}

// ************************************************
// Affiche une valeur entre 0 et 9 avec la virgule
// @return true si OK, false si valeur hors echelle
// ************************************************
bool GestionHP50827300::setValueWithPoint(uint8_t pValeur) {
	bool result = true;
	switch(pValeur) {
		case 0: setValue(ZERO_POINT); break;
		case 1: setValue(UN_POINT); break;
		case 2: setValue(DEUX_POINT); break;
		case 3: setValue(TROIS_POINT); break;
		case 4: setValue(QUATRE_POINT); break;
		case 5: setValue(CINQ_POINT); break;
		case 6: setValue(SIX_POINT); break;
		case 7: setValue(SEPT_POINT); break;
		case 8: setValue(HUIT_POINT); break;
		case 9: setValue(NEUF_POINT); break;
		default: result = false;
	}
	if(result) {
		valeur = pValeur;
		point = true;
	}
	return result;
}

// ************************
// Allume tous les segments
// ************************	
void GestionHP50827300::setTest(void) {
	valeur = NOT_A_NUMBER;
	point = false;
	setValue(TEST);
}

// ************************
// Eteint tous les segments
// ************************	
void GestionHP50827300::setBlank(void) {
	valeur = NOT_A_NUMBER;
	point = false;
	setValue(BLANK);
}

// ****************
// Affiche un moins
// ****************	
void GestionHP50827300::setMinus(void) {
	valeur = NOT_A_NUMBER;
	point = false;
	setValue(MINUS);
}

// ****************
// Affiche un moins
// ****************	
void GestionHP50827300::setMinusWithPoint(void) {
	valeur = NOT_A_NUMBER;
	point = false;
	setValue(MINUS_POINT);
}

// ********************************************
// Affiche une valeur
// @return true si OK, false si valeur inconnue
// ********************************************	
bool GestionHP50827300::setValue(Values pValeur) {
	bool result = true;
	// Attention point decimal actif sur off
	switch(pValeur) {
		case ZERO        : iochip.byteWrite(GPIOA, 0x01); break;
		case UN          : iochip.byteWrite(GPIOA, 0x11); break;
		case DEUX        : iochip.byteWrite(GPIOA, 0x09); break;
		case TROIS       : iochip.byteWrite(GPIOA, 0x19); break;
		case QUATRE      : iochip.byteWrite(GPIOA, 0x05); break;
		case CINQ        : iochip.byteWrite(GPIOA, 0x15); break;
		case SIX         : iochip.byteWrite(GPIOA, 0x0D); break;
		case SEPT        : iochip.byteWrite(GPIOA, 0x1D); break;
		case HUIT        : iochip.byteWrite(GPIOA, 0x03); break;
		case NEUF        : iochip.byteWrite(GPIOA, 0x13); break;
		case ZERO_POINT  : iochip.byteWrite(GPIOA, 0x00); break;
		case UN_POINT    : iochip.byteWrite(GPIOA, 0x10); break;
		case DEUX_POINT  : iochip.byteWrite(GPIOA, 0x08); break;
		case TROIS_POINT : iochip.byteWrite(GPIOA, 0x18); break;
		case QUATRE_POINT: iochip.byteWrite(GPIOA, 0x04); break;
		case CINQ_POINT  : iochip.byteWrite(GPIOA, 0x14); break;
		case SIX_POINT   : iochip.byteWrite(GPIOA, 0x0C); break;
		case SEPT_POINT  : iochip.byteWrite(GPIOA, 0x1C); break;
		case HUIT_POINT  : iochip.byteWrite(GPIOA, 0x02); break;
		case NEUF_POINT  : iochip.byteWrite(GPIOA, 0x12); break;
		case TEST        : iochip.byteWrite(GPIOA, 0x0A); break;
		case BLANK       : iochip.byteWrite(GPIOA, 0x0F); break;
		case MINUS       : iochip.byteWrite(GPIOA, 0x17); break;
		case MINUS_POINT : iochip.byteWrite(GPIOA, 0x16); break;
		default          : result = false;
	}
	if(result) {
		iochip.byteWrite(GPIOB, 0xFF);
		iochip.byteWrite(GPIOB, ~PinLatchEnable);
		iochip.byteWrite(GPIOB, 0xFF);
	}
	return result;
}
	
// ******************
// Destructeur
// Désactive les GPIO
// ******************
GestionHP50827300::~GestionHP50827300() {
	iochip.pinMode(0xFFFF);
}

