/*
 * GestionHCSR04.cpp
 *
 *  Created on: 14 août 2017
 *      Author: totof
 */

#include "GestionHCSR04.h"
#include <Arduino.h>

// *************************************
// Constructeur
// Mémorise le numéro des pins utilisées
// @param numéro de pin du trigger
// @param numéro de pin de l'echo
// *************************************
GestionHCSR04::GestionHCSR04(int pinTrigger, int pinEcho) {
	trigger = pinTrigger;
	echo = pinEcho;
	pinMode(trigger, OUTPUT);
	pinMode(echo, INPUT);
	digitalWrite(trigger, LOW);  
}

// **********************************************************
// Positionne la temperature pour calcul de la vitesse du son
// **********************************************************
void GestionHCSR04::setTemperature(float pTemperature) {
	temperature = pTemperature;
}

// ********************************
// Donne la temperature positionnée
// ********************************
float GestionHCSR04::getTemperature(void) {
	return temperature;
}
 
// ***************************
// Renvoie la distance mesurée
// ***************************
float GestionHCSR04::getDistance(void) {
	long duration;
	digitalWrite(trigger, LOW);  
	delayMicroseconds(2); 

	digitalWrite(trigger, HIGH);
	delayMicroseconds(10); 
  
	digitalWrite(trigger, LOW);
	duration = pulseIn(echo, HIGH);

	// Calcul de la distance
	float vitesse = 0.62 * temperature + 331.6;
	return vitesse * (float)duration / 2000000.0;
}

// **********************************************************
// Destructeur
// **********************************************************
GestionHCSR04::~GestionHCSR04() {
	pinMode(trigger, INPUT);
	pinMode(echo, INPUT);
	digitalWrite(trigger, LOW);  
	digitalWrite(echo, LOW);  
}
