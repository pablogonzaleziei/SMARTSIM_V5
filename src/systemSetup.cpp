#include "systemSetup.h"
#include "Arduino.h"
#include <BLEPeripheral.h>


/*
 *  @brief  Select the model for the smart airway app with the jumpers
 *  @author  pgonzalez
 */
SystemSetup::SystemSetup() {}

int SystemSetup::models()
{
  pinMode(PIN_2, INPUT);
  pinMode(PIN_8, INPUT);
  int pin8 = digitalRead(PIN_8);
  int pin2 = digitalRead(PIN_2);
  int model = 0;

  for (int i = 0; i < 4; i++)
  {
    if (pin8 == PIN_STATES[i][0] && pin2 == PIN_STATES[i][1])
    {
      model = i + 1;
      break;
    }
  }

  return model;
}

void error()
{
}

void BLEsetup()
{
  
}