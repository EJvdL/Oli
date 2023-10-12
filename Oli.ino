#include "webserver.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) yield();
  Serial.println();

  webserverInit();
  bool lvValidSettings = SettingsInit();
}

void loop() {}
