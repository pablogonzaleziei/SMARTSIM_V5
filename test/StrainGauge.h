#ifndef StrainGauge_h
#define StrainGauge_h

#include <Arduino.h>
#include "HX711.h"

class StrainGauge {
  public:
    StrainGauge(uint8_t dataPin, uint8_t clockPin, float scaleValue);
    int getIncisorForce();
  private:
    HX711 scale;
};

#endif
