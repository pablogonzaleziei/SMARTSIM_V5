#include "StrainGauge.h"

StrainGauge::StrainGauge(uint8_t dataPin, uint8_t clockPin, float scaleValue) {
  scale.begin(dataPin, clockPin);
  scale.set_scale(scaleValue);
  scale.tare();
}

int StrainGauge::getIncisorForce() {
  return scale.get_units(1);
}
