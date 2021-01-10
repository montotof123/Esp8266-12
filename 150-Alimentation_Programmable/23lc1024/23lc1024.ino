/*!
 *   \file    23lc1024.cpp
 *   \brief   Lecture et écriture dans la mémoire série
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    10/01/2021
 */

#include <SPI.h>
#include <SRAM_23LC.h>

#define SPI_PERIPHERAL		SPI
#define CHIP_SELECT_PIN		16
#define START_ADDRESS   0
#define RAM_SIZE  1310
//131072 max

/**
 *   \brief   Mémoire série 23LC1024
 */
SRAM_23LC SRAM(&SPI_PERIPHERAL, CHIP_SELECT_PIN, SRAM_23LC1024);


// *****************************************
//       ***** ***** ***** *   * *****
//       *     *       *   *   * *   *
//       ***** ****    *   *   * *****
//           * *       *   *   * *
//       ***** *****   *   ***** *
// *****************************************
void setup(void)
{
	SRAM.begin();

	Serial.begin(115200);
	while (!Serial);
}

// ****************************************
//         *     ***** ***** *****
//         *     *   * *   * *   *
//         *     *   * *   * *****
//         *     *   * *   * *
//         ***** ***** ***** *
// ****************************************
void loop(void)
{
	// Write Byte, print to serial monitor
	Serial.print("Write Byte:  ");
	uint8_t data = 0;
	for (uint32_t i=0; i < RAM_SIZE; i++) {
		SRAM.writeByte(START_ADDRESS + i, data);
		data++;
		yield(); // Réinitialise le Watchdog si il y a beaucoup à écrire
		// https://forum.arduino.cc/index.php?topic=442570.0
	}
	Serial.println();

	// Read Byte, print to serial monitor
	Serial.print("Read Byte:  ");
	for (uint32_t i=0; i < RAM_SIZE; i++) {
		data = SRAM.readByte(START_ADDRESS + i);
		Serial.write(data);
		if(data == 255) {
			Serial.println();
		}
		yield();
	}
	Serial.println();

	delay(10000);
}
