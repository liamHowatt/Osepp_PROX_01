/*
  Osepp_PROX_01.cpp - Library for using
  the Osepp PROX-01 proximity module.
  Created by Liam Howatt, June 13, 2021.
  Released into the public domain.
*/
#include "Arduino.h"
#include "Osepp_PROX_01.h"

Osepp_PROX_01::Osepp_PROX_01(int address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  _IR_LED_state = true;
  _selected_register = PCA9534_REGISTER_WRITE;
}

void Osepp_PROX_01::begin()
{
  _wire->begin();

  // talk to i2c IC of distance sensor module
  // slave address 0x20
  _wire->beginTransmission(_address);
  // select register 3 (configuration register)
  _wire->write(PCA9534_REGISTER_CONFIG);
  // set pin 0 to output, the rest input
  _wire->write(0b11111110);
  _wire->endTransmission();
  // pins are high by default when set to output.
  // high on pin 0 required to enable IR IC
  // explicitly turn on IR LED just in case
  turnIRLEDOn();
}

bool Osepp_PROX_01::read()
{
  if(_selected_register != PCA9534_REGISTER_READ){
    _wire->beginTransmission(_address);
    // select register 0 (pin input reading register)
    _wire->write(PCA9534_REGISTER_READ);
    _wire->endTransmission();
    _selected_register = PCA9534_REGISTER_READ;
  }

  // read register that is currently selected (reg 0)
  _wire->requestFrom(_address, 1); // read one byte
  byte b = _wire->read();
  // extract pin 1 reading
  b = bitRead(b, 1);

  // Invert the value so it makes more sense
  // true for object near, false for nothing detected
  return (bool) !b;
}

void Osepp_PROX_01::turnIRLEDOn()
{
  if(_IR_LED_state){
    // already on
    return;
  }

  _wire->beginTransmission(_address);
  // select register 1 (output register)
  _wire->write(PCA9534_REGISTER_WRITE);
  // set pin 0 high
  _wire->write(0b11111111);
  _wire->endTransmission();
  _selected_register = PCA9534_REGISTER_WRITE;

  _IR_LED_state = true;
}

void Osepp_PROX_01::turnIRLEDOff()
{
  if(!_IR_LED_state){
    // already off
    return;
  }

  _wire->beginTransmission(_address);
  // select register 1 (output register)
  _wire->write(PCA9534_REGISTER_WRITE);
  // set pin 0 low
  _wire->write(0b11111110);
  _wire->endTransmission();
  _selected_register = PCA9534_REGISTER_WRITE;

  _IR_LED_state = false;
}