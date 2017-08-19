/*
 * GestionAffichage.h
 *
 *  Created on: 31 juillet 2017
 *      Author: totof
 * Affichage de valeurs sur 4 afficheurs HP5082-7300
 */

#ifndef GESTIONAFFICHAGE_H_
#define GESTIONAFFICHAGE_H_

#include "GestionHP50827300.h"

class GestionAffichage {
public:
	GestionAffichage(uint8_t, uint8_t);
	
	void eteindre(void);
	bool affiche(float, int);

	virtual ~GestionAffichage();

private:
	GestionHP50827300 afficheur4;
	GestionHP50827300 afficheur3;
	GestionHP50827300 afficheur2;
	GestionHP50827300 afficheur1;
};

#endif /* GESTIONAFFICHAGE_H_ */
