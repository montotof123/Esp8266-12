/*!
 *   \file    Chiffres7seg.h
 *   \brief   Liste des caractères pour affichage 7 segment
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    25/12/2020
 */
 
#ifndef Chiffres7seg_h
#define Chiffres7seg_h

/**
 *   \brief   Chiffre de 0 à 9
 */ 
uint8_t chiffres []  = {
  0b11000000,
  0b11111001,
  0b10100100,
  0b10110000,
  0b10011001,
  0b10010010,
  0b10000010,
  0b11111000,
  0b10000000,
  0b10010000
};

/**
 *   \brief   Afficheur vide
 */
uint8_t vide = 0b11111111;

/**
 *   \brief   Signe moins
 */
 uint8_t moins = 0b01111111;

/**
 *   \brief   Chiffre de 0 à 9 avec virgule
 */
uint8_t chiffresVirgule []  = {
  0b01000000,
  0b01111001,
  0b00100100,
  0b00110000,
  0b00011001,
  0b00010010,
  0b00000010,
  0b01111000,
  0b00000000,
  0b00010000
};

#endif
