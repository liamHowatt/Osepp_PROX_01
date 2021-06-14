#include <Osepp_PROX_01.h>

// replace "0x20" with the address chosen using the
// microswitches on the module (0x20, 0x22, 0x24, 0x26)
Osepp_PROX_01 prox1(0x20);

void setup(){
  prox1.begin();
  Serial.begin(9600);
}

void loop(){
  bool is_near = prox1.read();
  Serial.println(is_near);
  
  // potentially save a tiny bit of power
  // between reads
  prox1.turnIRLEDOff();
  delay(1000);
  prox1.turnIRLEDOn();
  // give some time for the sensor to
  // register a reflection (just in case)
  delay(20);
}
