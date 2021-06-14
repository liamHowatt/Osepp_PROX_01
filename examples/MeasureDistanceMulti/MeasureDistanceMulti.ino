#include <Osepp_PROX_01.h>

// multiple modules are required
// for this example

Osepp_PROX_01 prox1(0x20);
Osepp_PROX_01 prox2(0x22);
Osepp_PROX_01 prox3(0x24);

void setup(){
  prox1.begin();
  prox2.begin();
  prox3.begin();
  Serial.begin(9600);
}

void loop(){
  Serial.print(prox1.read());
  Serial.print(" ");
  Serial.print(prox2.read());
  Serial.print(" ");
  Serial.println(prox3.read());
  delay(20);
}
