/*
 * GestionADXL362.h
 *
 * Created on 22/08/2020
 * Author Totof
 *
 */
 
#ifndef GESTIONADXL362_H_
#define GESTIONADXL362_H_

#include <stdint.h>

#define ERROR -1

class GestionADXL362 {
	public:
		enum LinkLoop {
			defaultMode   = 0b00000000,
			linked        = 0b00010000,
			loop          = 0b00110000,
			linkLoopMask  = 0b11001111,
			linkLoopError = -1
		};
		enum FifoMode {
			disabled      = 0b00000000,
			oldestSaved   = 0b00000001,
			stream        = 0b00000010,
			triggered     = 0b00000011,
			fifoModeMask  = 0b11111100,
			fifoModeError = -1
		};
		enum Range {
			R2G        = 0b00000000,
			R4G        = 0b01000000,
			R8G        = 0b10000000,
			rangeMask  = 0b00111111,
			rangeError = -1
		};
		enum DataRate {
			DR12p5        = 0b00000000,
			DR25          = 0b00000001,
			DR50          = 0b00000010,
			DR100         = 0b00000011,
			DR200         = 0b00000100,
			DR400         = 0b00000111,
			dataRateMask  = 0b11111000,
			dataRateError = -1
		};
		enum Noise {
			normal        = 0b00000000,
			lowNoise      = 0b00010000,
			ultraLowNoise = 0b00100000,
			noiseMask     = 0b11001111,
			noiseError    = -1
		};
		enum Measure {
			standby      = 0b00000000,
			measurement  = 0b00000010,
			measureMask  = 0b11111100,
			measureError = -1
		};
		
		GestionADXL362(int);
		
		// 0x00
		uint8_t getDevId(void);
		// 0x01
		uint8_t getMicroElectroMechanicalSystemId(void);
		// 0x02
 		uint8_t getPartId(void);
		// 0x03
		uint8_t getRevId(void);
		// 0x00, 0x01, 0x02
		bool isADXL362Device(void);
		// 0x08
		int8_t getXAxis8Msb(void);
		// 0x09
		int8_t getYAxis8Msb(void);
		// 0x0A
		int8_t getZAxis8Msb(void);
		// 0x0B
		uint8_t getStatus(void);
		bool isError(void);
		bool isAwake(void);
		bool isInactif(void);
		bool isActif(void);
		bool isFifoOverrun(void);
		bool isFifoWatermark(void);
		bool isFifoReady(void);
		bool isDataReady(void);
		// 0x0C 0x0D
		uint16_t getFifoEntries(void);
		// 0x0E 0x0F
		int16_t getXAxisData(void);
		float getXAxisG(void);
		// 0x10 0x11
		int16_t getYAxisData(void);
		float getYAxisG(void);
		// 0x12 0x13
		int16_t getZAxisData(void);
		float getZAxisG(void);
		// 0x14 0x15
		uint16_t getTemperatureData(void);
		float getTemperatureCelcius(void);
		// 0x1F
		uint8_t softReset(void);
		// 0x20 0x21
		uint16_t getActivityThreshold(void);
		uint8_t setActivityThreshold(uint16_t);
		// 0x22
		uint8_t getActivityTime(void);
		uint8_t setActivityTime(uint8_t);
		// 0x23 0x24
		uint16_t getInactivityThreshold(void);
		uint8_t setInactivityThreshold(uint16_t);
		// 0x25 0x26	
		uint16_t getInactivityTime(void);
		uint8_t setInactivityTime(uint16_t);
		// 0x27
		uint8_t getActivityInactivity(void);
		uint8_t setActivityInactivity(uint8_t);
		LinkLoop getLinkLoopMode(void);
		uint8_t setLinkLoopMode(LinkLoop);
		bool isInactRef(void);
		uint8_t setInactRef(void);
		uint8_t unSetInactRef(void);
		bool isInactEnable(void);
		uint8_t setInactEnable(void);
		uint8_t unSetInactEnable(void);
		bool isActRef(void);
		uint8_t setActRef(void);
		uint8_t unSetActRef(void);
		bool isActEnable(void);
		uint8_t setActEnable(void);
		uint8_t unSetActEnable(void);
		// 0x28
		uint8_t getFifoControl(void);
		uint8_t setFifoControl(uint8_t);
		bool isAboveHalf(void);
		uint8_t setAboveHalf(void);
		uint8_t unSetAboveHalf(void);
		bool isTemperature(void);
		uint8_t setTemperature(void);
		uint8_t unSetTemperature(void);
		FifoMode getFifoMode(void);
		uint8_t setFifoMode(FifoMode);
		// 0x29 (AH 0x28)
		uint8_t getFifoSamples(void);
		uint8_t setFifoSamples(uint8_t);
		uint16_t getFullFifoSamples(void);
		// 0x2A
		uint8_t getIntMap1(void);
		uint8_t setIntMap1(uint8_t);
		bool isActiveLow1(void);
		uint8_t setActiveLow1(void);
		uint8_t unSetActiveLow1(void);
		bool isAwake1(void);
		uint8_t setAwake1(void);
		uint8_t unSetAwake1(void);
		bool isInactif1(void);
		uint8_t setInactif1(void);
		uint8_t unSetInactif1(void);
		bool isActif1(void);
		uint8_t setActif1(void);
		uint8_t unSetActif1(void);
		bool isFifoOverrun1(void);
		uint8_t setFifoOverrun1(void);
		uint8_t unSetFifoOverrun1(void);
		bool isFifoWatermark1(void);
		uint8_t setFifoWatermark1(void);
		uint8_t unSetFifoWatermark1(void);
		bool isFifoReady1(void);
		uint8_t setFifoReady1(void);
		uint8_t unSetFifoReady1(void);
		bool isDataReady1(void);
		uint8_t setDataReady1(void);
		uint8_t unSetDataReady1(void);
		// 0x2B
		uint8_t getIntMap2(void);
		uint8_t setIntMap2(uint8_t);
		bool isActiveLow2(void);
		uint8_t setActiveLow2(void);
		uint8_t unSetActiveLow2(void);
		bool isAwake2(void);
		uint8_t setAwake2(void);
		uint8_t unSetAwake2(void);
		bool isInactif2(void);
		uint8_t setInactif2(void);
		uint8_t unSetInactif2(void);
		bool isActif2(void);
		uint8_t setActif2(void);
		uint8_t unSetActif2(void);
		bool isFifoOverrun2(void);
		uint8_t setFifoOverrun2(void);
		uint8_t unSetFifoOverrun2(void);
		bool isFifoWatermark2(void);
		uint8_t setFifoWatermark2(void);
		uint8_t unSetFifoWatermark2(void);
		bool isFifoReady2(void);
		uint8_t setFifoReady2(void);
		uint8_t unSetFifoReady2(void);
		bool isDataReady2(void);
		uint8_t setDataReady2(void);
		uint8_t unSetDataReady2(void);
		// 0x2C
		uint8_t getFilterControl(void);
		uint8_t setFilterControl(uint8_t);
		Range getRange(void);
		uint8_t setRange(Range);
		bool isHalfBandWidth(void);
		uint8_t setHalfBandWidth(void);
		uint8_t unSetHalfBandWidth(void);
		bool isExternalSample(void);
		uint8_t setExternalSample(void);
		uint8_t unSetExternalSample(void);
		DataRate getDataRate(void);
		uint8_t setDataRate(DataRate);
		// 0x2D
		uint8_t getPowerControl(void);
		uint8_t setPowerControl(uint8_t);
		bool isExternalClock(void);
		uint8_t setExternalClock(void);
		uint8_t unSetExternalClock(void);
		Noise getNoise(void);
		uint8_t setNoise(Noise);
		bool isWakeUp(void);
		uint8_t setWakeUp(void);
		uint8_t unSetWakeUp(void);
		bool isAutoSleep(void);
		uint8_t setAutoSleep(void);
		uint8_t unSetAutoSleep(void);
		Measure getMeasure(void);
		uint8_t setMeasure(Measure);
		// 0x2E
		bool isSelfTest(void);
		uint8_t setSelfTest(void);
		uint8_t unSetSelfTest(void);
		
		// Fifo
		// char[] getFifoData(uint16_t);
		
		// Sample Init
		void sampleInit1(void);
		void sampleInit2(void);
		void sampleInit3(void);

    void spiStop(void);

		virtual ~GestionADXL362();
		
	private:
		int pinCS;
		char fifoData[513];
		uint8_t genericRead8(uint8_t);
		uint16_t genericRead16(uint8_t);
		uint8_t genericWrite8(uint8_t, uint8_t);
		uint8_t genericWrite16(uint8_t, uint16_t);
};

#endif // GESTIONADXL362_H_
