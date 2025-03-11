/*
  NamKodX 01/02/03
*/
// include these libraries
// #include <stduint8_t const.h>
// #include <avr/uint8_t consterrupt.h>
#include "PortRF24.h"

// Create a new class
PortRF24  portRF;

void setup() {
  portRF.initialization();

}
//
void loop() {
  //portRF.displayResults();
  portRF.patrol();
}
