// ***************************************************************************************
// totof 2020/11/21
// Mise en EEPROM d'un identifiant d'IOT
// Inspiré de l'article: https://projetsdiy.fr/esp8266-comment-lire-ecrire-effacer-eeprom/
// ***************************************************************************************

#include <EEPROM.h> 

// Adresse de l'identifiant dans l'EEPROM
int addr_id = 0;
// Max 200 caractères
int sizeEEPROM = 200;
// Caractère § indiquant un caractère inutilisé
int emptyChar = 167;

// Identifiant
String id = "PorteEntrée";

// true si l'EEPROM doit être effacé, false sinon
#define RESET_EEPROM true

// *****************************************
//       ***** ***** ***** *   * *****
//       *     *       *   *   * *   *
//       ***** ****    *   *   * *****
//           * *       *   *   * *
//       ***** *****   *   ***** *
// *****************************************
void setup() {
  // Initialisation
  Serial.begin(115200);
  EEPROM.begin(sizeEEPROM);
  Serial.println("");

  // Effacement EEPROM si voulu
  if ( RESET_EEPROM ) {
    for (int i = 0; i < sizeEEPROM; i++) {
      EEPROM.write(i, emptyChar);
    }
    EEPROM.commit();
    delay(500);
  }

  // Envoie de l'identifiant dans l'EEPROM
  Serial.println("");
  Serial.print("Write ID at address "); Serial.println(addr_id);
  Serial.print("");
  for (int i = 0; i < id.length(); ++i)
  {
    EEPROM.write(addr_id + i, id[i]);
    Serial.print(id[i]); Serial.print("");
  }
  
  // Ecriture de l'identifiant dans l'EEPROM
  Serial.println("");
  if (EEPROM.commit()) {
    Serial.println("Data successfully committed");
  } else {
    Serial.println("ERROR! Data commit failed");
  }

  // Vérification globale de la zone EEPROM
  Serial.println("");
  Serial.println("Check writing");
  String idfull;
  for (int k = addr_id; k < addr_id + sizeEEPROM; ++k)
  {
    Serial.print(char(EEPROM.read(k)));
    idfull += char(EEPROM.read(k));
  }
  Serial.println("");
  Serial.print("ID: ");
  Serial.println(idfull);
  
  // Vérification de l'identifiant
  Serial.println("");
  Serial.println("Check writing");
  String id;
  for (int k = addr_id; k < addr_id + sizeEEPROM; ++k)
  {
    Serial.print(char(EEPROM.read(k)));
    if(EEPROM.read(k) == emptyChar){
      break;
    } else {
      id += char(EEPROM.read(k));
    }
  }
  Serial.println("");
  Serial.print("ID: ");
  Serial.println(id);

  EEPROM.end();
}

// ****************************************
//         *     ***** ***** *****
//         *     *   * *   * *   *
//         *     *   * *   * *****
//         *     *   * *   * *
//         ***** ***** ***** *
// ****************************************
// Vide, tout se passe dans le setup
void loop() {
}
