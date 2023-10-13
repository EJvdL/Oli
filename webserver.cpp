#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "webserver.h"
#include "secure.h"
#include "settings.h"

//Include the HTML, STYLE and Script "Pages"
#include "oli_config.h"
#include "oli_status.h"
#include "oli_scenarios.h"

#define WIFI_RETRY_TIME (5 * 60 * 1000)

AsyncWebServer server(80);
bool mvAP_active = false;

void startAP() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(oli_ssid, oli_password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  if (MDNS.begin(oli_mdns)) {
    Serial.print("MDNS on: "); Serial.print(oli_mdns); Serial.println(".local");
  }
}

// If STA credentials are available try to connect to WiFi network
// If connection not possible start WiFi AP mode for WIFI_RETRY_MINUTES minutes
// Repeat again and again....
void webserverHandleWiFi() {
  static long int lvDisconnectTime = millis() - WIFI_RETRY_TIME;

  if (mvUserSettings.wifiSettingsAvailable == true) {
    if (millis() - lvDisconnectTime >= WIFI_RETRY_TIME) {
      lvDisconnectTime = millis();
      WiFi.disconnect();

      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);

      if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi issue, going to AP");
        startAP();
        mvAP_active = true;
      } else {
        mvAP_active = false;
      }
    }
  } else {
    if (mvAP_active == false) {
      startAP();
      mvAP_active = true;
    }
  }
}

void submitConfig(AsyncWebServerRequest *request) {
  Serial.print("Method: ");
  Serial.println(request->method());
  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter *p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  }
  request->send_P(200, "text/html", PAGE_oli_status);
}

void submitScenario(AsyncWebServerRequest *request) {
  Serial.print("Method: ");
  Serial.println(request->method());
  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter *p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  }
  request->send_P(200, "text/html", PAGE_oli_status);
}

// Webserver will call this function whenever a variable %NAME% is found in the webpage.
// This function will replace the %NAME% by an actual value.
String processor(const String& var)
{
  Serial.println(var);
  if(var == "DATE_TIME"){
    return String("Dinsdag 12-10-2023 11:34");
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
  webserverHandleWiFi();

  // Configure and start webserver
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {

    request->send_P(200, "text/html", PAGE_oli_status, processor);
  });

  server.on("/scenarios", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", PAGE_oli_scenarios);
  });

  server.on("/submitConfig", HTTP_POST, submitConfig);
  server.on("/submitScenario", HTTP_POST, submitScenario);

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "The content you are looking for was not found.");
  });

  server.begin();
}