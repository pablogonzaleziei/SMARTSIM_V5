#include <Arduino.h>
#include <smartairway.h>
#include <BLEPeripheral.h>
#include <systemSetup.h>
#include <ble_uuids.h>

#define rightLung_CS 7
#define stomach_CS 6
#define leftLung_CS 5

// SMART AIRWAY CLASSES
SystemSetup settings;
HeadPosition headSensor;
HeadPosition chestSensor;
StrainGauge strainGauge;
Airflow rightLung;
Airflow stomach;
Airflow leftLung;
FSRsensor upperCricoid(PIN_A0);
FSRsensor lowerCricoid(PIN_A1);

BLEPeripheral blePeripheral;

void systemSetup()
{
  switch (settings.models())
  {
  case 1:
    blePeripheral.setLocalName("SMARTAIRWAYADULT");
    blePeripheral.setDeviceName("SMART AIRWAY ADULT");
    break;
  case 2:
    blePeripheral.setLocalName("SMARTAIRWAYCHILD");
    blePeripheral.setDeviceName("SMART AIRWAY CHILD");
    break;
  case 3:
    blePeripheral.setLocalName("SMARTAIRWAYBABY");
    blePeripheral.setDeviceName("SMART AIRWAY BABY");
    break;
  case 4:
    blePeripheral.setLocalName("SMARTAIRWAYDIFF");
    blePeripheral.setDeviceName("SMART AIRWAY DIFF");
    break;
  }

  // BLE SETUP
  blePeripheral.setAdvertisedServiceUuid(smartAirwayService.uuid());

  blePeripheral.addAttribute(smartAirwayService);

  blePeripheral.addAttribute(cricoidCharacteristic);
  blePeripheral.addAttribute(cricoidDescriptor);

  blePeripheral.addAttribute(headNeckCharacteristic);
  blePeripheral.addAttribute(headNeckDescriptor);

  blePeripheral.addAttribute(pressureCharacteristic);
  blePeripheral.addAttribute(pressureDescriptor);

  blePeripheral.addAttribute(teethCharacteristic);
  blePeripheral.addAttribute(teethDescriptor);

  blePeripheral.addAttribute(errorCharacteristic);
  blePeripheral.addAttribute(errorDescriptor);

  blePeripheral.addAttribute(wifiIPCharacteristic);
  blePeripheral.addAttribute(wifiIPDescriptor);

  blePeripheral.addAttribute(jawCharacteristic);
  blePeripheral.addAttribute(jawDescriptor);

  blePeripheral.addAttribute(credentialsCharacteristic);
  blePeripheral.addAttribute(credentialsDescriptor);
  blePeripheral.begin();
}

void setup()
{
  Serial.begin(115200);
  systemSetup();

  // INCISOR FORCE SETUP
  uint8_t dataPin = 16, clockPin = 17;
  // strainGauge.begin(dataPin, clockPin);
  // strainGauge.setScale(420.0983);
  // strainGauge.tare();

  // HEAD SENSOR SETUP
  // headSensor.begin(0x18);

  // Airflow setup
  rightLung.begin(rightLung_CS);
  leftLung.begin(leftLung_CS);
  stomach.begin(stomach_CS);
}

void loop()
{
  BLECentral central = blePeripheral.central();
  blePeripheral.poll();
  if (central)
  {
    Serial.print(F("Connected to central: "));
    Serial.println(central.address());
    // headSensor.getPitch();
    // upperCricoid.getTaredForce();
    // rightLung.readSensor();
    // strainGauge.getUnits(1);
  }
  Serial.print(F("Disconnected from central: "));
  Serial.println(central.address());

  delay(100);
}