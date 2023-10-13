#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <EEPROM.h>                                           // used for storing user preferences in non-volatile memory     
#include <FastLED.h>
#include "RTClib.h"

#define MAX_SECURITY_LENGTH  (32)

/*
  Structure to hold the user preferences. 
  These values can be modified by user interaction.
  It is stored in non-volatile EEPROM memory
*/
typedef struct UserSettings {
  int   signature;

  char  oliPassword[MAX_SECURITY_LENGTH + 1];    // + 1 for the terminating \0

  bool  wifiSettingsAvailable;
  char  userSSID[MAX_SECURITY_LENGTH + 1];
  char  userPassword[MAX_SECURITY_LENGTH + 1];
  
  bool  scenarioAvailable;
  // monday scenario
  DateTime  maTijd1;
  CRGB      maKleur1;
  byte      maInt1;
  DateTime  maTijd2;
  CRGB      maKleur2;
  byte      maInt2;
  DateTime  maTijd3;
  CRGB      maKleur3;
  byte      maInt3;
  DateTime  maTijd4;

  // tuseday scenario
  DateTime  diTijd1;
  CRGB      diKleur1;
  byte      diInt1;
  DateTime  diTijd2;
  CRGB      diKleur2;
  byte      diInt2;
  DateTime  diTijd3;
  CRGB      diKleur3;
  byte      diInt3;
  DateTime  diTijd4;

  // wednesday sceanrio
  DateTime  woTijd1;
  CRGB      woKleur1;
  byte      woInt1;
  DateTime  woTijd2;
  CRGB      woKleur2;
  byte      woInt2;
  DateTime  woTijd3;
  CRGB      woKleur3;
  byte      woInt3;
  DateTime  woTijd4;

  // thursday sceanrio
  DateTime  doTijd1;
  CRGB      doKleur1;
  byte      doInt1;
  DateTime  doTijd2;
  CRGB      doKleur2;
  byte      doInt2;
  DateTime  doTijd3;
  CRGB      doKleur3;
  byte      doInt3;
  DateTime  doTijd4;

  // friday sceanrio
  DateTime  vrTijd1;
  CRGB      vrKleur1;
  byte      vrInt1;
  DateTime  vrTijd2;
  CRGB      vrKleur2;
  byte      vrInt2;
  DateTime  vrTijd3;
  CRGB      vrKleur3;
  byte      vrInt3;
  DateTime  vrTijd4;

  // saturday sceanrio
  DateTime  zaTijd1;
  CRGB      zaKleur1;
  byte      zaInt1;
  DateTime  zaTijd2;
  CRGB      zaKleur2;
  byte      zaInt2;
  DateTime  zaTijd3;
  CRGB      zaKleur3;
  byte      zaInt3;
  DateTime  zaTijd4;

  // sundayday sceanrio
  DateTime  zoTijd1;
  CRGB      zoKleur1;
  byte      zoInt1;
  DateTime  zoTijd2;
  CRGB      zoKleur2;
  byte      zoInt2;
  DateTime  zoTijd3;
  CRGB      zoKleur3;
  byte      zoInt3;
  DateTime  zoTijd4;

} UserSettings_t;

extern UserSettings_t  mvUserSettings;                        // variable of type UserSettings_t holding the default or the EEPROM stored user settings

bool SettingsInit();
bool SettingsStore();
bool SettingsClear();
bool SettingsValid();
#endif