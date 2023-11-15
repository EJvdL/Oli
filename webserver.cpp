#include <ESPAsyncWebServer.h>
#include "webserver.h"
#include "ASetting.h"
#include "AWifi.h"
#include "ATime.h"
#include "oli.h"
#include "ALed.h"

//Include the HTML, STYLE and Script "Pages"
#include "oli_config.h"
#include "oli_status.h"
#include "oli_scenarios.h"
#include "colorPicker.h"

AsyncWebServer server(80);
uint32_t mvPickedRGBColor = 0;  // Black

// TODO remove
// handle the submit button on the Oli Configuration page
// store the received name-value pairs into the user settings
// redirect the browser to the oli status webpage
void submitColor(AsyncWebServerRequest *request) {
  Serial.println("submitColor");
  Serial.println(request->args());

  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter *p = request->getParam(i);
    Serial.print(p->name().c_str());
    Serial.print("\t");
    Serial.println(p->value().c_str());
    if (strcmp(p->name().c_str(), "K10") == 0) {

      char lvStr[10];

      strcpy(lvStr, p->value().c_str());
      Serial.println(lvStr);
      if (strlen(lvStr) >= 7) {
        mvPickedRGBColor = strtoul((const char*)&lvStr[1], NULL, 16);   
        Serial.print("Color stored:\t");
        Serial.println(mvPickedRGBColor);
        ALedSet(mvPickedRGBColor);
      }
    }
  }
  request->redirect("/colorPicker");
}

// End TODO


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
        oliSetTime(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "oli-pwd") == 0) {
        //Serial.print("Change oli pwd:\t");
        //Serial.println(p->value().c_str());
        oliSetPassword(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "ssid") == 0) {
        //Serial.print("Change wifi ssid:\t");
        //Serial.println(p->value().c_str());
        oliSetUserSSID(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "pwd") == 0) {
        //Serial.print("Change wifi pwd:\t");
        //Serial.println(p->value().c_str());
        oliSetUserPassword(p->value().c_str());
      }

      if (strcmp(p->name().c_str(), "reset") == 0) {
        //Serial.print("Fabrieksinstellingen:\t");
        //Serial.println(p->value().c_str());
        oliClearSettings();
      }
    }
  }
//  if (ASettingsStore()) Serial.println("Store settings success");
  request->redirect("/status");
}

// handle the submit button on the Oli Scenario page
// Input from webpage tijd name:   <T><dag><trigger> 
//                    tijd value:  06:30
// Input from webpage kleur name:  <K><dag><trigger> 
//                    kleur value: #ff6600
//
// <dag>      : 0 = zondag, 1 = maandag.... 6 = zaterdag
// <trigger>  : 0-3 for the 4 triggers

void submitScenario(AsyncWebServerRequest *request) {
  int   lvWday, lvTrigger;
  char  lvStr[32];

  Serial.println("submitScenario");
  int params = request->params();

  for (int i = 0; i < params; i++) {
    AsyncWebParameter *p = request->getParam(i);
    // Serial.print(p->name().c_str());
    // Serial.print("\t");
    // Serial.println(p->value().c_str());

    // Parse the name field day and trigger#
    strcpy(lvStr, p->name().c_str());
    if (strlen(lvStr) >= 3) {

      char lvChar = lvStr[1];
      lvWday      = atoi(&lvChar);
      lvChar      = lvStr[2];
      lvTrigger   = atoi(&lvChar);

//      Serial.print("wday:\t\t");
//      Serial.println(lvWday);
//      Serial.print("trigger#:\t");
//      Serial.println(lvTrigger);
      
      if (lvStr[0] == 'T') {
        // Parse the value field e.g. '06:15'
        strcpy(lvStr, p->value().c_str());   
        if (strlen(lvStr) >= 5) {
          mvUserSettings.triggers[lvWday][lvTrigger].theHour   = (uint8_t)atoi(strtok((char*)lvStr, ":"));
          mvUserSettings.triggers[lvWday][lvTrigger].theMinute = (uint8_t)atoi(strtok(NULL, ":"));
//          Serial.print("Time stored:\t");
//          Serial.print(mvUserSettings.triggers[lvWday][lvTrigger].theHour);
//          Serial.print(":");
//          Serial.println(mvUserSettings.triggers[lvWday][lvTrigger].theMinute);
        }
      }

      if (lvStr[0] == 'K') {
        // Parse the value field, skip the leading '#'
        strcpy(lvStr, p->value().c_str());
Serial.println(lvStr);
        if (strlen(lvStr) >= 7) {
          mvUserSettings.triggers[lvWday][lvTrigger].theRGB   = strtoul((const char*)&lvStr[1], NULL, 16);   
Serial.print("Color stored:\t");
Serial.println(mvUserSettings.triggers[lvWday][lvTrigger].theRGB);
        }
      }
    } 
  }
  oliStoreScenarios();
  
  request->redirect("/status");
}

// The Oli Status webpage has some dynamic data to display.
// This data is encoded in the html page as e.g. %COLOR%
// The string %COLOR% must be replaced by the actual color of oli.
// This function is called by the webserver as we indicated that, see function webserverInit()
String processorStatus(const String &var) {
  if (var == "DATE_TIME") {
    return String(ATimeGetTime());
  } else if (var == "SSID") {
    return String(AWifiGetSSID());
  } else if (var == "IP") {
    return (AWifiGetIP());
  } return String();
}

// The Oli Scenario webpage has dynamic data to display.
// This data is encoded in the html page as e.g. %T01% meaning the time of trigger 0 (sunday), 2-nd trigger (1)
// The string %T01% must be replaced by the actual time configured.
// This function is called by the webserver as we indicated that, see function webserverInit()
String processorScenario(const String &var) {
  char  lvStr[32];
  strcpy(lvStr, var.c_str());

  if (strlen(var.c_str()) >= 3) {
    char lvChar     = lvStr[1];
    int lvWday      = atoi(&lvChar);
    lvChar          = lvStr[2];
    int lvTrigger   = atoi(&lvChar);

    if (lvStr[0] == 'T') {
        sprintf(lvStr, "%02d:%02d",mvUserSettings.triggers[lvWday][lvTrigger].theHour, mvUserSettings.triggers[lvWday][lvTrigger].theMinute);
//        Serial.println(lvStr);
        return (String(lvStr));
      }
      if (var[0] == 'K') {
//        Serial.println(mvUserSettings.triggers[lvWday][lvTrigger].theRGB);
        sprintf(lvStr, "#%06X", mvUserSettings.triggers[lvWday][lvTrigger].theRGB);
//        Serial.println(lvStr);
        return (String(lvStr));
      }
  }
  return(String(""));
}

// The Oli ColorPicker webpage has one dynamic data field to display.
// We always return the color value of the last picked color in the form #RRGGBB e.g. #E3FE00
// This function is called by the webserver as we indicated that, see function webserverInit()
String processorColor(const String &var) {
  char  lvStr[32];

  sprintf(lvStr, "#%06X", mvPickedRGBColor);
  return (String(lvStr));
}

void webserverInit() {

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("root");
    oliOnColorPicker(false);
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("/config");
    oliOnColorPicker(false);
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("/status");
    oliOnColorPicker(false);
    request->send_P(200, "text/html", PAGE_oli_status, processorStatus);        // the processor function replaces %NAME% by some value
  });

  server.on("/scenarios", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("/scenarios");
    oliOnColorPicker(false);
    request->send_P(200, "text/html", PAGE_oli_scenarios, processorScenario);
  });

  server.on("/colorPicker", HTTP_GET, [](AsyncWebServerRequest *request) {
    oliOnColorPicker(true);
    Serial.println("/colorPicker");
    request->send_P(200, "text/html", PAGE_oli_color, processorColor);
  });

  server.on("/submitConfig", HTTP_POST, submitConfig);
  server.on("/submitScenario", HTTP_POST, submitScenario);
  server.on("/submitColor", HTTP_POST, submitColor);

  server.onNotFound([](AsyncWebServerRequest *request) {
    oliOnColorPicker(false);
    Serial.print("URL not found:\t");
    Serial.println(request->url());
    Serial.println("With parameters:");
    int params = request->params();
    for (int i = 0; i < params; i++) {
      AsyncWebParameter *p = request->getParam(i);
      Serial.print(p->name().c_str());
      Serial.print("\t");
      Serial.println(p->value().c_str());
    }
    request->redirect("/status");
  });

  server.begin();
}
