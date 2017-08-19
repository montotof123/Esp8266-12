/*
 * GestionAffichage.cpp
 *
 *  Created on: 31 juillet 2017
 *      Author: totof
 * Affichage de valeurs sur 4 afficheurs HP5082-7300
*/
 
#include "GestionAffichage.h"

// *******************************************************
// Constructeur
// *******************************************************
GestionAffichage::GestionAffichage(uint8_t adresse, uint8_t cs) {
	afficheur4.init(adresse, cs, 0);
	afficheur3.init(adresse, cs, 1);
	afficheur2.init(adresse, cs, 2);
	afficheur1.init(adresse, cs, 3);
}

// ******************
// Eteint l'affichage
// ******************
void GestionAffichage::eteindre() {
	afficheur4.setBlank();
	afficheur3.setBlank();
	afficheur2.setBlank();
	afficheur1.setBlank();
}

// ***********************************************
// Decremente la valeur de l'afficheur
// @return true si OK, false si valeur trop petite
// ***********************************************
bool GestionAffichage::affiche(float valeur, int nbChVirgule) {
	int valAfficheur4;
	int valAfficheur3;
	int valAfficheur2;
	int valAfficheur1;
	float valeurCalcul;
	
	// controles
	if(nbChVirgule < 0) {
		return false;
	}
	
	if(nbChVirgule > 3) {
		return false;
	}
	
	if(valeur < -999.0) {
		return false;
	}
	
	if(valeur > 9999.0) {
		return false;
	}
	
	switch(nbChVirgule) {
		case 0: valeurCalcul = valeur;
				break;
		case 1: valeurCalcul = valeur * 10;
				break;
		case 2: valeurCalcul = valeur * 100;
				break;
		case 3: valeurCalcul = valeur * 1000;
				break;
	}
	if(valeur >= 0) {
		valAfficheur4 = (int)(valeurCalcul / 1000);
		valAfficheur3 = (int)(valeurCalcul / 100) - (10 * valAfficheur4);
		valAfficheur2 = (int)(valeurCalcul / 10) - (100 * valAfficheur4) - (10 * valAfficheur3);
		valAfficheur1 = (int)(valeurCalcul) - (1000 * valAfficheur4) - (100 * valAfficheur3) - (10 * valAfficheur2);
		
		if(valAfficheur4 > 9 || valAfficheur3 > 9 || valAfficheur2 > 9 || valAfficheur1 > 9) {
			return false;
		}
		if(valAfficheur4 < 0 || valAfficheur3 < 0 || valAfficheur2 < 0 || valAfficheur1 < 0) {
			return false;
		}
		
		switch(nbChVirgule) {
			case 0: if(valeur < 1000.0) {
						afficheur4.setBlank();
					} else {
						afficheur4.setValueWithoutPoint(valAfficheur4); 
					}
					if(valeur < 100.0) {
						afficheur3.setBlank();
					} else {
						afficheur3.setValueWithoutPoint(valAfficheur3);
					}
					if(valeur < 10.0) {
						afficheur2.setBlank();
					} else {
						afficheur2.setValueWithoutPoint(valAfficheur2); 
					}
					afficheur1.setValueWithoutPoint(valAfficheur1); 
					break;
			case 1: if(valeur < 100.0) {
						afficheur4.setBlank();
					} else {
						afficheur4.setValueWithoutPoint(valAfficheur4);
					}
					if(valeur < 10.0) {
						afficheur3.setBlank();
					} else {
						afficheur3.setValueWithoutPoint(valAfficheur3);
					}
					afficheur2.setValueWithPoint(valAfficheur2); 
					afficheur1.setValueWithoutPoint(valAfficheur1); 
					break;
			case 2: if(valeur < 10.0) {
						afficheur4.setBlank();
					} else {
						afficheur4.setValueWithoutPoint(valAfficheur4);
					}
					afficheur3.setValueWithPoint(valAfficheur3); 
					afficheur2.setValueWithoutPoint(valAfficheur2); 
					if(valAfficheur1 == 0) {
						afficheur1.setBlank();
					} else {
						afficheur1.setValueWithoutPoint(valAfficheur1); 
					}
					break;
			case 3: afficheur4.setValueWithPoint(valAfficheur4); 
					afficheur3.setValueWithoutPoint(valAfficheur3); 
					if(valAfficheur2 == 0 && valAfficheur1 == 0) {
						afficheur2.setBlank();
					} else {
						afficheur2.setValueWithoutPoint(valAfficheur2);
					}
					if(valAfficheur1 == 0) {
						afficheur1.setBlank();
					} else {
						afficheur1.setValueWithoutPoint(valAfficheur1); 
					}
					break;
		}	
	} else {
		valAfficheur3 = -(int)(valeurCalcul / 100);
		valAfficheur2 = -(int)(valeurCalcul / 10) - (10 * valAfficheur3);
		valAfficheur1 = -(int)(valeurCalcul) - (100 * valAfficheur3) - (10 * valAfficheur2);
		
		if(valAfficheur3 > 9 || valAfficheur2 > 9 || valAfficheur1 > 9) {
			return false;
		}
		if(valAfficheur3 < 0 || valAfficheur2 < 0 || valAfficheur1 < 0) {
			return false;
		}
		
		switch(nbChVirgule) {
			case 0: afficheur4.setMinus(); 
					if(valeur > -100.0) {
						afficheur3.setBlank();
					} else {
						afficheur3.setValueWithoutPoint(valAfficheur3);
					}
					if(valeur > -10.0) {
						afficheur2.setBlank();
					} else {
						afficheur2.setValueWithoutPoint(valAfficheur2);
					}
					afficheur1.setValueWithoutPoint(valAfficheur1); 
					break;
			case 1: afficheur4.setMinus(); 
					if(valeur > -10.0) {
						afficheur3.setBlank();
					} else {
						afficheur3.setValueWithoutPoint(valAfficheur3); 
					}
					afficheur2.setValueWithPoint(valAfficheur2); 
					afficheur1.setValueWithoutPoint(valAfficheur1); 
					break;
			case 2: afficheur4.setMinus(); 
					afficheur3.setValueWithPoint(valAfficheur3); 
					afficheur2.setValueWithoutPoint(valAfficheur2); 
					if(valAfficheur1 == 0) {
						afficheur1.setBlank();
					} else {
						afficheur1.setValueWithoutPoint(valAfficheur1); 
					}
					break;
			case 3: afficheur4.setMinusWithPoint(); 
					afficheur3.setValueWithoutPoint(valAfficheur3); 
					if(valAfficheur2 == 0 && valAfficheur1 == 0) {
						afficheur2.setBlank();
					} else {
						afficheur2.setValueWithoutPoint(valAfficheur2);
					}
					if(valAfficheur1 == 0) {
						afficheur1.setBlank();
					} else {
						afficheur1.setValueWithoutPoint(valAfficheur1); 
					}
					break;
		}	
	}
	
	return true;
}

// ******************
// Destructeur
// Désactive les GPIO
// ******************
GestionAffichage::~GestionAffichage() {
	eteindre();
}

