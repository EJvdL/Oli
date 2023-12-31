#include <sys/_stdint.h>
#include "c_types.h"
#include "TimeLib.h"
/*
  ASetting.h - Library for storing user settings in flash memory.
  Created by E-J van der Linden, November, 2023.
  Released into the public domain.
*/
#ifndef ASETTING_H
#define ASETTING_H

#include "Arduino.h"
#include <EEPROM.h>                                           // used for storing user preferences in non-volatile memory     

bool  ASettingInit();
bool  ASettingStore();
bool  ASettingClear();
bool  ASettingValid();
void  ASettingDump();

#define MAX_SECURITY_LENGTH  (32 + 1)   // + 1 for the terminating \0

/*
  Structure to hold the user preferences. 
  These values can be modified by user interaction.
  It is stored in non-volatile EEPROM memory
*/
typedef struct UserTrigger {
  uint8_t  theHour;
  uint8_t  theMinute;
  uint32_t theRGB;
} user_trigger_t;

typedef struct UserSetting {
  int   signature;

  char  oliPassword[MAX_SECURITY_LENGTH];    
  char  userSSID[MAX_SECURITY_LENGTH];
  char  userPassword[MAX_SECURITY_LENGTH];

  user_trigger_t  triggers[7][4]; // 7 days with each day having 4 triggers

} UserSetting_t;

static_assert (sizeof(UserSetting_t) < 512, "Size of UserSetting_t too large");

extern UserSetting_t  mvUserSettings;                        // variable of type UserSettings_t holding the default or the EEPROM stored user settings

#endif