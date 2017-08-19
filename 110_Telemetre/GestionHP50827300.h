/*
 * GestionHP50827300.h
 *
 *  Created on: 16 juillet 2017
 *      Author: totof
 * Controle de l'afficheur HP 5082-7300
 */

#ifndef GESTIONHP50827300_H_
#define GESTIONHP50827300_H_

#include <stdint.h>
#include "MCP23S17.h"

#define NOT_A_NUMBER -1

enum Values{
	ZERO = 0,
	UN = 1,
	DEUX = 2,
	TROIS = 3,
	QUATRE = 4,
	CINQ = 5,
	SIX = 6,
	SEPT = 7,
	HUIT = 8,
	NEUF = 9,
	ZERO_POINT = 10,
	UN_POINT = 11,
	DEUX_POINT = 12,
	TROIS_POINT = 13,
	QUATRE_POINT = 14,
	CINQ_POINT = 15,
	SIX_POINT = 16,
	SEPT_POINT = 17,
	HUIT_POINT = 18,
	NEUF_POINT = 19,
	TEST = 20,
	BLANK = 21,
	MINUS = 22,
	MINUS_POINT = 23
};

// Classe de gestion du HP 5082-7300
class GestionHP50827300 {
public:
	GestionHP50827300();
	GestionHP50827300(uint8_t, uint8_t, uint8_t);
	void init(uint8_t, uint8_t, uint8_t);
	bool setValueWithoutPoint(uint8_t);
	bool setValueWithPoint(uint8_t);
	void setTest(void);
	void setBlank(void);
	void setMinus(void);
	void setMinusWithPoint(void);
	bool increment(void);
	bool decrement(void);
	bool increment(uint8_t);
	bool decrement(uint8_t);

	virtual ~GestionHP50827300();

private:
	uint8_t PinLatchEnable;
	bool setValue(Values);
	uint8_t valeur;
	bool point;
	MCP iochip;
};

#endif /* GESTIONHP50827300_H_ */
