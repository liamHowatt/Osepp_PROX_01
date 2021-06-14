#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // talk to i2c IC of distance sensor module
  // slave address 0x20
  // (replace with selected address -
  //  0x20, 0x22, 0x24, 0x26)
  Wire.beginTransmission(0x20);
  // select register 3 (configuration register)
  Wire.write(0b11);
  // set pin 0 to output, the rest input
  Wire.write(0b11111110);
  Wire.endTransmission();
  // pins are high by default when set to output.
  // high on pin 0 required to enable IR IC

  Wire.beginTransmission(0x20);
  // select register 0 (pin input reading register)
  Wire.write(0b00);
  Wire.endTransmission();
}

void loop() {
  // read register that is currently selected (reg 0)
  Wire.requestFrom(0x20, 1); // read one byte
  byte b = Wire.read();
  // invert for intuitiveness
  b = ~b;
  // extract pin 1 reading
  b = bitRead(b, 1);

  Serial.println(b);

  delay(50);
}