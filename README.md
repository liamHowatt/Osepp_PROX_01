# Osepp PROX-01 Distance Sensor Module Library
I made this library to make it easier for others to get up and running with this module.

What this module does is very simple. It reports a 1 bit signal based on the distance of an object from it. **It is not analog**.

`read()` returns `false` if nothing is near and `true` if it detects an object within a certain distance (~1.5 cm). It is important to note that it also emits `false` when an object is very close (~0.5 cm).

The values are read over i2c (aka Wire). Up to four of these modules can be chained together. Use the microswitches on the module to select an i2c address. If you are using more than one module, make sure you use a different address for each. Take note of the address(es) to use in your code.

## Wiring
Red => 5v\
White => SDA\
Black => GND\
Gray => SCL

There are plenty of resources online to locate the i2c SDA and SCL pins on your particular Arduino board. For the Arduino Uno, SDA is pin A4 and SCL is pin A5. Arduino Uno R3 also has unlabled SDA and SCL pins next to the AREF pin.

The modules can be "daisy chained" together by plugging one into the next.

## Installation
Simply download this repository as a zip file, then in your Arduino IDE go to Sketch>Include Library>Add .ZIP Library

## Usage
```Arduino
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
  delay(20);
}
```
This example is included in the library and, once installed, can be opened with File>Examples>Osepp_PROX_01>MeasureDistance.

You can use multiple modlues like so
```Arduino
// --snip--
Osepp_PROX_01 prox1(0x20);
Osepp_PROX_01 prox2(0x22);
Osepp_PROX_01 prox3(0x24);

void setup(){
    prox1.begin();
    prox2.begin();
    prox3.begin();
    // --snip--
}
// --snip--
```

## Advanced Usage
You may want to use a different i2c interface or toggle the IR LED to conserve power. That functionality is available, but not required whatsoever for basic usage.

### i2c Interface
This library uses the builtin `Wire.h` library to communicate with the module over i2c. It should be safe to use `Wire` elsewhere in your sketch, or include other libraries that use it too (given they don't use the same address).

If your board has multiple i2c interfaces, you can pass a pointer to the constructor and it will use that instead of the default `Wire` interface.
```Arduino
// Replace "Wire" with a different i2c interface
// to use that to communicate over i2c instead.
// It expects a valid TwoWire interface.
Osepp_PROX_01 prox1(0x20, &Wire);
```

### Toggle the IR LED
The member functions `turnIRLEDOff()` and `turnIRLEDOff()` are available.

This is probably only worth doing if you are using the IR LED in this module as a general purpose IR LED, or if you wish to conserve as much power as possible when the module is not in use.

```Arduino
// --snip--
void loop(){
  prox1.turnIRLEDOff();
  delay(1000);
  prox1.turnIRLEDOn();
  delay(1000);
}
```

**You cannot see IR light with your eyes**; however, some cameras can.

`read()` **does not** turn the IR LED on if it is off. Readings will be incorrect if the IR LED is not on. It is not known whether a value read immediately after turning on the IR LED will be reliable or not.

## Further Reading
[Osepp Proximity Senor schematic](https://www.osepp.com/downloads/pdf/OSEPP-PROX-01_REV1_1.pdf)\
[GP2Y0D815Z0F onboard distance measuring sensor unit](https://www.pololu.com/file/0J813/gp2y0d815z_e.pdf)\
[PCA9534 onboard i2c I/O expander IC](https://www.ti.com/lit/ds/symlink/pca9534.pdf?ts=1621111481195&ref_url=https%253A%252F%252Fwww.google.com%252F)
