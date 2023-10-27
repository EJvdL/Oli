#include "settings.h"
#include "secure.h"

#define SETTINGS_SIGNATURE (0xAAAAAAAA)                  // repetitive bit pattern of 1010101010...

int mvEEAddress = 0;  // The structure with user preferences is stored at the first position in the EEPROM

UserSettings_t  mvUserSettings;
bool            mvUserSettingsChanged = false;
bool            mvOliSettingsChanged  = false;

void SettingsInit() {

#ifdef ESP8266
    EEPROM.begin(sizeof(UserSettings_t));                       // Initialise the EEPROM library
#endif
  
  EEPROM.get(mvEEAddress, mvUserSettings.signature);          // read the signature from EEPROM

  if (SettingsValid()) {                                      // Check if this value corresponds to the signature
    EEPROM.get(mvEEAddress, mvUserSettings);                  // if yes, trust the EEPROM content and read the values stored in EEPROM into the variable mvUserSettings
  } else {
    strcpy(mvUserSettings.oliPassword, oli_password);
//    mvUserSettings.wifiSettingsAvailable = false;
//    mvUserSettings.scenarioAvailable = false;
  }
}

bool SettingsStore() {
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
  mvUserSettingsChanged = true;
  mvOliSettingsChanged  = true;  
  for (int i = 0; i < EEPROM.length(); i++) { // write a 0 to all bytes of the EEPROM
    EEPROM.write(i, 255);
  }
#ifdef ESP8266
  return(EEPROM.commit());
#endif
#ifdef ARDUINO_AVR_PRO
  return (true);
#endif
}

bool SettingsValid() {
  int lvTemp;

  EEPROM.get(mvEEAddress, lvTemp);
  return(lvTemp == (int)SETTINGS_SIGNATURE);
}

void  SettingsDump() {
  Serial.println(F("--------------------"));
  
  Serial.print(F("EEPROM length: "));
  Serial.println(EEPROM.length());
  Serial.print("EEPROM content: ");
  for (int i = 0; i < EEPROM.length(); i++) {
    byte value = EEPROM.read(i);
    Serial.print(value, HEX);
    Serial.print(F(" "));  
  }
  Serial.println();
  Serial.println(F("--------------------"));
  Serial.print("Oli password:\t");
  Serial.println(mvUserSettings.oliPassword);
  Serial.print("SSID:\t");
  Serial.println(mvUserSettings.userSSID);
  Serial.print("Password:\t");
  Serial.println(mvUserSettings.userPassword);

}

void SettingsSetOliPassword(const char* fpOliPassword) {
  if (strcmp(fpOliPassword, mvUserSettings.oliPassword) != 0) {
    mvOliSettingsChanged = true;
    if (strlen(fpOliPassword) != 0) {
      strcpy(mvUserSettings.oliPassword, fpOliPassword);
    }
  }
}

void SettingsSetUserPassword(const char* fpUserPassword) {
  if (strcmp(fpUserPassword, mvUserSettings.userPassword) != 0) {
    mvUserSettingsChanged = true;
    if (strlen(fpUserPassword) != 0) {
      strcpy(mvUserSettings.userPassword, fpUserPassword);
    }
  }
}

void SettingsSetUserSSID(const char* fpUserSSID) {
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