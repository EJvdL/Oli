/*
  ASetting.cpp - Library for storing user settings in flash memory.
  Created by E-J van der Linden, November, 2023.
  Released into the public domain.
*/
#include "ASetting.h"

#define SETTING_SIGNATURE (0xAAAAAAAA)                  // repetitive bit pattern of 1010101010...

int mvEEAddress = 0;  // The structure with user preferences is stored at the first position in the EEPROM

UserSetting_t  mvUserSettings;

/*
  ASettingInit()
  */
bool ASettingInit() {
//  Serial.println("SettingInit");
bool lvResult = false;

#ifdef ESP8266
    EEPROM.begin(sizeof(UserSetting_t));                       // Initialise the EEPROM library
#endif
  
  EEPROM.get(mvEEAddress, mvUserSettings.signature);          // read the signature from EEPROM

  if (ASettingValid()) {                                      // Check if this value corresponds to the signature
    EEPROM.get(mvEEAddress, mvUserSettings);                  // if yes, trust the EEPROM content and read the values stored in EEPROM into the variable mvUserSettings
    lvResult = true;
  } else {
    // clear the user settings
    memset(&mvUserSettings, 0, sizeof(UserSetting_t));    
  }
  return (lvResult);
}

/*
  ASettingStore()
  False if error occurred
  */
bool ASettingStore() {
//  Serial.println("SettingStore");
  mvUserSettings.signature = SETTING_SIGNATURE;              // save the data with our signature
  EEPROM.put(mvEEAddress, mvUserSettings);                   // save new data in EEPROM, put only updates the bytes that differ from the bytes already in EEPROM

#ifdef ESP8266
  return(EEPROM.commit());
#endif
#ifdef ARDUINO_AVR_PRO
  return (true);
#endif
}

/*
  ASettingClear()
  */
bool ASettingClear() {
//  Serial.println("SettingClear");

  bool lvResult = false;
  
  // clear the user settings
  memset(&mvUserSettings, 0, sizeof(UserSetting_t));

  // clear the EPROM
  for (int i = 0; i < EEPROM.length(); i++) { // write a 0 to all bytes of the EEPROM
    EEPROM.write(i, 255);
  }
#ifdef ESP8266
  lvResult = EEPROM.commit();
#endif
#ifdef ARDUINO_AVR_PRO
  lvResult = true;
#endif
//  ASettingDump();
  return (lvResult);
}

/*
  ASettingValid()
  */
bool ASettingValid() {
  int lvTemp;

//  Serial.println("SettingValid");
  EEPROM.get(mvEEAddress, lvTemp);
  return(lvTemp == (int)SETTING_SIGNATURE);
}

/*
  ASettingDump()
  */
void  ASettingDump() {
  Serial.println(F("--------------------"));
  
  Serial.print(F("EEPROM length:\t"));
  Serial.println(EEPROM.length());
  Serial.print("EEPROM content:\t");
  for (int i = mvEEAddress; i < mvEEAddress + EEPROM.length(); i++) {
    if (i % 16 == 0) Serial.println(); 
    byte value = EEPROM.read(i);
    char buffer[3];
    sprintf (buffer, "%02X", value);
    Serial.print(buffer);
    Serial.print(F(" ")); 
  }
  Serial.println();
  Serial.println(F("--------------------"));
}
