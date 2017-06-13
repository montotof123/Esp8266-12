//=================================================
// Name        : tstBH1750.cpp
// Author      : totof
// Version     : 19/05/2017
// Copyright   : Free
// Description : test de la librairie GestionBH1750
//=================================================

#include "GestionBH1750.h"

using namespace std;

// Objets utilisés
GestionBH1750 bh1750(ADDRESS_AD0_LOW);

void setup() {
  Serial.begin(115200);  // Initialisation Terminal Série
}

// ******************
// Fonction pricipale
// ******************
void loop() {
	for(int compteur = 0; compteur != 10; compteur++) {
		Serial.print("STD-BH1750_CONTINUOUS_HIGH_RES_MODE  : ");
    Serial.println(bh1750.readLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE));
		Serial.print("STD-BH1750_CONTINUOUS_HIGH_RES_MODE_2: ");
    Serial.println(bh1750.readLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE_2));
		Serial.print("STD-BH1750_CONTINUOUS_LOW_RES_MODE   : ");
    Serial.println(bh1750.readLightLevel(BH1750_CONTINUOUS_LOW_RES_MODE));
		Serial.print("STD-BH1750_ONE_TIME_HIGH_RES_MODE    : ");
    Serial.println(bh1750.readLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE));
		Serial.print("STD-BH1750_ONE_TIME_HIGH_RES_MODE_2  : ");
    Serial.println(bh1750.readLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE_2));
		Serial.print("STD-BH1750_ONE_TIME_LOW_RES_MODE     : ");
    Serial.println(bh1750.readLightLevel(BH1750_ONE_TIME_LOW_RES_MODE));
	}
	Serial.println("BH1750_RESET                     : ");
	bh1750.setState(BH1750_RESET);
	for(int compteur = 0; compteur != 10; compteur++) {
		Serial.print("DBL-BH1750_CONTINUOUS_HIGH_RES_MODE  : ");
    Serial.println(bh1750.readDoubleResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE));
		Serial.print("DBL-BH1750_CONTINUOUS_HIGH_RES_MODE_2: ");
    Serial.println(bh1750.readDoubleResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE_2));
		Serial.print("DBL-BH1750_CONTINUOUS_LOW_RES_MODE   : ");
    Serial.println(bh1750.readDoubleResolutionLightLevel(BH1750_CONTINUOUS_LOW_RES_MODE));
		Serial.print("DBL-BH1750_ONE_TIME_HIGH_RES_MODE    : ");
    Serial.println(bh1750.readDoubleResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE));
		Serial.print("DBL-BH1750_ONE_TIME_HIGH_RES_MODE_2  : ");
    Serial.println(bh1750.readDoubleResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE_2));
		Serial.print("DBL-BH1750_ONE_TIME_LOW_RES_MODE     : ");
    Serial.println(bh1750.readDoubleResolutionLightLevel(BH1750_ONE_TIME_LOW_RES_MODE));
	}
	Serial.println("BH1750_RESET                     : ");
	bh1750.setState(BH1750_RESET);
	for(int compteur = 0; compteur != 10; compteur++) {
		Serial.print("MAX-BH1750_CONTINUOUS_HIGH_RES_MODE  : ");
    Serial.println(bh1750.readMaxResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE));
		Serial.print("MAX-BH1750_CONTINUOUS_HIGH_RES_MODE_2: ");
    Serial.println(bh1750.readMaxResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE_2));
		Serial.print("MAX-BH1750_CONTINUOUS_LOW_RES_MODE   : ");
    Serial.println(bh1750.readMaxResolutionLightLevel(BH1750_CONTINUOUS_LOW_RES_MODE));
		Serial.print("MAX-BH1750_ONE_TIME_HIGH_RES_MODE    : ");
    Serial.println(bh1750.readMaxResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE));
		Serial.print("MAX-BH1750_ONE_TIME_HIGH_RES_MODE_2  : ");
    Serial.println(bh1750.readMaxResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE_2));
		Serial.print("MAX-BH1750_ONE_TIME_LOW_RES_MODE     : ");
    Serial.println(bh1750.readMaxResolutionLightLevel(BH1750_ONE_TIME_LOW_RES_MODE));
	}
	Serial.println("BH1750_RESET                     : ");
	bh1750.setState(BH1750_RESET);
	for(int compteur = 0; compteur != 10; compteur++) {
		Serial.print("MIN-BH1750_CONTINUOUS_HIGH_RES_MODE  : ");
    Serial.println(bh1750.readMinResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE));
		Serial.print("MIN-BH1750_CONTINUOUS_HIGH_RES_MODE_2: ");
    Serial.println(bh1750.readMinResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE_2));
		Serial.print("MIN-BH1750_CONTINUOUS_LOW_RES_MODE   : ");
    Serial.println(bh1750.readMinResolutionLightLevel(BH1750_CONTINUOUS_LOW_RES_MODE));
		Serial.print("MIN-BH1750_ONE_TIME_HIGH_RES_MODE    : ");
    Serial.println(bh1750.readMinResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE));
		Serial.print("MIN-BH1750_ONE_TIME_HIGH_RES_MODE_2  : ");
    Serial.println(bh1750.readMinResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE_2));
		Serial.print("MIN-BH1750_ONE_TIME_LOW_RES_MODE     : ");
    Serial.println(bh1750.readMinResolutionLightLevel(BH1750_ONE_TIME_LOW_RES_MODE));
	}
}
