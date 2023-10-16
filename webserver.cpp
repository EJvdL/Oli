#include <ESPAsyncWebServer.h>
#include "webserver.h"
#include "settings.h"
#include "rtc.h"
#include "oliwifi.h"

//Include the HTML, STYLE and Script "Pages"
#include "oli_config.h"
#include "oli_status.h"
#include "oli_scenarios.h"

AsyncWebServer server(80);

// handle the submit button on the Oli Configuration page
// store the received name-value pairs into the user settings
// redirect the browser to the oli status webpage 
void submitConfig(AsyncWebServerRequest *request) {
  bool lvStopAP = false;

  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter *p = request->getParam(i);

    if (strlen(p->value().c_str()) != 0) {
      if (strcmp(p->name().c_str(), "datetime") == 0) {
        rtcSetTime(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "oli-pwd") == 0) {
        strcpy(mvUserSettings.oliPassword, p->value().c_str());
        lvStopAP = true;
      }

      if (strcmp(p->name().c_str(), "ssid") == 0) {
        strcpy(mvUserSettings.userSSID, p->value().c_str());
        mvUserSettings.wifiSettingsAvailable = true;
      }

      if (strcmp(p->name().c_str(), "pwd") == 0) {
        strcpy(mvUserSettings.userPassword, p->value().c_str());
        mvUserSettings.wifiSettingsAvailable = true;
      }    
    }
    yield();
//   Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  }

  request->redirect("/status");
  for (int i = 0; i < 500; i++) {
    delay(1); 
    yield();            // make sure the WiFi SW does not timeout
  }                     // make sure the reply is send before the AP is stopped
  
  if (lvStopAP == true) {
    oliWiFiStopAP();
  }
  oliWiFiHandleWiFi();
}

// handle the submit button on the Oli Scenario page

void submitScenario(AsyncWebServerRequest *request) {
  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter *p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  }
  request->redirect("/status");
}

// The Oli Status webpage has some dynamic data to display.
// This data is encoded in the html page as e.g. %COLOR%
// The string %COLOR% must be replaced by the actual color of oli.
// This function is called by the webserver as we indicated that, see function webserverInit()
String processor(const String& var)
{
  if(var == "DATE_TIME"){
    return String(rtcGetTime());
  } else if (var == "CONNECTED_TO") {
    return String("Verbonden aan het SSID van het thuis netwerk &nbsp;&nbsp;&nbsp;&nbsp; OF &nbsp;&nbsp;&nbsp;&nbsp;Verbonden via het Oli WiFi netwerk");
  } else if (var == "COLOR") {
    return String("Huidige kleur: Rood - echte kleur weergeven in RGB?");
  } else if (var == "INTENSITEIT") {
    return String("Intensiteit: 50%");
  }
  return String();
}

void webserverInit() {
  oliWiFiHandleWiFi();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {

    request->send_P(200, "text/html", PAGE_oli_status, processor);        // the processor function replaces %NAME% by some value
  });

  server.on("/scenarios", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", PAGE_oli_scenarios);
  });

  server.on("/submitConfig", HTTP_POST, submitConfig);
  server.on("/submitScenario", HTTP_POST, submitScenario);

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->redirect("/status");
  });

  server.begin();
}