/*
  MCP23S17 Class Example
  Version 0.2
  Cort Buffington 2011
  
  This example will use the methods in "word mode", that is, writing/reading/setting
  16 bits at a time. Also note that on the inputs, we use the internal pull-up
  resistors and an SPST button to ground when the button is pushed. While this uses
  simpler (less expensive) pushbuttons, it does invert the logic. This is a perfect
  example of one of the more advanced features of the MCP23S17 where we can invert
  the logic state of the input pins. So, when a button is closed, we read a logic
  low state, but the chip will report it as a logic high.
  
  In the example, we'll set up two chips, one as an input and one as an output. We
  will read the input chip, then write the input pin states to the output chip. This
  is a completely useless program in the real world, but it demonstrates the
  abilities of this class well, and makes a simple example.
  
  A few things are done less efficiently than possible to make the sketch easier to
  follow. In the hardware setup I used to write this example, I set up 2 x 8 position
  DIP switches on the input chip, and 16 LEDs on the output chip.
  
  Be sure to see the companion example that demonstrates the same funcionality with
  the methods being used in "bit mode", which replicates the utilitiy of arduino's
  built-in functions digitalWrite and digitalRead.
*/

#include "MCP23S17.h"         // Here is the new class to make using the MCP23S17 easy.

MCP iochip(0, 15);            // Instantiate an object called "outputchip" on an MCP23S17 device at address 2
  								  // and slave-select on Arduino pin 10

void setup() {
	iochip.begin();
	iochip.pinMode(0x0000);    // Use word-write mode to Set all of the pins on outputchip to be outputs
	iochip.digitalWrite(0xFFFF);    // Use word-write mode to Set all of the pins on outputchip to be outputs
	iochip.byteWrite(GPIOA, 0x0A);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x01);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x02);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x04);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x08);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(2000);

	iochip.byteWrite(GPIOA, 0x0F);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x01);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x02);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x04);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x08);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(2000);
}

void loop() {
	//0
	iochip.byteWrite(GPIOA, 0x01);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x01);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//1
	iochip.byteWrite(GPIOA, 0x11);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x02);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//2
	iochip.byteWrite(GPIOA, 0x09);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x04);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//3
	iochip.byteWrite(GPIOA, 0x19);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x08);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//4
	iochip.byteWrite(GPIOA, 0x05);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x01);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//5
	iochip.byteWrite(GPIOA, 0x15);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x02);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//6
	iochip.byteWrite(GPIOA, 0x0D);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x04);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//7
	iochip.byteWrite(GPIOA, 0x1D);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x08);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//8
	iochip.byteWrite(GPIOA, 0x03);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x01);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//9
	iochip.byteWrite(GPIOA, 0x13);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x02);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//0.
	iochip.byteWrite(GPIOA, 0x00);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x04);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//1.
	iochip.byteWrite(GPIOA, 0x10);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x08);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//2.
	iochip.byteWrite(GPIOA, 0x08);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x01);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//3.
	iochip.byteWrite(GPIOA, 0x18);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x02);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//4.
	iochip.byteWrite(GPIOA, 0x04);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x04);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//5.
	iochip.byteWrite(GPIOA, 0x14);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x08);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//6.
	iochip.byteWrite(GPIOA, 0x0C);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x01);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//7.
	iochip.byteWrite(GPIOA, 0x1C);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x02);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//8.
	iochip.byteWrite(GPIOA, 0x02);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x04);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//9.
	iochip.byteWrite(GPIOA, 0x12);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x08);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//TEST
	iochip.byteWrite(GPIOA, 0x0A);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x01);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//BLANK
	iochip.byteWrite(GPIOA, 0x0F);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x02);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//MINUS
	iochip.byteWrite(GPIOA, 0x17);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x04);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);

	//MINUS.
	iochip.byteWrite(GPIOA, 0x16);
	iochip.byteWrite(GPIOB, 0xFF);
	iochip.byteWrite(GPIOB, ~0x08);
	iochip.byteWrite(GPIOB, 0xFF);
	delay(1000);
}
