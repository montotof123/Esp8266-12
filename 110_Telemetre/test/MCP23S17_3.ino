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

#include "GestionHP50827300.h"         // Here is the new class to make using the MCP23S17 easy.

GestionHP50827300 aff1(0, 15, 0);
GestionHP50827300 aff2(0, 15, 1);
GestionHP50827300 aff3(0, 15, 2);
GestionHP50827300 aff4(0, 15, 3);
void setup() {
}

void loop() {
	//0
  aff1.setValueWithoutPoint(0);
  aff2.setValueWithoutPoint(1);
  aff3.setValueWithoutPoint(2);
  aff4.setValueWithoutPoint(3);
  delay(1000);

  aff1.setValueWithoutPoint(1);
  aff2.setValueWithoutPoint(2);
  aff3.setValueWithoutPoint(3);
  aff4.setValueWithoutPoint(4);
  delay(1000);

  aff1.setValueWithoutPoint(2);
  aff2.setValueWithoutPoint(3);
  aff3.setValueWithoutPoint(4);
  aff4.setValueWithoutPoint(5);
  delay(1000);

  aff1.setValueWithoutPoint(3);
  aff2.setValueWithoutPoint(4);
  aff3.setValueWithoutPoint(5);
  aff4.setValueWithoutPoint(6);
  delay(1000);

  aff1.setValueWithoutPoint(4);
  aff2.setValueWithoutPoint(5);
  aff3.setValueWithoutPoint(6);
  aff4.setValueWithoutPoint(7);
  delay(1000);

  aff1.setValueWithoutPoint(5);
  aff2.setValueWithoutPoint(6);
  aff3.setValueWithoutPoint(7);
  aff4.setValueWithoutPoint(8);
  delay(1000);

  aff1.setValueWithoutPoint(6);
  aff2.setValueWithoutPoint(7);
  aff3.setValueWithoutPoint(8);
  aff4.setValueWithoutPoint(9);
  delay(1000);

  aff1.setValueWithoutPoint(7);
  aff2.setValueWithoutPoint(8);
  aff3.setValueWithoutPoint(9);
  aff4.setValueWithoutPoint(0);
  delay(1000);

  aff1.setValueWithoutPoint(8);
  aff2.setValueWithoutPoint(9);
  aff3.setValueWithoutPoint(0);
  aff4.setValueWithoutPoint(1);
  delay(1000);

  aff1.setValueWithoutPoint(9);
  aff2.setValueWithoutPoint(0);
  aff3.setValueWithoutPoint(1);
  aff4.setValueWithoutPoint(2);
  delay(1000);
}
