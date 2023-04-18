#include <Arduino.h>
#include <smartairway.h>
#include <BLEPeripheral.h>
#include <systemSetup.h>
#include <ble_uuids.h>

#define rightLung_CS 7
#define stomach_CS 6
#define leftLung_CS 5

const int bleConnected = 10;
// SMART AIRWAY CLASSES
SystemSetup settings;
HeadPosition headSensor;
HeadPosition chestSensor;
StrainGauge incisor;
Airflow rightLung;
Airflow stomach;
Airflow leftLung;
FSRsensor upper_Cricoid(PIN_A0);
FSRsensor lower_Cricoid(PIN_A1);
FSRsensor frontLeft_Jaw(PIN_A2);
FSRsensor backLeft_Jaw(PIN_A3);
FSRsensor frontRight_Jaw(PIN_A4);
FSRsensor backRight_Jaw(PIN_A5);
FSRsensor left_Maxilla(PIN_A4);
FSRsensor right_Maxilla(PIN_A5);

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

  blePeripheral.addAttribute(headPositionCharacteristic);
  blePeripheral.addAttribute(headPositionDescriptor);

  blePeripheral.addAttribute(pressureCharacteristic);
  blePeripheral.addAttribute(pressureDescriptor);

  blePeripheral.addAttribute(incisorForceCharacteristic);
  blePeripheral.addAttribute(incisorForceDescriptor);

  blePeripheral.addAttribute(connectedSensorsCharacteristic);
  blePeripheral.addAttribute(connectedSensorsDescriptor);

  blePeripheral.addAttribute(wifiIPCharacteristic);
  blePeripheral.addAttribute(wifiIPDescriptor);

  blePeripheral.addAttribute(jawCharacteristic);
  blePeripheral.addAttribute(jawDescriptor);

  blePeripheral.addAttribute(credentialsCharacteristic);
  blePeripheral.addAttribute(credentialsDescriptor);
  blePeripheral.begin();

  pinMode(bleConnected, OUTPUT);
}

void connectedSensors()
{
  bool isWritten = connectedSensorsCharacteristic.written();
  char connectedSensorsArray[7] = {rightLung.isConnected(), leftLung.isConnected(), stomach.isConnected(), headSensor.isConnected(), chestSensor.isConnected(), 0, settings.wifi_written(isWritten)};
  if (settings.wifi_written(isWritten) == 1)
  {
    Serial.println("Alguien ha matado a alguien...");
  }
  connectedSensorsCharacteristic.setValue((const unsigned char *)connectedSensorsArray, 7);
}

void setup()
{
  Serial.begin(115200);
  systemSetup();

  // INCISOR FORCE SETUP
  uint8_t dataPin = 16, clockPin = 17;
  incisor.begin(dataPin, clockPin);
  incisor.setScale(420.0983);
  incisor.tare();

  // HEAD SENSOR SETUP
  headSensor.begin(0x18);
  chestSensor.begin(0x19);

  // Airflow setup
  rightLung.begin(rightLung_CS);
  leftLung.begin(leftLung_CS);
  stomach.begin(stomach_CS);
}

void airflow()
{
  char airflowArray[6] = {lowByte(rightLung.readSensor()), highByte(rightLung.readSensor()),
                          lowByte(leftLung.readSensor()), highByte(leftLung.readSensor()),
                          lowByte(stomach.readSensor()), highByte(stomach.readSensor())};

  pressureCharacteristic.setValue((const unsigned char *)airflowArray, 6);
}

void headPosition()
{
  char headPositionArray[4] = {lowByte(headSensor.getPitch()), highByte(headSensor.getPitch()),
                               lowByte(chestSensor.getPitch()), highByte(chestSensor.getPitch())};

  headPositionCharacteristic.setValue((const unsigned char *)headPositionArray, 6);
}

void incisorForce()
{

  int incisor_force = incisor.getUnits(1);
  // Serial.println(incisor_force);
  char incisorForceArray[2] = {lowByte(incisor_force), highByte(incisor_force)};

  incisorForceCharacteristic.setValue((const unsigned char *)incisorForceArray, 2);
}

void cricoidForce()
{
  char cricoidForceArray[4] = {lowByte(upper_Cricoid.getTaredForce()), highByte(upper_Cricoid.getTaredForce()),
                               lowByte(lower_Cricoid.getTaredForce()), highByte(lower_Cricoid.getTaredForce())};

  cricoidCharacteristic.setValue((const unsigned char *)cricoidForceArray, 4);
}

void jawThrust()
{
  char jawArray[12] = {lowByte(backLeft_Jaw.getTaredForce()), highByte(backLeft_Jaw.getTaredForce()),
                       lowByte(frontLeft_Jaw.getTaredForce()), highByte(frontLeft_Jaw.getTaredForce()),
                       lowByte(frontRight_Jaw.getTaredForce()), highByte(frontRight_Jaw.getTaredForce()),
                       lowByte(backRight_Jaw.getTaredForce()), highByte(backRight_Jaw.getTaredForce()),
                       lowByte(left_Maxilla.getTaredForce()), highByte(left_Maxilla.getTaredForce()),
                       lowByte(right_Maxilla.getTaredForce()), highByte(right_Maxilla.getTaredForce())};
  jawCharacteristic.setValue((const unsigned char *)jawArray, 12);
}
void loop()
{
  BLECentral central = blePeripheral.central();
  blePeripheral.poll();
  if (central)
  {
    Serial.print(F("Connected to central: "));
    Serial.println(central.address());

    while (central.connected())
    {
      settings.bleConnected(true);
      airflow();
      incisorForce();
      headPosition();
      cricoidForce();
      connectedSensors();
      delay(10);
    }

    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
  settings.bleConnected(false);

  delay(100);
}
