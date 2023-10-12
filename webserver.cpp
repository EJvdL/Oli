#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "webserver.h"
#include "secure.h"

//Include the HTML, STYLE and Script "Pages"
#include "oli_config.h"
#include "oli_status.h"
#include "oli_scenarios.h"

AsyncWebServer server(80);

void submitConfig(AsyncWebServerRequest *request) {
  Serial.print("Method: ");
  Serial.println(request->method());
  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter* p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  }
  request->send_P(200, "text/html", PAGE_oli_status);
}


void webserverInit() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi issue");
    while (true) yield();
  }

  Serial.println();
  Serial.print("Connect to: http://"); Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", PAGE_oli_config);
  });
  
  server.on("/config", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", PAGE_oli_config);
  });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", PAGE_oli_status);
  });  

  server.on("/scenarios", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", PAGE_oli_scenarios);
  });

  server.on("/submitConfig", HTTP_POST, submitConfig);
  
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "The content you are looking for was not found.");
  });

  server.begin();
}