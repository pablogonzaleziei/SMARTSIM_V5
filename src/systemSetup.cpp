#include "systemSetup.h"
#include "Arduino.h"
#include <BLEPeripheral.h>
#include <smartairway.h>

/*
 *  @brief  Select the model for the smart airway app with the jumpers
 *  @author  pgonzalez
 */
SystemSetup::SystemSetup()
{
  pinMode(bleConnectedPin, OUTPUT);
  pinMode(wifiForgetPin, OUTPUT);
}

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

/*
 *  @brief  Control the LED of the switch. It blinks if BLE is disconnected.
 *  @param BLEconnected: (bool) true if a BLE device is connected
 *  @author  pgonzalez
 */
void SystemSetup::bleConnected(bool BLEconnected)
{

  if (!BLEconnected)
  {
    digitalWrite(bleConnectedPin, HIGH);
    delay(200);
    digitalWrite(bleConnectedPin, LOW);
    delay(200);
  }
  else
  {
    digitalWrite(bleConnectedPin, HIGH); // light of switch on and continuous
  }
}

int SystemSetup::wifi_written(bool written)
{
  if (written){
    digitalWrite(wifiForgetPin, 1);
    return 1;
  }else{
    return 0;
  }

  
}

// void SystemSetup::error(){

// }

// void BLEsetup()
// {

// }