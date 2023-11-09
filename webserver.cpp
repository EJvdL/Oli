//#include "oliTime.h"
#include <ESPAsyncWebServer.h>
#include "webserver.h"
#include "ASetting.h"
#include "AWifi.h"
#include "ATime.h"
#include "oli.h"

//Include the HTML, STYLE and Script "Pages"
#include "oli_config.h"
#include "oli_status.h"
#include "oli_scenarios.h"

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
        //Serial.print("Set date&Time:\t");
        //Serial.println(p->value().c_str());
        setOliTime(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "oli-pwd") == 0) {
        //Serial.print("Change oli pwd:\t");
        //Serial.println(p->value().c_str());
        setOliPassword(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "ssid") == 0) {
        //Serial.print("Change wifi ssid:\t");
        //Serial.println(p->value().c_str());
        setUserSSID(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "pwd") == 0) {
        //Serial.print("Change wifi pwd:\t");
        //Serial.println(p->value().c_str());
        setUserPassword(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "reset") == 0) {
        //Serial.print("Fabrieksinstellingen:\t");
        //Serial.println(p->value().c_str());
        clearSettings();
      }
    }
  }
//  if (ASettingsStore()) Serial.println("Store settings success");
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
  Serial.println("ToDo: store user settings");
  
  request->redirect("/status");
}

// The Oli Status webpage has some dynamic data to display.
// This data is encoded in the html page as e.g. %COLOR%
// The string %COLOR% must be replaced by the actual color of oli.
// This function is called by the webserver as we indicated that, see function webserverInit()
String processor(const String &var) {

  if (var == "DATE_TIME") {
    return String(ATimeGetTime());
  } else if (var == "SSID") {
    return String(AWifiGetSSID());
  } else if (var == "IP") {
    return (AWifiGetIP());
  } else if (var == "COLOR") {
    return String("Huidige kleur: Rood - echte kleur weergeven in RGB?");
  } else if (var == "INTENSITEIT") {
    return String("Intensiteit: 50%");
  }
  return String();
}

void webserverInit() {

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("root");
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("/config");
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("/status");
    request->send_P(200, "text/html", PAGE_oli_status, processor);        // the processor function replaces %NAME% by some value
//    request->send_P(200, "text/html", PAGE_oli_status);                 // the processor function replaces %NAME% by some value
  });

  server.on("/scenarios", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("/scenarios");
    request->send_P(200, "text/html", PAGE_oli_scenarios);
  });

  server.on("/submitConfig", HTTP_POST, submitConfig);
  server.on("/submitScenario", HTTP_POST, submitScenario);

  server.onNotFound([](AsyncWebServerRequest *request) {
    Serial.println("Not found");
    request->redirect("/status");
  });

  server.begin();
}
