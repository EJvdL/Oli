#include <DS1307RTC.h>    //must be on top... else you get crashing SW
#include "oliwifi.h"
#include "oliTime.h"
#include "webserver.h"
#include "settings.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) yield();
//  delay(500);
  
  Serial.println();

  SettingsInit();
  SettingsDump();

  oliWiFiInit();
  webserverInit();
  oliTimeInit();
}


void loop() {
  static bool lvTimeSync = false;
  oliWiFiHandleWiFi();
  if (lvTimeSync == false) {
    lvTimeSync = oliTimeSync();
  }
}
