#include <DS1307RTC.h>    //must be on top... else you get crashing SW...
#include "ASetting.h"
#include "AWifi.h"
#include "webserver.h"
#include "ATime.h"
#include "secure.h"

void setDefaultSettings();

bool  mvUserSSIDChanged = false;
bool  mvUserPasswordChanged = false;
bool  mvClearSettings = false;


void setup() {
  Serial.begin(115200);
  while (!Serial) yield();
  delay(3000);  // if no delay, the output is not always visiblew on the serial monitor.
  Serial.println();

  if (ASettingInit() == false) {      // use default values if no values stored in EEPROM
    setDefaultSettings();
  }
  ASettingDump();
  Serial.println("Current settings: ");
  Serial.println(mvUserSettings.oliPassword);
  Serial.println(mvUserSettings.userSSID);
  Serial.println(mvUserSettings.userPassword);

  AWifiInit(OliMdns);
  AWifiSetOliCredentials(OliSSID, mvUserSettings.oliPassword);
  if (strlen(mvUserSettings.userSSID) != 0 && strlen(mvUserSettings.userPassword) != 0) {
    AWifiSetUserCredentials(mvUserSettings.userSSID ,mvUserSettings.userPassword);
  }

  webserverInit();
  ATimeInit();
}

void loop() {
  static bool lvTimeSync = false;

  if (Serial.parseInt() !=  0) {
    Serial.print(".");
  }

  AWifiHandleWiFi();

  if (mvUserSSIDChanged == true && mvUserPasswordChanged == true) {
    ASettingStore();
    AWifiSetUserCredentials(mvUserSettings.userSSID, mvUserSettings.userPassword);
    mvUserSSIDChanged = false;
    mvUserPasswordChanged = false;
    lvTimeSync = false;
  }

  if (mvClearSettings == true) {
    mvClearSettings = false;
    Serial.println("Now clear the settings");
    setDefaultSettings();
    AWifiSetOliCredentials(OliSSID, mvUserSettings.oliPassword);
    AWifiSetUserCredentials("", "");
    lvTimeSync = false;
  }
  // if NTP becomes available sync the RTC - do this once
  if (lvTimeSync == false) {
    lvTimeSync = ATimeSync();
  }
}

void setOliTime(const char* fpString) {
  Serial.print("set time: ");
  Serial.println(fpString);
  ATimeSetTime(fpString);
}

void setOliPassword(const char* fpString) {
  Serial.print("set Oli password: ");
  Serial.println(fpString);
  strcpy(mvUserSettings.oliPassword, fpString);
  ASettingStore();
  AWifiSetOliCredentials(OliSSID, mvUserSettings.oliPassword);
}

void setUserSSID(const char* fpString) {
  Serial.print("set WiFi SSID: ");
  Serial.println(fpString);
  strcpy(mvUserSettings.userSSID, fpString);
  mvUserSSIDChanged = true;
}

void setUserPassword(const char* fpString) {
  Serial.print("set WiFi password: ");
  Serial.println(fpString);
  strcpy(mvUserSettings.userPassword, fpString);
  mvUserPasswordChanged = true;
}

void clearSettings() {
  mvClearSettings = true;
  Serial.println("clear settings");
}

void setDefaultSettings() {
  strcpy(mvUserSettings.oliPassword, OliPwd);
  strcpy(mvUserSettings.userSSID, "");
  strcpy(mvUserSettings.userPassword, "");
  ASettingStore();
}
