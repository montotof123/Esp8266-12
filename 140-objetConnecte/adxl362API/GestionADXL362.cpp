/*
 * GestionADXL362.cpp
 *
 * Driver pour l'accéléromètre ADXL362
 *
 * Created on 22/08/2020
 * Author Totof
 *
 */
 
#include "GestionADXL362.h"
#include "GestionADXL362Reg.h"
#include <SPI.h>

// ****************
// Constructeur
// @Param canal SPI
// ****************
GestionADXL362::GestionADXL362(int pPinCS){
	SPI.begin();
	pinCS = pPinCS;
	pinMode(pinCS, OUTPUT);
}

// ***************************************
// Donne le Device ID d'Analog Device (AD)
// @Return Device ID
// ***************************************
uint8_t GestionADXL362::getDevId(void){
	return genericRead8(ADXL362_REG_DEVID_AD);
}

// *************************
// Donne le MEMS du circuit
// @Return MEMS
// *************************
uint8_t GestionADXL362::getMicroElectroMechanicalSystemId(void){
	return genericRead8(ADXL362_REG_DEVID_MST);
}

// ***************
// Donne le PartId
// @Return PartId
// ***************
uint8_t GestionADXL362::getPartId(void){
	return genericRead8(ADXL362_REG_PARTID);
}

// *******************
// Donne le RevisionId
// @Return RevisionId
// *******************
uint8_t GestionADXL362::getRevId(void){
	return genericRead8(ADXL362_REG_REVID);
}

// ********************************
// Indique si c'est bien un ADXL362 
// @Return true si oui false sinon
// ********************************
bool GestionADXL362::isADXL362Device(void){
	
	if(getDevId() != ADXL362_DEVICE_AD) {
		return false;
	}
	if(getMicroElectroMechanicalSystemId() != ADXL362_DEVICE_MST) {
		return false;
	}
	if(getPartId() != ADXL362_PART_ID) {
		return false;
	}
	
	return true;
}

// ********************************
// Donne la valeur 8bit sur l'axe X 
// @Return valeur 8bit sur l'axe X
// ********************************
int8_t GestionADXL362::getXAxis8Msb(void){
	return genericRead8(ADXL362_REG_XDATA);
}

// ********************************
// Donne la valeur 8bit sur l'axe Y 
// @Return valeur 8bit sur l'axe Y
// ********************************
int8_t GestionADXL362::getYAxis8Msb(void){
	return genericRead8(ADXL362_REG_YDATA);
}

// ********************************
// Donne la valeur 8bit sur l'axe Z 
// @Return valeur 8bit sur l'axe Z
// ********************************
int8_t GestionADXL362::getZAxis8Msb(void){
	return genericRead8(ADXL362_REG_ZDATA);
}

// **************************************
// Donne le contenu du registre de status 
// @Return le registre de status 
// **************************************
uint8_t GestionADXL362::getStatus(void){
	return genericRead8(ADXL362_REG_STATUS);
}

// ********************
// Status error 
// @Return status error
// ********************
bool GestionADXL362::isError(void){
	return genericRead8(ADXL362_REG_STATUS) & (uint8_t)ADXL362_STATUS_ERR_USER_REGS;
}

// ********************
// Status awake 
// @Return status awake
// ********************
bool GestionADXL362::isAwake(void){
	return genericRead8(ADXL362_REG_STATUS) & (uint8_t)ADXL362_STATUS_AWAKE;
}

// **********************
// Status inactif 
// @Return status inactif
// **********************
bool GestionADXL362::isInactif(void){
	return genericRead8(ADXL362_REG_STATUS) & (uint8_t)ADXL362_STATUS_INACT;
}

// ********************
// Status actif 
// @Return status actif
// ********************
bool GestionADXL362::isActif(void){
	return genericRead8(ADXL362_REG_STATUS) & (uint8_t)ADXL362_STATUS_ACT;
}

// ***************************
// Status fifo overrun 
// @Return status fifo overrun 
// ***************************
bool GestionADXL362::isFifoOverrun(void){
	return genericRead8(ADXL362_REG_STATUS) & (uint8_t)ADXL362_STATUS_FIFO_OVERRUN;
}

// *****************************
// Status fifo watermark  
// @Return status fifo watermark
// *****************************
bool GestionADXL362::isFifoWatermark(void){
	return genericRead8(ADXL362_REG_STATUS) & (uint8_t)ADXL362_STATUS_FIFO_WATERMARK;
}

// *************************
// Status fifo ready 
// @Return status fifo ready 
// *************************
bool GestionADXL362::isFifoReady(void){
	return genericRead8(ADXL362_REG_STATUS) & (uint8_t)ADXL362_STATUS_FIFO_RDY;
}

// *************************
// Status data ready 
// @Return status data ready
// *************************
bool GestionADXL362::isDataReady(void){
	return genericRead8(ADXL362_REG_STATUS) & (uint8_t)ADXL362_STATUS_DATA_RDY;
}

// **************************************
// Donne le nombre de mesure dans le Fifo 
// @Return nombre de mesure dans le Fifo 
// **************************************
uint16_t GestionADXL362::getFifoEntries(void){
	return genericRead16(ADXL362_REG_FIFO_L);
}

// ******************
// Mesure sur l'axe X 
// @Return axe X
// ******************
int16_t GestionADXL362::getXAxisData(void){
	return genericRead16(ADXL362_REG_XDATA_L);
}

// ******************
// Mesure sur l'axe X 
// @Return axe X
// ******************
float GestionADXL362::getXAxisG(void){
	float selectrange = 0.0F;
	switch(getRange()) {
		case R2G: selectrange = 2.0F; break;
		case R4G: selectrange = 4.0F; break;
		case R8G: selectrange = 8.0F; break;
	}
	return (float)getXAxisData() / (1000.0F / (selectrange / 2.0F));
}

// ******************
// Mesure sur l'axe Y 
// @Return axe Y
// ******************
int16_t GestionADXL362::getYAxisData(void){
	return genericRead16(ADXL362_REG_YDATA_L);
}

// ******************
// Mesure sur l'axe Y 
// @Return axe Y
// ******************
float GestionADXL362::getYAxisG(void){
	float selectrange = 0.0F;
	switch(getRange()) {
		case R2G: selectrange = 2.0F; break;
		case R4G: selectrange = 4.0F; break;
		case R8G: selectrange = 8.0F; break;
	}
	return (float)getYAxisData() / (1000.0F / (selectrange / 2.0F));
}

// ******************
// Mesure sur l'axe Z 
// @Return axe Z
// ******************
int16_t GestionADXL362::getZAxisData(void){
	return genericRead16(ADXL362_REG_ZDATA_L);
}

// ******************
// Mesure sur l'axe Z 
// @Return axe Z
// ******************
float GestionADXL362::getZAxisG(void){
	float selectrange = 0.0F;
	switch(getRange()) {
		case R2G: selectrange = 2.0F; break;
		case R4G: selectrange = 4.0F; break;
		case R8G: selectrange = 8.0F; break;
	}
	return (float)getZAxisData() / (1000.0F / (selectrange / 2.0F));
}

// ******************************************
// Mesure de la temperature 
// Attention: ce n'est pas la température
//            ambiante, mais celle du circuit 
// @Return temperature
// ******************************************
uint16_t GestionADXL362::getTemperatureData(void){
	return genericRead16(ADXL362_REG_TEMP_L);
}

// ******************************************
// Mesure de la temperature en degré celcius
// Attention: ce n'est pas la température
//            ambiante, mais celle du circuit 
// @Return temperature
// ******************************************
float GestionADXL362::getTemperatureCelcius(void){
	return (float)getTemperatureData() * 0.065F;
}

// **********
// Soft Reset 
// **********
uint8_t GestionADXL362::softReset(void){
	return genericWrite8(ADXL362_REG_SOFT_RESET, ADXL362_RESET_KEY);
}

// *********************************************************
// Donne la valeur d'activite pour la detection de mouvement 
// @Return valeur d'activite
// *********************************************************
uint16_t GestionADXL362::getActivityThreshold(void){
	return genericRead16(ADXL362_REG_THRESH_ACT_L);
}

// **************************************************************
// Positionne la valeur d'activite pour la detection de mouvement 
// @Return le nombre d'octet ecrit
// **************************************************************
uint8_t GestionADXL362::setActivityThreshold(uint16_t pValue){
	return genericWrite16(ADXL362_REG_THRESH_ACT_L, pValue);
}

// ********************************************************
// Donne le temps d'activite pour la detection de mouvement 
// @Return temps d'activite
// ********************************************************
uint8_t GestionADXL362::getActivityTime(void){
	return genericRead8(ADXL362_REG_TIME_ACT);
}

// *************************************************************
// Positionne le temps d'activite pour la detection de mouvement 
// @Return le nombre d'octet ecrit
// *************************************************************
uint8_t GestionADXL362::setActivityTime(uint8_t pValue){
	return genericWrite8(ADXL362_REG_TIME_ACT, pValue);
}

// ***********************************************************
// Donne la valeur d'inactivite pour la detection de mouvement 
// @Return valeur d'inactivite
// ***********************************************************
uint16_t GestionADXL362::getInactivityThreshold(void){
	return genericRead16(ADXL362_REG_THRESH_INACT_L);
}

// ****************************************************************
// Positionne la valeur d'inactivite pour la detection de mouvement 
// @Return le nombre d'octet ecrit
// ****************************************************************
uint8_t GestionADXL362::setInactivityThreshold(uint16_t pValue){
	return genericWrite16(ADXL362_REG_THRESH_INACT_L, pValue);
}

// **********************************************************
// Donne le temps d'inactivite pour la detection de mouvement 
// @Return temps d'inactivite
// **********************************************************
uint16_t GestionADXL362::getInactivityTime(void){
	return genericRead16(ADXL362_REG_TIME_INACT_L);
}

// ***************************************************************
// Positionne le temps d'inactivite pour la detection de mouvement 
// @Return le nombre d'octet ecrit
// ***************************************************************
uint8_t GestionADXL362::setInactivityTime(uint16_t pValue){
	return genericWrite16(ADXL362_REG_TIME_INACT_L, pValue);
}

// ********************************************
// Donne l'état du registre activité/inactivité
// @Return le registre activité/inactivité
// ********************************************
uint8_t GestionADXL362::getActivityInactivity(void){
	return genericRead8(ADXL362_REG_ACT_INACT_CTL);
}

// *************************************************
// Positionne l'état du registre activité/inactivité
// @Return le nombre d'octet ecrit
// *************************************************
uint8_t GestionADXL362::setActivityInactivity(uint8_t pValue){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, pValue);
}

// *********************************
// Donne le mode de fonctionnement
// @Return le mode de fonctionnement
// *********************************
GestionADXL362::LinkLoop GestionADXL362::getLinkLoopMode(void){
	switch(genericRead8(ADXL362_REG_ACT_INACT_CTL) & 0b00110000) {
		case 0b00000000: return defaultMode; break;
		case 0b00010000: return linked;      break;
		case 0b00100000: return defaultMode; break;
		case 0b00110000: return loop;        break;
	}
	return linkLoopError;
}

// ************************************
// Positionne le mode de fonctionnement
// @Param Le mode de fonctionnement
// @Return le nombre d'octet ecrit
// ************************************
uint8_t GestionADXL362::setLinkLoopMode(GestionADXL362::LinkLoop pValue){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, (genericRead8(ADXL362_REG_ACT_INACT_CTL) & linkLoopMask) | pValue);
}

// *******************************************
// Détecte l'inactivité en absolue ou en delta 
// @Return mode de détection de l'inactivité
// @Values 1 delta, 0 absolue
// *******************************************
bool GestionADXL362::isInactRef(void){
	return genericRead8(ADXL362_REG_ACT_INACT_CTL) & (uint8_t)ADXL362_ACT_INACT_CTL_INACT_REF;
}

// ************************************************
// Positionne la détection de l'inactivité en delta 
// @Return le nombre d'octet ecrit
// ************************************************
uint8_t GestionADXL362::setInactRef(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL) | ADXL362_ACT_INACT_CTL_INACT_REF);
}

// **************************************************
// Positionne la détection de l'inactivité en absolue 
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::unSetInactRef(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL) & ~ADXL362_ACT_INACT_CTL_INACT_REF);
}

// ***********************************************
// Demande si la détection d'inactivité est active
// @Return true si oui, false si non
// ***********************************************
bool GestionADXL362::isInactEnable(void){
	return genericRead8(ADXL362_REG_ACT_INACT_CTL) & (uint8_t)ADXL362_ACT_INACT_CTL_INACT_EN;
}

// ********************************
// Active la détection d'inactivité 
// @Return le nombre d'octet ecrit
// ********************************
uint8_t GestionADXL362::setInactEnable(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL) | ADXL362_ACT_INACT_CTL_INACT_EN);
}

// **********************************
// Déactive la détection d'inactivité 
// @Return le nombre d'octet ecrit
// **********************************
uint8_t GestionADXL362::unSetInactEnable(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL) & ~ADXL362_ACT_INACT_CTL_INACT_EN);
}

// *****************************************
// Détecte l'activité en absolue ou en delta 
// @Return 1 delta, 0 absolue 
// *****************************************
bool GestionADXL362::isActRef(void){
	return genericRead8(ADXL362_REG_ACT_INACT_CTL) & (uint8_t)ADXL362_ACT_INACT_CTL_ACT_REF;
}

// *******************************************
// Positionne la détection d'activité en delta 
// @Return le nombre d'octet ecrit
// *******************************************
uint8_t GestionADXL362::setActRef(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL) | ADXL362_ACT_INACT_CTL_ACT_REF);
}

// *********************************************
// Positionne la détection d'activité en absolue 
// @Return le nombre d'octet ecrit
// *********************************************
uint8_t GestionADXL362::unSetActRef(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL) & ~ADXL362_ACT_INACT_CTL_ACT_REF);
}

// *********************************************
// Demande si la détection d'activité est active
// @Return true si oui, false si non 
// *********************************************
bool GestionADXL362::isActEnable(void){
	return genericRead8(ADXL362_REG_ACT_INACT_CTL) & (uint8_t)ADXL362_ACT_INACT_CTL_ACT_EN;
}

// *******************************
// Active la détection d'activité 
// @Return le nombre d'octet ecrit
// *******************************
uint8_t GestionADXL362::setActEnable(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL) | ADXL362_ACT_INACT_CTL_ACT_EN);
}

// ********************************
// Déactive la détection d'activité 
// @Return le nombre d'octet ecrit
// ********************************
uint8_t GestionADXL362::unSetActEnable(void){
	return genericWrite8(ADXL362_REG_ACT_INACT_CTL, genericRead8(ADXL362_REG_ACT_INACT_CTL) & ~ADXL362_ACT_INACT_CTL_ACT_EN);
}

// **************************************************
// Donne le contenu du registre de control des FIFO 
// @Return le contenu du registre de control des FIFO
// **************************************************
uint8_t GestionADXL362::getFifoControl(void){
	return genericRead8(ADXL362_REG_FIFO_CTL);
}

// *****************************************************
// Positionne le contenu du registre de control des FIFO 
// @Return le nombre d'octet ecrit
// *****************************************************
uint8_t GestionADXL362::setFifoControl(uint8_t pValue){
	return genericWrite8(ADXL362_REG_FIFO_CTL, pValue);
}

// **********************************************************************************************
// 9eme bit du nombre de mesures du FIFO
// @Return le 9eme bit indiquant qu'il y a au moins 256 mesures dans le FIFO sur les 512 posibles
// **********************************************************************************************
bool GestionADXL362::isAboveHalf(void){
	return genericRead8(ADXL362_REG_FIFO_CTL) & (uint8_t)ADXL362_FIFO_CTL_AH;
}

// *****************************************************************
// Positionne le 9eme bit du pointeur FIFO à 1 (donc au delà de 256)
// @Return le nombre d'octet ecrit
// *****************************************************************
uint8_t GestionADXL362::setAboveHalf(void){
	return genericWrite8(ADXL362_REG_FIFO_CTL, genericRead8(ADXL362_REG_FIFO_CTL) | ADXL362_FIFO_CTL_AH);
}

// ************************************************************
// Positionne le 9eme bit du pointeur FIFO à 0 (donc avant 256) 
// @Return le nombre d'octet ecrit
// ************************************************************
uint8_t GestionADXL362::unSetAboveHalf(void){
	return genericWrite8(ADXL362_REG_FIFO_CTL, genericRead8(ADXL362_REG_FIFO_CTL) & ~ADXL362_FIFO_CTL_AH);
}

// *************************************************
// Demande si la temperature est stocké dans le FIFO 
// @Return true si oui, false si non
// *************************************************
bool GestionADXL362::isTemperature(void){
	return genericRead8(ADXL362_REG_FIFO_CTL) & (uint8_t)ADXL362_FIFO_CTL_FIFO_TEMP;
}

// ***************************************
// La temperature sera stocké dans le FIFO 
// @Return le nombre d'octet ecrit
// ***************************************
uint8_t GestionADXL362::setTemperature(void){
	return genericWrite8(ADXL362_REG_FIFO_CTL, genericRead8(ADXL362_REG_FIFO_CTL) | ADXL362_FIFO_CTL_FIFO_TEMP);
}

// **********************************************
// La temperature ne sera pas stocké dans le FIFO 
// @Return le nombre d'octet ecrit
// **********************************************
uint8_t GestionADXL362::unSetTemperature(void){
	return genericWrite8(ADXL362_REG_FIFO_CTL, genericRead8(ADXL362_REG_FIFO_CTL) & ~ADXL362_FIFO_CTL_FIFO_TEMP);
}

// *****************************************
// Donne le mode de fonctionnement du FIFO 
// @Return le mode de fonctionnement du FIFO 
// *****************************************
GestionADXL362::FifoMode GestionADXL362::getFifoMode(void){
		switch(genericRead8(ADXL362_REG_FIFO_CTL) & 0b00000011) {
		case 0b00000000: return disabled   ; break;
		case 0b00000001: return oldestSaved; break;
		case 0b00000010: return stream     ; break;
		case 0b00000011: return triggered  ; break;
	}
	return fifoModeError;
}

// ********************************************
// Positionne le mode de fonctionnement du FIFO 
// @Return le nombre d'octet ecrit
// ********************************************
uint8_t GestionADXL362::setFifoMode(GestionADXL362::FifoMode pValue){
	return genericWrite8(ADXL362_REG_FIFO_CTL, (genericRead8(ADXL362_REG_FIFO_CTL) & fifoModeMask) | pValue);
}

// *******************************************************************
// Donne les 8 premiers bits du nombre de mesures voulue dans le FIFO
// @Return les 8 premiers bits du nombre de mesure voulue dans le FIFO
// *******************************************************************
uint8_t GestionADXL362::getFifoSamples(void){
	return genericRead8(ADXL362_REG_FIFO_SAMPLES);
}

// **********************************************************************
// Positionne les 8 premiers bits du nombre de mesure voulue dans le FIFO
// @Return le nombre d'octet ecrit
// **********************************************************************
uint8_t GestionADXL362::setFifoSamples(uint8_t pValue){
	return genericWrite8(ADXL362_REG_FIFO_SAMPLES, pValue);
}

// *****************************************************
// Donne le nombre de mesures totale voulue dans le FIFO
// @Return le nombre de mesure dans le FIFO
// *****************************************************
uint16_t GestionADXL362::getFullFifoSamples(void){
	return isAboveHalf() * 256 + genericRead8(ADXL362_REG_FIFO_SAMPLES);
}


// ***********************************************
// Donne le registre de mapping d'interruption 1 
// @Return le registre de mapping d'interruption 1 
// ***********************************************
uint8_t GestionADXL362::getIntMap1(void){
	return genericRead8(ADXL362_REG_INTMAP1);
}

// **************************************************
// Positionne le registre de mapping d'interruption 1 
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::setIntMap1(uint8_t pValue){
	return genericWrite8(ADXL362_REG_INTMAP1, pValue);
}

// ***********************************************
// Demande si l'interruption est active niveau bas
// @Return true si oui, false sinon
// ***********************************************
bool GestionADXL362::isActiveLow1(void){
	return genericRead8(ADXL362_REG_INTMAP1) & (uint8_t)ADXL362_INTMAP1_INT_LOW;
}

// *******************************************
// Positionne l'interruption active niveau bas 
// @Return le nombre d'octet ecrit
// *******************************************
uint8_t GestionADXL362::setActiveLow1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) | ADXL362_INTMAP1_INT_LOW);
}

// ********************************************
// Positionne l'interruption active niveau haut 
// @Return le nombre d'octet ecrit
// ********************************************
uint8_t GestionADXL362::unSetActiveLow1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) & ~ADXL362_INTMAP1_INT_LOW);
}

// ***********************************************************
// Demande si il y a interruption quand le circuit se reveille
// @Return true si oui, false si non
// ***********************************************************
bool GestionADXL362::isAwake1(void){
	return genericRead8(ADXL362_REG_INTMAP1) & (uint8_t)ADXL362_INTMAP1_AWAKE;
}

// *****************************************
// interruption quand le circuit se reveille
// @Return le nombre d'octet ecrit
// *****************************************
uint8_t GestionADXL362::setAwake1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) | ADXL362_INTMAP1_AWAKE);
}

// ***********************************************
// Pas d'interruption quand le circuit se reveille
// @Return le nombre d'octet ecrit
// ***********************************************
uint8_t GestionADXL362::unSetAwake1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) & ~ADXL362_INTMAP1_AWAKE);
}

// *************************************************************
// Demande si il y a interruption quand l'inactivité est détecté 
// @Return true si oui, false si non
// *************************************************************
bool GestionADXL362::isInactif1(void){
	return genericRead8(ADXL362_REG_INTMAP1) & (uint8_t)ADXL362_INTMAP1_INACT;
}

// **************************************************
// @Param interruption quand l'inactivité est détecté 
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::setInactif1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) | ADXL362_INTMAP1_INACT);
}

// ********************************************************
// @Param pas d'interruption quand l'inactivité est détecté 
// @Return le nombre d'octet ecrit
// ********************************************************
uint8_t GestionADXL362::unSetInactif1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) & ~ADXL362_INTMAP1_INACT);
}

// ***********************************************************
// Demande si il y a interruption quand l'activité est détecté 
// @Return true si oui, false si non
// ***********************************************************
bool GestionADXL362::isActif1(void){
	return genericRead8(ADXL362_REG_INTMAP1) & (uint8_t)ADXL362_INTMAP1_ACT;
}

// *****************************************
// Interruption quand l'activité est détecté 
// @Return le nombre d'octet ecrit
// *****************************************
uint8_t GestionADXL362::setActif1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) | ADXL362_INTMAP1_ACT);
}

// ***********************************************
// Pas d'interruption quand l'activité est détecté 
// @Return le nombre d'octet ecrit
// ***********************************************
uint8_t GestionADXL362::unSetActif1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) & ~ADXL362_INTMAP1_ACT);
}

// ***********************************************************************************************
// Demande si il y a interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return true si oui, false si non
// ***********************************************************************************************
bool GestionADXL362::isFifoOverrun1(void){
	return genericRead8(ADXL362_REG_INTMAP1) & (uint8_t)ADXL362_INTMAP1_FIFO_OVERRUN;
}

// *****************************************************************************
// Interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return le nombre d'octet ecrit
// *****************************************************************************
uint8_t GestionADXL362::setFifoOverrun1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) | ADXL362_INTMAP1_FIFO_OVERRUN);
}

// ***********************************************************************************
// Pas d'interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return le nombre d'octet ecrit
// ***********************************************************************************
uint8_t GestionADXL362::unSetFifoOverrun1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) & ~ADXL362_INTMAP1_FIFO_OVERRUN);
}

// *********************************************************************************************
// Demande si il y a interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return true si oui, false si non
// *********************************************************************************************
bool GestionADXL362::isFifoWatermark1(void){
	return genericRead8(ADXL362_REG_INTMAP1) & (uint8_t)ADXL362_INTMAP1_FIFO_WATERMARK;
}

// ***************************************************************************
// Interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return le nombre d'octet ecrit
// ***************************************************************************
uint8_t GestionADXL362::setFifoWatermark1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) | ADXL362_INTMAP1_FIFO_WATERMARK);
}

// *********************************************************************************
// Pas d'interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return le nombre d'octet ecrit
// *********************************************************************************
uint8_t GestionADXL362::unSetFifoWatermark1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) & ~ADXL362_INTMAP1_FIFO_WATERMARK);
}

// ******************************************************************
// Demande si il y a interruption si au moins une mesure dans le FIFO
// @Return true si oui, false si non
// ******************************************************************
bool GestionADXL362::isFifoReady1(void){
	return genericRead8(ADXL362_REG_INTMAP1) & (uint8_t)ADXL362_INTMAP1_FIFO_READY;
}

// ************************************************
// Interruption si au moins une mesure dans le FIFO
// @Return le nombre d'octet ecrit
// ************************************************
uint8_t GestionADXL362::setFifoReady1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) | ADXL362_INTMAP1_FIFO_READY);
}

// ******************************************************
// Pas d'interruption si au moins une mesure dans le FIFO
// @Return le nombre d'octet ecrit
// ******************************************************
uint8_t GestionADXL362::unSetFifoReady1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) & ~ADXL362_INTMAP1_FIFO_READY);
}

// ************************************************************************
// Demande si il y a interruption si une mesure est disponible à la lecture
// @Return true si oui, false si non
// ************************************************************************
bool GestionADXL362::isDataReady1(void){
	return genericRead8(ADXL362_REG_INTMAP1) & (uint8_t)ADXL362_INTMAP1_DATA_READY;
}

// ******************************************************
// Interruption si une mesure est disponible à la lecture
// @Return le nombre d'octet ecrit
// ******************************************************
uint8_t GestionADXL362::setDataReady1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) | ADXL362_INTMAP1_DATA_READY);
}

// ************************************************************
// Pas d'interruption si une mesure est disponible à la lecture 
// @Return le nombre d'octet ecrit
// ************************************************************
uint8_t GestionADXL362::unSetDataReady1(void){
	return genericWrite8(ADXL362_REG_INTMAP1, genericRead8(ADXL362_REG_INTMAP1) & ~ADXL362_INTMAP1_DATA_READY);
}

// ***********************************************
// Donne le registre de mapping d'interruption 2 
// @Return le registre de mapping d'interruption 2 
// ***********************************************
uint8_t GestionADXL362::getIntMap2(void){
	return genericRead8(ADXL362_REG_INTMAP2);
}

// **************************************************
// Positionne le registre de mapping d'interruption 2 
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::setIntMap2(uint8_t pValue){
	return genericWrite8(ADXL362_REG_INTMAP2, pValue);
}

// ***********************************************
// Demande si l'interruption est active niveau bas
// @Return true si oui, false sinon
// ***********************************************
bool GestionADXL362::isActiveLow2(void){
	return genericRead8(ADXL362_REG_INTMAP2) & (uint8_t)ADXL362_INTMAP2_INT_LOW;
}

// *******************************************
// Positionne l'interruption active niveau bas 
// @Return le nombre d'octet ecrit
// *******************************************
uint8_t GestionADXL362::setActiveLow2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) | ADXL362_INTMAP2_INT_LOW);
}

// ********************************************
// Positionne l'interruption active niveau haut 
// @Return le nombre d'octet ecrit
// ********************************************
uint8_t GestionADXL362::unSetActiveLow2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) & ~ADXL362_INTMAP2_INT_LOW);
}

// ***********************************************************
// Demande si il y a interruption quand le circuit se reveille
// @Return true si oui, false si non
// ***********************************************************
bool GestionADXL362::isAwake2(void){
	return genericRead8(ADXL362_REG_INTMAP2) & (uint8_t)ADXL362_INTMAP2_AWAKE;
}

// *****************************************
// interruption quand le circuit se reveille
// @Return le nombre d'octet ecrit
// *****************************************
uint8_t GestionADXL362::setAwake2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) | ADXL362_INTMAP2_AWAKE);
}

// ***********************************************
// Pas d'interruption quand le circuit se reveille
// @Return le nombre d'octet ecrit
// ***********************************************
uint8_t GestionADXL362::unSetAwake2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) & ~ADXL362_INTMAP2_AWAKE);
}

// **************************************************
// @Param interruption quand l'inactivité est détecté 
// @Return le nombre d'octet ecrit
// **************************************************
bool GestionADXL362::isInactif2(void){
	return genericRead8(ADXL362_REG_INTMAP2) & (uint8_t)ADXL362_INTMAP2_INACT;
}

// **************************************************
// @Param interruption quand l'inactivité est détecté 
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::setInactif2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) | ADXL362_INTMAP2_INACT);
}

// ********************************************************
// @Param pas d'interruption quand l'inactivité est détecté 
// @Return le nombre d'octet ecrit
// ********************************************************
uint8_t GestionADXL362::unSetInactif2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) & ~ADXL362_INTMAP2_INACT);
}

// ***********************************************************
// Demande si il y a interruption quand l'activité est détecté 
// @Return true si oui, false si non
// ***********************************************************
bool GestionADXL362::isActif2(void){
	return genericRead8(ADXL362_REG_INTMAP2) & (uint8_t)ADXL362_INTMAP2_ACT;
}

// *****************************************
// Interruption quand l'activité est détecté 
// @Return le nombre d'octet ecrit
// *****************************************
uint8_t GestionADXL362::setActif2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) | ADXL362_INTMAP2_ACT);
}

// ***********************************************
// Pas d'interruption quand l'activité est détecté 
// @Return le nombre d'octet ecrit
// ***********************************************
uint8_t GestionADXL362::unSetActif2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) & ~ADXL362_INTMAP2_ACT);
}

// ***********************************************************************************************
// Demande si il y a interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return true si oui, false si non
// ***********************************************************************************************
bool GestionADXL362::isFifoOverrun2(void){
	return genericRead8(ADXL362_REG_INTMAP2) & (uint8_t)ADXL362_INTMAP2_FIFO_OVERRUN;
}

// *****************************************************************************
// Interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return le nombre d'octet ecrit
// *****************************************************************************
uint8_t GestionADXL362::setFifoOverrun2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) | ADXL362_INTMAP2_FIFO_OVERRUN);
}

// ***********************************************************************************
// Pas d'interruption lors d'un écrasement de mesures dans le FIFO sans les avoir lues
// @Return le nombre d'octet ecrit
// ***********************************************************************************
uint8_t GestionADXL362::unSetFifoOverrun2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) & ~ADXL362_INTMAP2_FIFO_OVERRUN);
}

// *********************************************************************************************
// Demande si il y a interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return true si oui, false si non
// *********************************************************************************************
bool GestionADXL362::isFifoWatermark2(void){
	return genericRead8(ADXL362_REG_INTMAP2) & (uint8_t)ADXL362_INTMAP2_FIFO_WATERMARK;
}

// ***************************************************************************
// Interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return le nombre d'octet ecrit
// ***************************************************************************
uint8_t GestionADXL362::setFifoWatermark2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) | ADXL362_INTMAP2_FIFO_WATERMARK);
}

// *********************************************************************************
// Pas d'interruption lors du dépassement du nombre de mesures désirées dans le FIFO
// @Return le nombre d'octet ecrit
// *********************************************************************************
uint8_t GestionADXL362::unSetFifoWatermark2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) & ~ADXL362_INTMAP2_FIFO_WATERMARK);
}

// ******************************************************************
// Demande si il y a interruption si au moins une mesure dans le FIFO
// @Return true si oui, false si non
// ******************************************************************
bool GestionADXL362::isFifoReady2(void){
	return genericRead8(ADXL362_REG_INTMAP2) & (uint8_t)ADXL362_INTMAP2_FIFO_READY;
}

// ************************************************
// Interruption si au moins une mesure dans le FIFO
// @Return le nombre d'octet ecrit
// ************************************************
uint8_t GestionADXL362::setFifoReady2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) | ADXL362_INTMAP2_FIFO_READY);
}

// ******************************************************
// Pas d'interruption si au moins une mesure dans le FIFO
// @Return le nombre d'octet ecrit
// ******************************************************
uint8_t GestionADXL362::unSetFifoReady2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) & ~ADXL362_INTMAP2_FIFO_READY);
}

// ************************************************************************
// Demande si il y a interruption si une mesure est disponible à la lecture
// @Return true si oui, false si non
// ************************************************************************
bool GestionADXL362::isDataReady2(void){
	return genericRead8(ADXL362_REG_INTMAP2) & (uint8_t)ADXL362_INTMAP2_DATA_READY;
}

// ******************************************************
// Interruption si une mesure est disponible à la lecture
// @Return le nombre d'octet ecrit
// ******************************************************
uint8_t GestionADXL362::setDataReady2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) | ADXL362_INTMAP2_DATA_READY);
}

// ************************************************************
// Pas d'interruption si une mesure est disponible à la lecture 
// @Return le nombre d'octet ecrit
// ************************************************************
uint8_t GestionADXL362::unSetDataReady2(void){
	return genericWrite8(ADXL362_REG_INTMAP2, genericRead8(ADXL362_REG_INTMAP2) & ~ADXL362_INTMAP2_DATA_READY);
}

// *************************************
// Donne le registre de filter control
// @Return le registre de filter control
// *************************************
uint8_t GestionADXL362::getFilterControl(void){
	return genericRead8(ADXL362_REG_FILTER_CTL);
}

// ****************************************
// Positionne le registre de filter control
// @Return le nombre d'octet ecrit
// ****************************************
uint8_t GestionADXL362::setFilterControl(uint8_t pValue){
	return genericWrite8(ADXL362_REG_FILTER_CTL, pValue);
}

// *****************
// Donne l'échelle
// @Return l'échelle
// *****************
GestionADXL362::Range GestionADXL362::getRange(void){
	switch(genericRead8(ADXL362_REG_FILTER_CTL) & 0b11000000) {
		case 0b00000000: return R2G; break;
		case 0b01000000: return R4G; break;
		case 0b10000000: 
		case 0b11000000: return R8G; break;
	}
	return rangeError;
}

// *************************
// Positionne l'échelle 
// @Return le nombre d'octet ecrit
// *************************
uint8_t GestionADXL362::setRange(GestionADXL362::Range pValue){
	return genericWrite8(ADXL362_REG_FILTER_CTL, (genericRead8(ADXL362_REG_FILTER_CTL) & rangeMask) | pValue);
}

// **********************************
// Demande si le filtre est postionné
// @Return true si oui, false si non
// **********************************
bool GestionADXL362::isHalfBandWidth(void){
	return genericRead8(ADXL362_REG_FILTER_CTL) & (uint8_t)ADXL362_FILTER_CTL_HALF_BW;
}

// *********************************
// Positionne le filtre antialiasing
// @Return le nombre d'octet ecrit
// *********************************
uint8_t GestionADXL362::setHalfBandWidth(void){
	return genericWrite8(ADXL362_REG_FILTER_CTL, genericRead8(ADXL362_REG_FILTER_CTL) | ADXL362_FILTER_CTL_HALF_BW);
}

// *****************************************************
// Positionne le filtre pour une bande passante maximale
// @Return le nombre d'octet ecrit
// *****************************************************
uint8_t GestionADXL362::unSetHalfBandWidth(void){
	return genericWrite8(ADXL362_REG_FILTER_CTL, genericRead8(ADXL362_REG_FILTER_CTL) & ~ADXL362_FILTER_CTL_HALF_BW);
}

// ***************************************************************
// Demande si le signal de synchronisation sur int2 est postionnée 
// @Return true si oui, false si non
// ***************************************************************
bool GestionADXL362::isExternalSample(void){
	return genericRead8(ADXL362_REG_FILTER_CTL) & (uint8_t)ADXL362_FILTER_CTL_EXT_SAMPLE;
}

// ************************************************
// Positionne le signal de synchronisation sur int2
// @Return le nombre d'octet ecrit
// ************************************************
uint8_t GestionADXL362::setExternalSample(void){
	return genericWrite8(ADXL362_REG_FILTER_CTL, genericRead8(ADXL362_REG_FILTER_CTL) | ADXL362_FILTER_CTL_EXT_SAMPLE);
}

// ****************************************************
// Positionne le signal de synchronisation int2 sur off
// @Return le nombre d'octet ecrit
// ****************************************************
uint8_t GestionADXL362::unSetExternalSample(void){
	return genericWrite8(ADXL362_REG_FILTER_CTL, genericRead8(ADXL362_REG_FILTER_CTL) & ~ADXL362_FILTER_CTL_EXT_SAMPLE);
}

// *************************************
// Donne la fréquence d'échantillonage
// @Return la fréquence d'échantillonage
// *************************************
GestionADXL362::DataRate GestionADXL362::getDataRate(void){
	switch(genericRead8(ADXL362_REG_FILTER_CTL) & 0b00000111) {
		case 0b00000000: return DR12p5; break;
		case 0b00000001: return DR25; break;
		case 0b00000010: return DR50; break;
		case 0b00000011: return DR100; break;
		case 0b00000100: return DR200; break;
		case 0b00000101: 
		case 0b00000110: 
		case 0b00000111: return DR400; break;
	}
	return dataRateError;
}

// ****************************************
// Positionne la fréquence d'échantillonage
// @Return le nombre d'octet ecrit
// ****************************************
uint8_t GestionADXL362::setDataRate(GestionADXL362::DataRate pValue){
	return genericWrite8(ADXL362_REG_FILTER_CTL, (genericRead8(ADXL362_REG_FILTER_CTL) & dataRateMask) | pValue);
}

// *********************************
// Donne le registre power control
// @Return le registre power control
// *********************************
uint8_t GestionADXL362::getPowerControl(void){
	return genericRead8(ADXL362_REG_POWER_CTL);
}

// ************************************
// Positionne le registre power control 
// @Return le nombre d'octet ecrit
// ************************************
uint8_t GestionADXL362::setPowerControl(uint8_t pValue){
	return genericWrite8(ADXL362_REG_POWER_CTL, pValue);
}

// *********************************
// Demande si l'horloge est externe
// @Return true si oui, false si non
// *********************************
bool GestionADXL362::isExternalClock(void){
	return genericRead8(ADXL362_REG_POWER_CTL) & (uint8_t)ADXL362_POWER_CTL_EXT_CLK;
}

// *******************************
// Positionne l'horloge externe 
// @Return le nombre d'octet ecrit
// *******************************
uint8_t GestionADXL362::setExternalClock(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL) | ADXL362_POWER_CTL_EXT_CLK);
}

// *******************************
// Positionne l'horloge interne
// @Return le nombre d'octet ecrit
// *******************************
uint8_t GestionADXL362::unSetExternalClock(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL) & ~ADXL362_POWER_CTL_EXT_CLK);
}

// *****************
// Donne le filtre
// @Return le filtre
// *****************
GestionADXL362::Noise GestionADXL362::getNoise(void){
	switch(genericRead8(ADXL362_REG_POWER_CTL) & 0b00110000) {
		case 0b00000000: return normal; break;
		case 0b00010000: return lowNoise; break;
		case 0b00100000: return ultraLowNoise; break;
	}
	return noiseError;
}

// *******************************
// Positionne le filtre
// @Return le nombre d'octet ecrit
// *******************************
uint8_t GestionADXL362::setNoise(GestionADXL362::Noise pValue){
	return genericWrite8(ADXL362_REG_POWER_CTL, (genericRead8(ADXL362_REG_POWER_CTL) & noiseMask) | pValue);
}

// *******************************************************
// Demande si le circuit est en mode consommation minimale
// @Return true si oui, false si non
// *******************************************************
bool GestionADXL362::isWakeUp(void){
	return genericRead8(ADXL362_REG_POWER_CTL) & (uint8_t)ADXL362_POWER_CTL_WAKEUP;
}

// ***************************************************
// Positionne le circuit en mode consommation minimale
// @Return le nombre d'octet ecrit
// ***************************************************
uint8_t GestionADXL362::setWakeUp(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL) | ADXL362_POWER_CTL_WAKEUP);
}

// **************************************************
// Positionne le circuit en mode consommation normale
// @Return le nombre d'octet ecrit
// **************************************************
uint8_t GestionADXL362::unSetWakeUp(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL) & ~ADXL362_POWER_CTL_WAKEUP);
}

// *******************************************************************
// Demande si le circuit passe en économie d'énergie si il est inactif
// @Return true si oui, false si non
// *******************************************************************
bool GestionADXL362::isAutoSleep(void){
	return genericRead8(ADXL362_REG_POWER_CTL) & (uint8_t)ADXL362_POWER_CTL_AUTOSLEEP;
}

// *************************************************************
// Positionne le circuit en économie d'énergie si il est inactif
// @Return le nombre d'octet ecrit
// *************************************************************
uint8_t GestionADXL362::setAutoSleep(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL) | ADXL362_POWER_CTL_AUTOSLEEP);
}

// ******************************************************
// Positionne le circuit en mode normal si il est inactif
// @Return le nombre d'octet ecrit
// ******************************************************
uint8_t GestionADXL362::unSetAutoSleep(void){
	return genericWrite8(ADXL362_REG_POWER_CTL, genericRead8(ADXL362_REG_POWER_CTL) & ~ADXL362_POWER_CTL_AUTOSLEEP);
}

// *************************
// Donne le mode de mesure
// @Return le mode de mesure
// *************************
GestionADXL362::Measure GestionADXL362::getMeasure(void){
	switch(genericRead8(ADXL362_REG_POWER_CTL) & 0b00000011) {
		case 0b00000000: return standby; break;
		case 0b00000010: return measurement; break;
	}
	return measureError;
}

// *******************************
// Positionne le mode de mesure
// @Return le nombre d'octet ecrit
// *******************************
uint8_t GestionADXL362::setMeasure(GestionADXL362::Measure pValue){
	return genericWrite8(ADXL362_REG_POWER_CTL, (genericRead8(ADXL362_REG_POWER_CTL) & measureMask) | pValue);
}

// *************************
// Demande si le circuit est en auto test 
// @Return true si oui, false si non
// *************************
bool GestionADXL362::isSelfTest(void){
	return genericRead8(ADXL362_REG_SELF_TEST) & (uint8_t)ADXL362_SELF_TEST_ST;
}

// **********************************
// Positionne le circuit en auto test
// @Return le nombre d'octet ecrit
// **********************************
uint8_t GestionADXL362::setSelfTest(void){
	return genericWrite8(ADXL362_REG_SELF_TEST, genericRead8(ADXL362_REG_SELF_TEST) | ADXL362_SELF_TEST_ST);
}

// *******************************************************
// Positionne le circuit est en mode fonctionnement normal
// @Return le nombre d'octet ecrit
// *******************************************************
uint8_t GestionADXL362::unSetSelfTest(void){
	return genericWrite8(ADXL362_REG_SELF_TEST, genericRead8(ADXL362_REG_SELF_TEST) & ~ADXL362_SELF_TEST_ST);
}

// *************************************
// Autonomous Motion switch du datasheet
// *************************************
void GestionADXL362::sampleInit1(void) {
	// Activité 250mG
	setActivityThreshold(0x00FA);
	// Inactivité 150mG
	setInactivityThreshold(0x0096);
	// Inactivité 5s
	setInactivityTime(0x0003);
	// Loop mode detect activité et inactivité
	setActivityInactivity(0x3F);
	// Awake to INT2
	setIntMap2(0x40);
	// start
	setPowerControl(0x0A);
}

// ***********
// Low energie
// ***********
void GestionADXL362::sampleInit2(void) {
	// Activité 100mG
	setActivityThreshold(0x0064);
	// Inactivité 150mG
	setInactivityThreshold(0x0096);
	// Inactivité 0.5s
	setInactivityTime(0x00003);
	// Loop mode detect activité et inactivité
	setActivityInactivity(0x3F);
	// Awake to INT2
	setIntMap2(0x90);
	// start
	setPowerControl(0x0E);
}

// ************************
// Initialisation interrupt
// ************************
void GestionADXL362::sampleInit3(void) {
	// Activité 250mG
	setActivityThreshold(0x001F);
	// Activité 0.1s
	setActivityTime(0x02);
	// Loop mode detect activité et inactivité
	setActivityInactivity(0x15);
	// Awake to INT2
	setIntMap1(0x10);
	// DataReady to INT2
	setIntMap2(0x01);
	// start
	setPowerControl(0x0A);
}

// *******************************************
// Fonction generique de lecture d'un registre
// @Return valeur
// *******************************************
uint8_t GestionADXL362::genericRead8(uint8_t pRegistre){
	digitalWrite(pinCS, LOW);
	SPI.transfer(ADXL362_READ_REG);
	SPI.transfer(pRegistre);
	uint8_t valeur = SPI.transfer(0x00);
	digitalWrite(pinCS, HIGH);
	return valeur;}

// ***********************************************
// Fonction generique de lecture de deux registres
// @Return valeur
// ***********************************************
uint16_t GestionADXL362::genericRead16(uint8_t pRegistre){
	digitalWrite(pinCS, LOW);
	SPI.transfer(ADXL362_READ_REG);
	SPI.transfer(pRegistre);
	uint8_t valeur1 = SPI.transfer(0x00);
	digitalWrite(pinCS, HIGH);
	digitalWrite(pinCS, LOW);
	SPI.transfer(ADXL362_READ_REG);
	SPI.transfer(pRegistre + 1);
	uint8_t valeur2 = SPI.transfer(0x00);
	uint16_t valeur = (uint16_t)(valeur2 << 8) + valeur1;
	digitalWrite(pinCS, HIGH);
	return valeur;
}

// *******************************************
// Fonction generique d'ecriture d'un registre
// @Return nombre d'octet ecrit
// *******************************************
uint8_t GestionADXL362::genericWrite8(uint8_t pRegistre, uint8_t pValue){
	digitalWrite(pinCS, LOW);
	SPI.transfer(ADXL362_WRITE_REG);
	SPI.transfer(pRegistre);
	SPI.transfer(pValue);
	digitalWrite(pinCS, HIGH);
	return 1;
}

// ***********************************************
// Fonction generique d'ecriture de deux registres
// @Return nombre d'octet ecrit
// ***********************************************
uint8_t GestionADXL362::genericWrite16(uint8_t pRegistre, uint16_t pValue){
	digitalWrite(pinCS, LOW);
	SPI.transfer(ADXL362_WRITE_REG);
	SPI.transfer(pRegistre);
	SPI.transfer((uint8_t)(pValue & 0x00FF));
	SPI.transfer((uint8_t)(pValue >> 8));
	digitalWrite(pinCS, HIGH);
	return 2;
}

// *********************************
// Lit le contenu de la mémoire Fifo
// *********************************
//char[] GestionADXL362::getFifoData(uint16_t pNombreValeur){
//	char values[pNombreValeur];
//  digitalWrite(pinCS, LOW);
//	SPI.transfer(ADXL362_READ_FIFO);
//	for(uint16_t compteur = 0; compteur != pNombreValeur; compteur++) {
//		values[compteur] = SPI.transfer(0x00);
//	}
//	digitalWrite(pinCS, HIGH);
//	return values;
//}

// *****************
// Stop spiexplicite
// *****************
void GestionADXL362::spiStop(void){
  SPI.end();
};

// ***********
// Destructeur
// ***********
GestionADXL362::~GestionADXL362(){
  SPI.end();
};
