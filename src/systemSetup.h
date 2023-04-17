#ifndef _SYSTEM_SET_UP_H_
#define _SYSTEM_SET_UP_H_

#include <Arduino.h>
#include <BLEPeripheral.h>
/*
 *  @brief  Manage the system settings like selecting the model, manage errors...
 *  @author  pgonzalez
 */

class SystemSetup
{
private:

  const int PIN_8 = 8;
  const int PIN_2 = 2;
  const int MODEL_ADULT = 1;
  const int MODEL_CHILD = 2;
  const int MODEL_BABY = 3;
  const int MODEL_DIFFICULT = 4;
  const int PIN_STATES[4][2] = {
      {0, 0}, // adult
      {0, 1}, // child
      {1, 0}, // baby
      {1, 1}  // difficult
  };

public:
  SystemSetup();
  int models();
  void error();
  void BLEsetup();
};

#endif

