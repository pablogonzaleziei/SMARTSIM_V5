# SMARTSIM V5
This code is made in VScode with Platformio. Check platformio.ini to check/add libraries and the settings of the board (nRF52_dk)

## CODE
### At 04/2023 the code includes:
- main.cpp. Main code for Smart Airway (Adult, Child, Baby and Difficult)
- ble_uuids.h: This library includes all the Services, Characteristics and Descriptor UUIDs for any Electronic proyect. It can be use for CPR adding a new UUID (avoiding having duplicate UUIDs)
- smartairway.cpp/.h (on development): includes functions and classes for all sensors and features.
    - Check smartairway.h for an overall of the classes and its functions and variables.
- systemSetup.cpp/.h (on development): manage model selection, errors and BLE connection (?)

 
## PCB
For this code we are using the nordic chipset nRF52xxx (currently nRF52832).

## Notes about nRF52 and ESP32
- ESP32 can include OTA over WIFI.
- OTA over BLE with nRF52 needs Zephyr implementation
- Using ESP32 can potentially improve the comunication with camera board (as it uses an ESP32)
- Issues found using certain analog inputs on ESP32. This needs to be checked
- Both can be programmed with platformio or using their own platform (ESP-IDF and nRFconnect)

## FUTURE APROACH
- smarairway.cpp/.h can be reused for smart CPR using the classes needed.
- ble_uuids.h can be used in both projects to keep track of the UUIDS used. The UUIDS can be changed using a proper generator.
- Code needs to be independent of the sensor used. smartairway library will include all the alternatives but main.cpp should remain the same.
 

