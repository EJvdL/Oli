#include <ESPAsyncWebServer.h>
#include "webserver.h"
#include "settings.h"
#include "rtc.h"
#include "oliwifi.h"

//Include the HTML, STYLE and Script "Pages"
#include "oli_config.h"
#include "oli_status.h"
#include "oli_scenarios.h"
#include "oli_redirect.h"

AsyncWebServer server(80);



// handle the submit button on the Oli Configuration page
// store the received name-value pairs into the user settings
// redirect the browser to the oli status webpage
void submitConfig(AsyncWebServerRequest *request) {

  Serial.println("submitConfig");
  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter *p = request->getParam(i);

    if (strlen(p->value().c_str()) != 0) {
      if (strcmp(p->name().c_str(), "datetime") == 0) {
        Serial.print("Set date&Time:\t");
        Serial.println(p->value().c_str());
        //       // rtcSetTime(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "oli-pwd") == 0) {
        Serial.print("Change oli pwd:\t");
        Serial.println(p->value().c_str());
        //strcpy(mvUserSettings.oliPassword, p->value().c_str());
        SettingsSetOliPassword(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "ssid") == 0) {
        Serial.print("Change wifi ssid:\t");
        Serial.println(p->value().c_str());
        //        strcpy(mvUserSettings.userSSID, p->value().c_str());
        SettingsSetUserSSID(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "pwd") == 0) {
        Serial.print("Change wifi pwd:\t");
        Serial.println(p->value().c_str());
        //        strcpy(mvUserSettings.userPassword, p->value().c_str());
        SettingsSetUserPassword(p->value().c_str());
      }
    }
  }
  SettingsStore();
  request->redirect("/status");
}

// handle the submit button on the Oli Scenario page

void submitScenario(AsyncWebServerRequest *request) {
  Serial.println("submitScenario");
  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter *p = request->getParam(i);
    Serial.print(p->name().c_str());
    Serial.print("\t");
    Serial.println(p->value().c_str());
    // Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  }
  //Serial.println("ToDo: store user settings");
  SettingsStore();

  request->redirect("/status");
}

// The Oli Status webpage has some dynamic data to display.
// This data is encoded in the html page as e.g. %COLOR%
// The string %COLOR% must be replaced by the actual color of oli.
// This function is called by the webserver as we indicated that, see function webserverInit()
String processor(const String &var) {
  Serial.print("processor: ");

  if (var == "DATE_TIME") {
    return String(rtcGetTime());
  } else if (var == "CONNECTED_TO") {
    return String(oliWiFigetStatus());
  } else if (var == "SSID") {
    return String(oliWiFigetSsid());
  } else if (var == "IP") {
    return (oliWiFigetIP());
  } else if (var == "COLOR") {
    Serial.println("Kleur");
    return String("Huidige kleur: Rood - echte kleur weergeven in RGB?");
  } else if (var == "INTENSITEIT") {
    Serial.println("Intensiteit");
    return String("Intensiteit: 50%");
  }
  return String();
}

void webserverInit() {

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    //    request->send_P(200, "text/html", PAGE_oli_status, processor);        // the processor function replaces %NAME% by some value
    request->send_P(200, "text/html", PAGE_oli_status);  // the processor function replaces %NAME% by some value
  });

  server.on("/scenarios", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", PAGE_oli_scenarios);
  });

  server.on("/submitConfig", HTTP_POST, submitConfig);
  server.on("/submitScenario", HTTP_POST, submitScenario);

  server.on("/redirect", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", PAGE_oli_redirect);
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->redirect("/status");
  });

  server.begin();
}