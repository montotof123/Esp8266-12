//====================================================
// Name        : tstAffichage.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie GestionAffichage
//====================================================

#include <stdlib.h>   // La librairie standard
#include "GestionAffichage.h"

GestionAffichage affichage(0, 15);

void setup() {	
	Serial.begin (115200);
	Serial.println("Test du HP Affichage");
}

void loop() {
	Serial.println("9999, 0");
	affichage.affiche(9999, 0);
	delay(1000);

	Serial.println("999, 0");
	affichage.affiche(999, 0);
	delay(1000);

	Serial.println("99, 0");
	affichage.affiche(99, 0);
	delay(1000);

	Serial.println("9, 0");
	affichage.affiche(9, 0);
	delay(1000);

	Serial.println("999, 1");
	affichage.affiche(999, 1);
	delay(1000);

	Serial.println("99, 1");
	affichage.affiche(99, 1);
	delay(1000);

	Serial.println("9, 1");
	affichage.affiche(9, 1);
	delay(1000);

	Serial.println("99, 2");
	affichage.affiche(99, 2);
	delay(1000);

	Serial.println("9, 2");
	affichage.affiche(9, 2);
	delay(1000);

	Serial.println("9, 3");
	affichage.affiche(9, 3);
	delay(1000);

	Serial.println("9999, 0");
	affichage.affiche(9999, 0);
	delay(1000);

	Serial.println("7777, 0");
	affichage.affiche(7777, 0);
	delay(1000);

	Serial.println("5555, 0");
	affichage.affiche(5555, 0);
	delay(1000);

	Serial.println("333.3, 1");
	affichage.affiche(333.3, 1);
	delay(1000);

	Serial.println("11.11, 2");
	affichage.affiche(11.11, 2);
	delay(1000);

	Serial.println("0.011, 3");
	affichage.affiche(0.011, 3);
	delay(1000);

	Serial.println("-999, 0");
	affichage.affiche(-999, 0);
	delay(1000);

	Serial.println("-99, 0");
	affichage.affiche(-99, 0);
	delay(1000);
	
	Serial.println("-9, 0");
	affichage.affiche(-9, 0);
	delay(1000);
	
	Serial.println("-99, 1");
	affichage.affiche(-99, 1);
	delay(1000);
	
	Serial.println("-9, 1");
	affichage.affiche(-9, 1);
	delay(1000);
	
	Serial.println("-9, 2");
	affichage.affiche(-9, 2);
	delay(1000);
	
	Serial.println("-999, 0");
	affichage.affiche(-999, 0);
	delay(1000);
	
	Serial.println("-777, 0");
	affichage.affiche(-777, 0);
	delay(1000);
	
	Serial.println("-444, 0");
	affichage.affiche(-444, 0);
	delay(1000);
	
	Serial.println("-99.9, 1");
	affichage.affiche(-99.9, 1);
	delay(1000);

	Serial.println("-6.66, 2");
	affichage.affiche(-6.66, 2);
	delay(1000);

	Serial.println("-0.22, 3");
	affichage.affiche(-0.22, 3);
	delay(1000);

	Serial.println("-12.3, 1");
	affichage.affiche(-12.3, 1);
	delay(1000);

	Serial.println("-999, 1");
	affichage.affiche(-999, 1);
	delay(1000);

	Serial.println("9999, 1");
	affichage.affiche(9999, 1);
	delay(1000);

	Serial.println("-999, 2");
	affichage.affiche(-999, 2);
	delay(1000);

	Serial.println("9999, 2");
	affichage.affiche(9999, 2);
	delay(1000);

	Serial.println("-999, 3");
	affichage.affiche(-999, 3);
	delay(1000);

	Serial.println("9999, 3");
	affichage.affiche(9999, 3);
	delay(1000);

	Serial.println("0, 3");
	affichage.affiche(0, 3);
	delay(1000);

	Serial.println("50, 2");
	affichage.affiche(50, 2);
	delay(1000);

	Serial.println("-0, 3");
	affichage.affiche(-0, 3);
	delay(1000);

	Serial.println("1, 1");
	affichage.affiche(1, 1);
	delay(1000);

	Serial.println("10, 1");
	affichage.affiche(10, 1);
	delay(1000);

	Serial.println("-1, 1");
	affichage.affiche(-1, 1);
	delay(1000);

	Serial.println("1.234567, 3");
	affichage.affiche(1.234567, 3);
	delay(1000);

	Serial.println("1.234567, 2");
	affichage.affiche(1.234567, 2);
	delay(1000);

	Serial.println("1.234567, 1");
	affichage.affiche(1.234567, 1);
	delay(1000);

	Serial.println("1.234567, 0");
	affichage.affiche(1.234567, 0);
	delay(1000);

	Serial.println("-1.234567, 3");
	affichage.affiche(-1.234567, 3);
	delay(1000);

	Serial.println("-1.234567, 2");
	affichage.affiche(-1.234567, 2);
	delay(1000);

	Serial.println("-1.234567, 1");
	affichage.affiche(-1.234567, 1);
	delay(1000);

	Serial.println("-1.234567, 0");
	affichage.affiche(-1.234567, 0);
	delay(1000);

	Serial.println("1.034567, 3");
	affichage.affiche(1.034567, 3);
	delay(1000);

	Serial.println("1.204567, 3");
	affichage.affiche(1.204567, 3);
	delay(1000);

	Serial.println("1.230567, 3");
	affichage.affiche(1.230567, 3);
	delay(1000);

	Serial.println("1.204567, 2");
	affichage.affiche(1.204567, 2);
	delay(1000);

	Serial.println("-1.034567, 1");
	affichage.affiche(-1.034567, 1);
	delay(1000);

	Serial.println("-1.034567, 0");
	affichage.affiche(-1.034567, 0);
	delay(1000);

	Serial.println("-0.034567, 3");
	affichage.affiche(-0.034567, 3);
	delay(1000);

	Serial.println("-0.204567, 3");
	affichage.affiche(-0.204567, 3);
	delay(1000);

	Serial.println("-0.230567, 3");
	affichage.affiche(-0.230567, 3);
	delay(1000);

	Serial.println("-0.034567, 2");
	affichage.affiche(-0.034567, 2);
	delay(1000);

	Serial.println("-0.204567, 2");
	affichage.affiche(-0.204567, 2);
	delay(1000);

	Serial.println("-0.030567, 1");
	affichage.affiche(-0.030567, 1);
	delay(1000);

	Serial.println("-0.030567, 0");
	affichage.affiche(-0.030567, 0);
	delay(1000);

	Serial.println("10000, 0");
	affichage.affiche(10000, 0);
	delay(1000);

	Serial.println("-1000, 1");
	affichage.affiche(-1000, 1);
	delay(1000);

	Serial.println("-9, 4");
	affichage.affiche(-9, 4);
	delay(1000);

	Serial.println("50, -1");
	affichage.affiche(50, -1);
	delay(1000);
}

	