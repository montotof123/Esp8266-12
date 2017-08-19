/*
 * GestionHCSR04.h
 *
 *  Created on: 30/07/2017
 *      Author: totof
 */

#ifndef GESTIONHCSR04_H_
#define GESTIONHCSR04_H_

// Classe de gestion des HC-SR04
class GestionHCSR04 {
public:
	GestionHCSR04(int, int);
	void setTemperature(float);
	float getTemperature(void);
	float getDistance(void);
	virtual ~GestionHCSR04();

private:
	int trigger;
	int echo;
	float temperature = 20.0;
};

#endif /* GESTIONHCSR04_H_ */
