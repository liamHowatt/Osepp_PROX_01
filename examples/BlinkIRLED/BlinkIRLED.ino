#include <Osepp_PROX_01.h>

// replace "0x20" with the address chosen using the
// microswitches on the module (0x20, 0x22, 0x24, 0x26)
Osepp_PROX_01 prox1(0x20);

void setup(){
  prox1.begin();
}

void loop(){
  prox1.turnIRLEDOn();
  delay(200);
  prox1.turnIRLEDOff();
  delay(200);
}
