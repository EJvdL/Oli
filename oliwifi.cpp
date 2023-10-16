#include "user_interface.h"
#include "settings.h"
#include "oliwifi.h"

#define WIFI_RETRY_TIME (5 * 60 * 1000)

bool      mvAP_active  = false;
bool      mvSTA_active = false;
long int  mvConnectTime = millis() - WIFI_RETRY_TIME;


void oliWiFiStopAP() {
  if (mvAP_active == true) {
    Serial.println(F("Stop AP-mode"));
    WiFi.softAPdisconnect(true);
    WiFi.disconnect();
    mvAP_active = false;
  }
}

void oliWiFiStopSTA() {
  if (mvSTA_active == true) {
    Serial.println(F("Stop STA-mode"));
    WiFi.disconnect();
    mvSTA_active = false;
  }
}

void oliWiFiStartAP() {
  Serial.println(F("Start AP-mode"));
  WiFi.mode(WIFI_AP);
  WiFi.softAP(oli_ssid, mvUserSettings.oliPassword);

  IPAddress IP = WiFi.softAPIP();
  Serial.print(F("AP IP address: "));
  Serial.println(IP);

  if (MDNS.begin(oli_mdns)) {
    Serial.print(F("MDNS on: ")); Serial.print(oli_mdns); Serial.println(F(".local"));
  }
  Serial.println(F("AP-mode"));
  mvAP_active = true;
}

void oliWiFiStartSTA() {
  Serial.println(F("Start STA-mode"));
  WiFi.mode(WIFI_STA);
  WiFi.begin(mvUserSettings.userSSID, mvUserSettings.userPassword);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println(F("STA connect failed"));
    mvSTA_active = false;
    oliWiFiStartAP();
    mvConnectTime = millis();    //startTimer
  } else {
    Serial.println(F("STA-mode"));
    mvSTA_active = true;
  }
}

// If STA credentials are available try to connect to WiFi network else start AP mode
// If connection to WiFi network not possible start WiFi AP mode for WIFI_RETRY_MINUTES minutes
// If connection to WiFi network is lost, reconnect
// Repeat again and again....
void oliWiFiHandleWiFi() {

  // case: STA
  if (mvSTA_active == true) {
    if (WiFi.status() != WL_CONNECTED) {  
      oliWiFiStopSTA();
      oliWiFiStartSTA();
    } else {
      //stay in STA mode
    }
  }

  // case AP
  if (mvAP_active == true) {
    if (mvUserSettings.wifiSettingsAvailable == true) {
      oliWiFiStopAP();
      oliWiFiStartSTA();
    } else {
      // stay in AP mode
    }
  }

  // case unconnected
  if (mvSTA_active == false && mvAP_active == false) {
    if (mvUserSettings.wifiSettingsAvailable == true) {
      oliWiFiStartSTA();
    } else { 
      oliWiFiStartAP();
    }
  }
  
  // case Time Out
  if (millis() - mvConnectTime >= WIFI_RETRY_TIME) {
    mvConnectTime = millis();
    if (mvAP_active == true) {
      oliWiFiStartSTA();
    }
  }
}
