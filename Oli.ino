#include "rtc.h"
#include "oliwifi.h"
#include "webserver.h"
#include "settings.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) yield();
  delay(500);
  
  Serial.println();

  rtcInit();

  SettingsInit();
  SettingsDump();

  oliWiFiInit();
  webserverInit();
}

void loop() {
  oliWiFiHandleWiFi();
}
