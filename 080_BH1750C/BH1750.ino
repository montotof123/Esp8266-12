#include <Wire.h>

#define ADDRESS_BH1750 0x23

#define BH1750_POWER_DOWN 0x00
#define BH1750_POWER_ON 0x01
#define BH1750_RESET 0x07
#define BH1750_CONTINUOUS_HIGH_RES_MODE 0x10
#define BH1750_CONTINUOUS_HIGH_RES_MODE_2 0x11
#define BH1750_CONTINUOUS_LOW_RES_MODE 0x13
#define BH1750_ONE_TIME_HIGH_RES_MODE 0x20
#define BH1750_ONE_TIME_HIGH_RES_MODE_2 0x21
#define BH1750_ONE_TIME_LOW_RES_MODE 0x23

union i2cData{
  unsigned short uSData;
  unsigned char uCData[2];
};  
  
void setup() {
  Serial.begin(115200);  // Initialisation Terminal Série
  Wire.begin();        // Initialisation I2C

  /* Configuration du BH1750 */
  Wire.beginTransmission(ADDRESS_BH1750);
  Wire.write(BH1750_POWER_ON);
  Wire.endTransmission();
  Wire.beginTransmission(ADDRESS_BH1750);
  Wire.write(BH1750_RESET);
  Wire.endTransmission();
}

void loop() {
  i2cData data;
  float valeur;
  
  Wire.beginTransmission(ADDRESS_BH1750);
  Wire.write(0x42);
  Wire.endTransmission();
  Wire.beginTransmission(ADDRESS_BH1750);
  Wire.write(0x65);
  Wire.endTransmission();
  Wire.beginTransmission(ADDRESS_BH1750);
  Wire.write(BH1750_CONTINUOUS_HIGH_RES_MODE);
  Wire.endTransmission();

  delay(150);

  Wire.requestFrom(ADDRESS_BH1750, 2); // Deux octets sont requis
  if (2 <= Wire.available()) {
    data.uCData[1] = Wire.read();  // Octet de poids fort
    data.uCData[0] = Wire.read();  // Octet de poids faible
  }

  valeur = (float)data.uSData / 1.2;

  Serial.print("Lumière = ");
  Serial.print(valeur);
  Serial.println(" lux");

  delay(1000);  // Attendre 1 s avant de recommencer

}
