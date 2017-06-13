/*
 * GestionBH1750.h
 *
 *  Created on: 15 may 2017
 *      Author: totof
 * Controle un module BH1750
 */

#ifndef _GESTION_BH1750_H_
#define _GESTION_BH1750_H_

namespace std {
  
enum Adresse {
	ADDRESS_AD0_LOW = 0x23,
	ADDRESS_AD0_HIGH = 0x5C
};

enum ModeState {
	// No active state
	BH1750_POWER_DOWN = 0x00,
	// Wating for measurment command
	BH1750_POWER_ON = 0x01,
	// Reset data register value - not accepted in POWER_DOWN mode
	BH1750_RESET = 0x07
};

enum ModeMesure {
	// Start measurement at 1lx resolution. Measurement time is approx 120ms.
	BH1750_CONTINUOUS_HIGH_RES_MODE = 0x10,
	// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
	BH1750_CONTINUOUS_HIGH_RES_MODE_2 = 0x11,
	// Start measurement at 4lx resolution. Measurement time is approx 16ms.
	BH1750_CONTINUOUS_LOW_RES_MODE = 0x13,
	// Start measurement at 1lx resolution. Measurement time is approx 120ms.
	// Device is automatically set to Power Down after measurement.
	BH1750_ONE_TIME_HIGH_RES_MODE = 0x20,
	// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
	// Device is automatically set to Power Down after measurement.
	BH1750_ONE_TIME_HIGH_RES_MODE_2 = 0x21,
	// Start measurement at 1lx resolution. Measurement time is approx 120ms.
	// Device is automatically set to Power Down after measurement.
	BH1750_ONE_TIME_LOW_RES_MODE = 0x23
};

class GestionBH1750 {
    public:
		GestionBH1750(Adresse);
		
		void setState(ModeState);
		float readMinResolutionLightLevel(ModeMesure);	
		float readLightLevel(ModeMesure);
		float readDoubleResolutionLightLevel(ModeMesure);	
		float readMaxResolutionLightLevel(ModeMesure);	
		
		virtual ~GestionBH1750();

    private:
		union i2cData{
			unsigned short uSData;
			unsigned char uCData[2];
		};	
		Adresse adresse;
};

}

#endif /* _GESTION_BH1750_H_ */
