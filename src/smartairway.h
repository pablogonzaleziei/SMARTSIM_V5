#ifndef _SMART_AIRWAY_H_
#define _SMART_AIRWAY_H_

#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "HX711.h"
#include "BlueDot_BME280.h"
/*
 *  @brief  Class for Head Position feature of Smart Airway.
 *  if I2C, define address with begin()
 *  @author  pgonzalez
 */
class HeadPosition
{
public:
  HeadPosition();
  bool begin(uint8_t address);
  int getPitch();
  int isConnected();

private:
  Adafruit_LIS3DH _lis3dh;
};

/*
 *  @brief  Class for Incisor force feature of Smart Airway.
 *  Load Cell Amp embedded: dataPin = 16; clockPin = 17
 *  External Load cell Amp: Data: 3, clock: 4
 *  @author  pgonzalez
 */
class StrainGauge
{
public:
  StrainGauge();
  void begin(uint8_t dataPin, uint8_t clockPin);
  void setScale(float scale);
  void tare();
  float getUnits(byte times);
  double getValue(byte times);
  float read_raw();

private:
  HX711 _hx711;
};

/*
 *  @brief  Class for Airflow measuring
 *  @author  pgonzalez
 */
class Airflow
{
public:
  Airflow();
  int readSensor();
  bool begin(uint8_t chipSelect);
  int isConnected();

private:
  BlueDot_BME280 _BME280;
  bool tareAirflow;
  float airflowOrigin;
  int airflow;
  const int SPI_MOSI_PIN = 11;
  const int SPI_MISO_PIN = 12;
  const int SPI_SCK_PIN = 13;
  const int SENSOR_MODE = 0b11;
  const int IIR_FILTER = 0b100;
  const int HUMIDITY_OVERSAMPLING = 0b101;
  const int TEMP_OVERSAMPLING = 0b101;
  const int PRESSURE_OVERSAMPLING = 0b101;
  const float pressureSeaLevel = 1013.25;
};

/*
 *  @brief  Class for any FSR sensor. Used for Cricoid force and Jaw thrust.
 *  @author  pgonzalez
 */
class FSRsensor
{
  private:
  uint8_t _analogPin;

public:
  FSRsensor(uint8_t analogPin);
  int getTaredForce();
  int getRawForce();

};

#endif
