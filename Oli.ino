/*
To connect to the webserver
http://10.0.0.1/status
oli.local/status

HW error                15 x blink Red
OTA error               15 x blink Orange
Offline (AP mode)       Orange
Online  (STA mode)      Green
*/

#include <DS1307RTC.h>    //must be on top... else you get crashing SW...
#include "ASetting.h"
#include "AWifi.h"
#include "webserver.h"
#include "ATime.h"
#include "secure.h"
#include "ALed.h"
#include "A_OTA.h"

void initWiFi();
void initSettings();
void setDefaults();
void resetSettingsToDefault();

bool  mvUserSSIDChanged     = false;
bool  mvUserPasswordChanged = false;
bool  mvOliPasswordChanged  = false;
bool  mvClearSettings       = false;
bool  mvStoreScenarios      = false;
bool  mvOnColorPickerPage   = false;


void setup() {
  Serial.begin(115200);
  while (!Serial) yield();
  for (int i = 0; i < 6; i++) {       // if no delay, the output is not always visiblew on the serial monitor.
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  ALedInit();

  initSettings();
  initWiFi();
  webserverInit();

  if (ATimeInit() == false) {
    ALedSetError(oli_HW_error);
  }
  A_OTAInit();  
}

void loop() {
  static bool lvTimeSync = false;

  if (Serial.parseInt() !=  0) {    // can be used to check if main-loop still runs if web-interface is locked
    Serial.print(".");
  }

  if (AWifiHandleWiFi() == true) {  // Sync again if  a STA connection is made
    lvTimeSync = false;
  }

  A_OTAHandleOTA();

  // if NTP becomes available sync the RTC - do this once
  if (lvTimeSync == false) {
    lvTimeSync = ATimeSync();
  }

  if (mvOnColorPickerPage == false) {
    checkTriggers();
  }

  // handle webserver triggers
  if (mvOliPasswordChanged == true) {
    if (ASettingStore() == false) {
      Serial.println("Oli Password not saved");
    }
    AWifiSetOliCredentials(OliSSID, mvUserSettings.oliPassword);
    mvOliPasswordChanged  = false;  
  }
  
  if (mvUserSSIDChanged == true && mvUserPasswordChanged == true) {
    if (ASettingStore() == false) {
      Serial.println("SSID not saved");
    }
    AWifiSetUserCredentials(mvUserSettings.userSSID, mvUserSettings.userPassword);
    mvUserSSIDChanged     = false;
    mvUserPasswordChanged = false;
  }

  if (mvClearSettings == true) {
    Serial.println("Now clear the settings");
    resetSettingsToDefault();
    AWifiSetOliCredentials(OliSSID, mvUserSettings.oliPassword);
    AWifiSetUserCredentials(mvUserSettings.userSSID, mvUserSettings.userPassword);
    mvClearSettings = false;
  }
  
  if (mvStoreScenarios == true) {
    mvStoreScenarios = false;
    if (ASettingStore() == false) {
      Serial.println("Scenario not stored");
    }
  }

  if (AWifiGetAPState() == true) { //AP-mode
    ALedSetStatus(CRGB::Orange);
  } else {  // STA mode
      ALedSetStatus(CRGB::Green);
  }
}

// Callback from webserver, must be short
void oliSetTime(const char* fpString) {
  Serial.print("set time: ");
  Serial.println(fpString);
  ATimeSetTime(fpString);
}

// Callback from webserver, must be short
void oliSetPassword(const char* fpString) {
  Serial.print("set Oli password: ");
  Serial.println(fpString);
  strcpy(mvUserSettings.oliPassword, fpString);
  mvOliPasswordChanged = true;
}

// Callback from webserver, must be short
void oliSetUserSSID(const char* fpString) {
  Serial.print("set WiFi SSID: ");
  Serial.println(fpString);
  strcpy(mvUserSettings.userSSID, fpString);
  mvUserSSIDChanged = true;
}

// Callback from webserver, must be short
void oliSetUserPassword(const char* fpString) {
  Serial.print("set WiFi password: ");
  Serial.println(fpString);
  strcpy(mvUserSettings.userPassword, fpString);
  mvUserPasswordChanged = true;
}

// Callback from webserver, must be short
void oliClearSettings() {
  mvClearSettings = true;
  Serial.println("clear settings");
}

// Callback from webserver, must be short
void oliStoreScenarios() {
  // sort the list of triggers on increasing time
  for (int i = 0; i < 7; i++) {   // sunday to saturday
    for (int j = 0; j < 4 - 1; j++) {
      if ((mvUserSettings.triggers[i][j].theHour * 60 + mvUserSettings.triggers[i][j].theMinute) > (mvUserSettings.triggers[i][j + 1].theHour * 60 + mvUserSettings.triggers[i][j + 1].theMinute)) {
        uint8_t  lvHour    = mvUserSettings.triggers[i][j].theHour;
        uint8_t  lvMinute  = mvUserSettings.triggers[i][j].theMinute;
        uint32_t lvRGB     = mvUserSettings.triggers[i][j].theRGB;
        mvUserSettings.triggers[i][j].theHour   = mvUserSettings.triggers[i][j + 1].theHour;
        mvUserSettings.triggers[i][j].theMinute = mvUserSettings.triggers[i][j + 1].theMinute;
        mvUserSettings.triggers[i][j].theRGB    = mvUserSettings.triggers[i][j + 1].theRGB;
        mvUserSettings.triggers[i][j + 1].theHour   = lvHour;
        mvUserSettings.triggers[i][j + 1].theMinute = lvMinute;
        mvUserSettings.triggers[i][j + 1].theRGB    = lvRGB;
        j = 0;
      }
    }
  }  
  mvStoreScenarios = true;
}

// Callback from webserver, must be short
void oliOnColorPicker(bool fpOnOliPage){
  mvOnColorPickerPage = fpOnOliPage;
}

void initWiFi() {
  AWifiInit(OliMdns);
  AWifiSetOliCredentials(OliSSID, mvUserSettings.oliPassword);
  if (strlen(mvUserSettings.userSSID) != 0 && strlen(mvUserSettings.userPassword) != 0) {
    AWifiSetUserCredentials(mvUserSettings.userSSID ,mvUserSettings.userPassword);
  }
}

void initSettings() {
  if (ASettingInit() == false) {      // use default values if no values stored in EEPROM
    setDefaults();
  }
  ASettingDump();                     //dump EEPROm values
  Serial.println("Current settings: ");
  Serial.println(mvUserSettings.oliPassword);
  Serial.println(mvUserSettings.userSSID);
  Serial.println(mvUserSettings.userPassword);
}

void setDefaults() {
  strcpy(mvUserSettings.oliPassword, OliPwd);
  strcpy(mvUserSettings.userSSID, "");
  strcpy(mvUserSettings.userPassword, "");

  for (int i = 0; i < 7; i++) {   // sunday to saturday
    mvUserSettings.triggers[i][0].theHour   = 6;        // 06:15
    mvUserSettings.triggers[i][0].theMinute = 15;
    mvUserSettings.triggers[i][0].theRGB    = 0x664000; // Orange

    mvUserSettings.triggers[i][1].theHour   = 6;        // 06:30
    mvUserSettings.triggers[i][1].theMinute = 30;
    mvUserSettings.triggers[i][1].theRGB    = 0x048400; // Green

    mvUserSettings.triggers[i][2].theHour   = 8;        // 08:00
    mvUserSettings.triggers[i][2].theMinute = 0;
    mvUserSettings.triggers[i][2].theRGB    = 0x000000; // Black

    mvUserSettings.triggers[i][3].theHour   = 19;       // 19:00
    mvUserSettings.triggers[i][3].theMinute = 0;
    mvUserSettings.triggers[i][3].theRGB    = 0xE632D2; // Purple 
  }
}

void resetSettingsToDefault() {
  setDefaults();
  if (ASettingStore() == false) {
    Serial.println("Default settings not saved");
  }
  ASettingDump();
}

void checkTriggers() {
  trigger_time_t  lvTriggerTime = ATimeGetBrokenTime();

  // convert hour/minute in an integer (60*hour + minute) to get easier comparison
  int lvNow = 60 * lvTriggerTime.theHour + lvTriggerTime.theMinute;

  // Check the triggers of the current day
  int lvT1 = 60 * mvUserSettings.triggers[lvTriggerTime.theDay][0].theHour + mvUserSettings.triggers[lvTriggerTime.theDay][0].theMinute;
  int lvT2 = 60 * mvUserSettings.triggers[lvTriggerTime.theDay][1].theHour + mvUserSettings.triggers[lvTriggerTime.theDay][1].theMinute;
  int lvT3 = 60 * mvUserSettings.triggers[lvTriggerTime.theDay][2].theHour + mvUserSettings.triggers[lvTriggerTime.theDay][2].theMinute;
  int lvT4 = 60 * mvUserSettings.triggers[lvTriggerTime.theDay][3].theHour + mvUserSettings.triggers[lvTriggerTime.theDay][3].theMinute;

  if (lvNow < lvT1) {
    ALedSet(mvUserSettings.triggers[lvTriggerTime.theDay][3].theRGB);
  }

  if (lvNow >= lvT1 && lvNow < lvT2) {
    ALedSet(mvUserSettings.triggers[lvTriggerTime.theDay][0].theRGB);
  }

  if (lvNow >= lvT2 && lvNow < lvT3) {
    ALedSet(mvUserSettings.triggers[lvTriggerTime.theDay][1].theRGB);
  }

  if (lvNow >= lvT3 && lvNow < lvT4) {
    ALedSet(mvUserSettings.triggers[lvTriggerTime.theDay][2].theRGB);
  }

  if (lvNow >= lvT4) {
    ALedSet(mvUserSettings.triggers[lvTriggerTime.theDay][3].theRGB);
  }
}

