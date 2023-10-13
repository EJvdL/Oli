#include "webserver.h"
#include "settings.h"


void setup() {
  Serial.begin(115200);
  while (!Serial) yield();
  Serial.println();

  bool lvValidSettings = SettingsInit();
  webserverInit();
}

void loop() {
  MDNS.update();
  webserverHandleWiFi();
}
