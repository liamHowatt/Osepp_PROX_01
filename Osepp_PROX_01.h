/*
  Osepp_PROX_01.h - Library for using
  the Osepp PROX-01 proximity module.
  Created by Liam Howatt, June 13, 2021.
  Released into the public domain.
*/
#ifndef Osepp_PROX_01_h
#define Osepp_PROX_01_h

#include "Arduino.h"
#include "Wire.h"

#define PCA9534_REGISTER_READ 0
#define PCA9534_REGISTER_WRITE 1
#define PCA9534_REGISTER_INVERT 2
#define PCA9534_REGISTER_CONFIG 3

class Osepp_PROX_01
{
  public:
    Osepp_PROX_01(int address, TwoWire *wire = &Wire);
    void begin();
    bool read();
    void turnIRLEDOn();
    void turnIRLEDOff();
  private:
    int _address;
    TwoWire *_wire;
    bool _IR_LED_state;
    uint8_t _selected_register;
};

#endif