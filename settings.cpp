#include "Settings.h"

#define SETTINGS_SIGNATURE (0xAAAAAAAA)                  // repetitive bit pattern of 1010101010...

int mvEEAddress = 0;  // The structure with user preferences is stored at the first position in the EEPROM

UserSettings_t mvUserSettings;

bool SettingsInit() {
  bool lvReturn = false;

#ifdef ESP8266
    EEPROM.begin(sizeof(UserSettings_t));                       // Initialise the EEPROM library
#endif

  // EEPROM of a new device can have random data stored in it
  EEPROM.get(mvEEAddress, mvUserSettings.signature);          // read the signature from EEPROM
  if (SettingsValid()) {                                      // Check if this value corresponds to the signature
    EEPROM.get(mvEEAddress, mvUserSettings);                  // if yes, trust the EEPROM content and read the values stored in EEPROM into the variable mvUserSettings
    lvReturn = true;
  }
  return (lvReturn);
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
