#include "smartairway.h"

// HEAD SENSOR FUNCTIONS---------------------------------------------------

HeadPosition::HeadPosition() {}

/*
 *  @brief  Initialize the LIS3DH sensor and set the range to 2G 
 *  @param address: I2C address
 *  @return true if address is correct (0x18 or 0x19). false if failure
 *  @author  pgonzalez
 */
bool HeadPosition::begin(uint8_t address)
{
  if (_lis3dh.begin(address))
  {
    _lis3dh.setRange(LIS3DH_RANGE_2_G);
    return true;
  }
  else
  {
    // Serial.println("Sensor not found!");
    return false;
  }
}

/*
 *  @brief  Calculates the inclination of the x-axis in degrees
 *  @return value of pitch (float)
 *  @author  pgonzalez
 */
float HeadPosition::getPitch()
{
  _lis3dh.read();
  float x = _lis3dh.x / 1000.0;
  float z = _lis3dh.z / 1000.0;
  float pitch = atan2(x, z) * 180.0 / PI;
  return pitch;
}

// STRAIN GAUGE FUNCTIONS---------------------------------------------------

StrainGauge::StrainGauge() {}

/*
 *  @brief  Initialize the H7X11 
 *  @param dataPin: Serial Data Output Pin 
 *  @param clockPin: Serial Clock Input Pin
 *  @author  pgonzalez
 */
void StrainGauge::begin(uint8_t dataPin, uint8_t clockPin)
{
  _hx711.begin(dataPin, clockPin);
}

/*
 *  @brief  Specify scale for H7X11
 *  @param scale: this value is used to convert the raw data to "human readable" data (measure units)
 *  @author  pgonzalez
 */
void StrainGauge::setScale(float scale)
{
  _hx711.set_scale(scale);
}

/*
 *  @brief  set the OFFSET value for tare weight. See smartairwaycpp to change
 *  @author  pgonzalez
 */
void StrainGauge::tare()
{
  _hx711.tare();
}
/*
 *  @brief  Value of getValue() divided by SCALE (obtained by calibration)
 *  @param times: how many readings to do
 *  @return getValue()/SCALE
 *  @author  pgonzalez
 */
float StrainGauge::getUnits(byte times)
{
  return _hx711.get_units(times);
}
/*
 *  @brief  Current value without the tare weight; 
 *  @param times: how many readings to do
 *  @return Tared value (double)
 *  @author  pgonzalez
 */
double StrainGauge::getValue(byte times) {
	return _hx711.read_average(times) - _hx711.get_offset();
}

// AIRFLOW FUNCTIONS---------------------------------------------------

Airflow::Airflow()
{
  checkOrigin = 0;
  airflowOrigin = 0;
  airflow = 0;
}

/*
 *  @brief  Value of pressure - initial value.
 *  @return airflow (int) OR -1: if sensor not connected
 *  @author  pgonzalez
 */
int Airflow::readSensor()
{

  while (checkOrigin == 0)
  {
    delay(100);
    airflowOrigin = _BME280.readPressure() * 1000;
    Serial.print("tare");
    checkOrigin = 1;
  }

  airflow = _BME280.readPressure() * 1000 - airflowOrigin;

  if (airflow < 0)
  {
    airflow = 0;
  }
  if (_BME280.checkID())
  {
    return airflow;
  }
  else
  {
    return -1;
  }
}

/*
 *  @brief  Initialize BME280
 *  @param chipSelect: Digital pin connected to chip select of sensor
 *  @return true if success, false if sensor not detected
 *  @author  pgonzalez
 */
bool Airflow::begin(uint8_t chipSelect)
{

  // 0: SPI Hardware
  // 1: SPI Software
  _BME280.parameter.communication = 1;                         // Hardware SPI
  _BME280.parameter.SPI_cs = chipSelect;                       // Chip Select Pin (Default arduino: 7 rightLung, 6 stomach, 5 leftLung)
  _BME280.parameter.SPI_mosi = SPI_MOSI_PIN;                   // The MOSI signal must be connected to the same pin for all sensors
  _BME280.parameter.SPI_miso = SPI_MISO_PIN;                   // The MISO signal must be connected to the same pin for all sensors
  _BME280.parameter.SPI_sck = SPI_SCK_PIN;                     // The SCK signal must be connected to the same pin for all sensors
  _BME280.parameter.sensorMode = SENSOR_MODE;                  // Setup Sensor mode
  _BME280.parameter.IIRfilter = IIR_FILTER;                    // IIR Filter
  _BME280.parameter.humidOversampling = HUMIDITY_OVERSAMPLING; // Humidity Oversampling
  _BME280.parameter.tempOversampling = TEMP_OVERSAMPLING;      // Temperature Oversampling
  _BME280.parameter.pressOversampling = PRESSURE_OVERSAMPLING; // Pressure Oversampling
  _BME280.parameter.pressureSeaLevel = pressureSeaLevel;       // default value of 1013.25 hPa
  if (_BME280.init())
  {
    Serial.print("ChipSelect: ");
    Serial.print(chipSelect);
    Serial.println("; BME280 init OK");
    return true;
  }
  else
  {
    Serial.print("ChipSelect: ");
    Serial.print(chipSelect);
    Serial.println("; BME280 init failed");
    return false;
  }
}


// FSR FUNCTIONS---------------------------------------------------


FSRsensor::FSRsensor(uint8_t analogPin) {
  _analogPin = analogPin;
  
}

/*
 *  @brief  FSR reading reseted depending on initial force
 *  @author  pgonzalez
 */
int FSRsensor::getTaredForce(){
  
  int fsrRaw = analogRead(_analogPin);
  
  static int restForce = 0; // Initial force in FSR1 (Trachea insert + neck skin)

  // Reset rest forces on the first loop iteration
  static bool isInitialized = false;
  if (!isInitialized) {
    restForce = fsrRaw;
    isInitialized = true;
  }

  int deltaFSR = fsrRaw - restForce;
  return deltaFSR;
}

/*
 *  @brief  FSR raw analog reading
 *  @author  pgonzalez
 */
int FSRsensor::getRawForce(){
  
  int fsrRaw = analogRead(_analogPin);
  return fsrRaw;
}
