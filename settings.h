#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <EEPROM.h>                                           // used for storing user preferences in non-volatile memory     

/*
  Structure to hold the user preferences. 
  These values can be modified by user interaction.
  It is stored in non-volatile EEPROM memory
*/
typedef struct UserSettings {
  int   signature;
  int   tempMin;
  int   tempMax;
  byte  pwmMin;
  byte  pwmMax;
//  byte  dutyCycle;                                            // 0 - 100%
  int   measurementInterval;                                  // in seconds
} UserSettings_t;

extern UserSettings_t  mvUserSettings;                        // variable of type UserSettings_t holding the default or the EEPROM stored user settings

bool SettingsInit();
bool SettingsStore();
bool SettingsClear();
bool SettingsValid();
#endif