//
/*
 *  @brief  This library contains all the necesary UUIDs for SMARTSIM (smart airway, CPR...)
 *  @author  pgonzalez
 */
#ifndef BLE_UUIDS_H
#define BLE_UUIDS_H

//Services UUIDs
#define SMART_AIRWAY_SERVICE_UUID "0000FFA0-0000-1000-8000-00805F9B34FB"

//Characteristics UUIDs
//Smart Airway
#define CRICOID_CHARACTERISTIC_UUID "ffa1"
#define HEAD_NECK_CHARACTERISTIC_UUID "ffb1"
#define PRESSURE_CHARACTERISTIC_UUID "ffc1"
#define TEETH_CHARACTERISTIC_UUID "ffd1"
#define ERROR_CHARACTERISTIC_UUID "ffe0"
#define WIFI_IP_CHARACTERISTIC_UUID "faa0"
#define JAW_CHARACTERISTIC_UUID "faA1"
#define CREDENTIALS_CHARACTERISTIC_UUID "fac1"

//Descriptors UUIDs
//Smart Airway
#define CRICOID_DESCRIPTOR_UUID "2901"
#define HEAD_NECK_DESCRIPTOR_UUID "2901"
#define PRESSURE_DESCRIPTOR_UUID "2901"
#define TEETH_DESCRIPTOR_UUID "2901"
#define ERROR_DESCRIPTOR_UUID "2901"
#define WIFI_IP_DESCRIPTOR_UUID "2901"
#define JAW_DESCRIPTOR_UUID "2901"
#define CREDENTIALS_DESCRIPTOR_UUID "2901"


BLEService smartAirwayService(SMART_AIRWAY_SERVICE_UUID);

BLECharacteristic cricoidCharacteristic(CRICOID_CHARACTERISTIC_UUID, BLERead | BLENotify, 20);
BLEDescriptor cricoidDescriptor(CRICOID_DESCRIPTOR_UUID, "CRICOID FORCE");

BLECharacteristic headNeckCharacteristic(HEAD_NECK_CHARACTERISTIC_UUID, BLERead | BLENotify, 20);
BLEDescriptor headNeckDescriptor(HEAD_NECK_DESCRIPTOR_UUID, "HEAD POSITION");

BLECharacteristic pressureCharacteristic(PRESSURE_CHARACTERISTIC_UUID, BLERead | BLENotify, 20);
BLEDescriptor pressureDescriptor(PRESSURE_DESCRIPTOR_UUID, "TORSO PRESSURES");

BLECharacteristic teethCharacteristic(TEETH_CHARACTERISTIC_UUID, BLERead | BLENotify, 20);
BLEDescriptor teethDescriptor(TEETH_DESCRIPTOR_UUID, "TEETH FORCE");

BLECharacteristic errorCharacteristic(ERROR_CHARACTERISTIC_UUID, BLEWrite | BLERead | BLENotify, 20);
BLEDescriptor errorDescriptor(ERROR_DESCRIPTOR_UUID, "CONNECTION ERRORS");

BLECharacteristic wifiIPCharacteristic(WIFI_IP_CHARACTERISTIC_UUID, BLERead | BLENotify | BLEWrite, 20);
BLEDescriptor wifiIPDescriptor(WIFI_IP_DESCRIPTOR_UUID, "WIFI IP");

BLECharacteristic jawCharacteristic(JAW_CHARACTERISTIC_UUID, BLEWrite | BLERead | BLENotify, 20);
BLEDescriptor jawDescriptor(JAW_DESCRIPTOR_UUID, "JAW THRUST");

BLECharacteristic credentialsCharacteristic(CREDENTIALS_CHARACTERISTIC_UUID, BLEWrite | BLERead | BLENotify, 20);
BLEDescriptor credentialsDescriptor(CREDENTIALS_DESCRIPTOR_UUID, "WIFI CREDENTIALS");

#endif