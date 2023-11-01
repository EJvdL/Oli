#include "settings.h"
#include "secure.h"

#define SETTINGS_SIGNATURE (0xAAAAAAAA)                  // repetitive bit pattern of 1010101010...

int mvEEAddress = 0;  // The structure with user preferences is stored at the first position in the EEPROM

UserSettings_t  mvUserSettings;
bool            mvUserSettingsChanged = false;
bool            mvOliSettingsChanged  = false;

void SettingsInit() {
  Serial.println("SettingsInit");

#ifdef ESP8266
    EEPROM.begin(sizeof(UserSettings_t));                       // Initialise the EEPROM library
#endif
  
  EEPROM.get(mvEEAddress, mvUserSettings.signature);          // read the signature from EEPROM

  if (SettingsValid()) {                                      // Check if this value corresponds to the signature
    EEPROM.get(mvEEAddress, mvUserSettings);                  // if yes, trust the EEPROM content and read the values stored in EEPROM into the variable mvUserSettings
  } else {
    strcpy(mvUserSettings.oliPassword, oli_password);
  }
}

bool SettingsStore() {
  Serial.println("SettingsStore");
  mvUserSettings.signature = SETTINGS_SIGNATURE;              // save the data with our signature
  EEPROM.put(mvEEAddress, mvUserSettings);                    // save new data in EEPROM, put only updates the bytes that differ from the bytes already in EEPROM

#ifdef ESP8266
  return(EEPROM.commit());
#endif
#ifdef ARDUINO_AVR_PRO
  return (true);
#endif
}

bool SettingsClear() {
  Serial.println("SettingsClear");

  bool lvResult = false;
  
  Serial.println("Clear user settings");
  // clear the user settings
  memset(&mvUserSettings, 0, sizeof(UserSettings_t));

  // Initialise user settings
  strcpy(mvUserSettings.oliPassword, oli_password);

  // Indicate we have changed credentials
  mvUserSettingsChanged = true;
  mvOliSettingsChanged  = true;

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
  SettingsDump();
  return (lvResult);
}

bool SettingsValid() {
  int lvTemp;

  EEPROM.get(mvEEAddress, lvTemp);
  return(lvTemp == (int)SETTINGS_SIGNATURE);
}

void  SettingsDump() {
  Serial.println(F("--------------------"));
  
  Serial.print(F("EEPROM length:\t"));
  Serial.println(EEPROM.length());
  Serial.print("EEPROM content:\t");
  for (int i = 0; i < EEPROM.length(); i++) {
    byte value = EEPROM.read(i);
    Serial.print(value, HEX);
    Serial.print(F(" "));  
  }
  Serial.println();
  Serial.print("Oli password:\t");
  Serial.println(mvUserSettings.oliPassword);
  Serial.print("SSID:\t\t");
  Serial.println(mvUserSettings.userSSID);
  Serial.print("Password:\t\t");
  Serial.println(mvUserSettings.userPassword);
  Serial.println(F("--------------------"));
}

void SettingsSetOliPassword(const char* fpOliPassword) {
//  Serial.println("SettingsSetOliPassword");

  if (strcmp(fpOliPassword, mvUserSettings.oliPassword) != 0) {
    mvOliSettingsChanged = true;
    if (strlen(fpOliPassword) != 0) {
      strcpy(mvUserSettings.oliPassword, fpOliPassword);
    }
  }
}

void SettingsSetUserPassword(const char* fpUserPassword) {
//  Serial.println("SettingsSetUserPassword");
  
  if (strcmp(fpUserPassword, mvUserSettings.userPassword) != 0) {
    mvUserSettingsChanged = true;
    if (strlen(fpUserPassword) != 0) {
      strcpy(mvUserSettings.userPassword, fpUserPassword);
    }
  }
}

void SettingsSetUserSSID(const char* fpUserSSID) {
//  Serial.println("SettingsSetUserSSID");
  
  if (strcmp(fpUserSSID, mvUserSettings.userSSID) != 0) {
    mvUserSettingsChanged = true;
    if (strlen(fpUserSSID) != 0) {
      strcpy(mvUserSettings.userSSID, fpUserSSID);
    }
  }
}

bool SettingsUserChanged() {
  if (mvUserSettingsChanged == true) {
   mvUserSettingsChanged = false;
    return (true);
  } else {
    return (false);
  }
}

bool SettingsOliChanged() {
  if (mvOliSettingsChanged == true) {
   mvOliSettingsChanged = false;
    return (true);
  } else {
    return (false);
  }
}
