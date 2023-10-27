#include "IPAddress.h"
#include <ESP8266mDNS.h>
#include "settings.h"
#include "oliwifi.h"


#define WIFI_RETRY_TIME (1 * 60 * 1000)
#define WIFI_CONNECT_TO (30000)

const char* oli_network  = "Verbonden aan het Oli WiFi netwerk ";
const char* home_network = "Verbonden aan het thuis netwerk ";


bool      mvAP_active  = false;
bool      mvSTA_active = false;
long int  mvConnectTime = 0;

void oliWiFiInit() {
  WiFi.mode(WIFI_AP_STA);

  if (MDNS.begin(oli_mdns)) {
    Serial.print(F("MDNS on: ")); Serial.print(oli_mdns); Serial.println(F(".local"));
  } else {
    Serial.println("MDNS not started");
  }  
  mvConnectTime = millis();
}

// Both STA and AP can be active. 
// The status returns STA if both are active.
const char * oliWiFigetStatus() {
  if (mvSTA_active == true) {
    return (home_network);
  } else {
    return (oli_network);
  }
}

const char * oliWiFigetSsid() {
  Serial.println("getSSID");

  if (WiFi.status() == WL_CONNECTED) {  
    return (mvUserSettings.userSSID);
  } else {
    Serial.println("kan niet goed werken");
    return("");
  }
}

String oliWiFigetIP() {
  Serial.println("getIP");
  if (WiFi.status() == WL_CONNECTED) {  
    return (WiFi.localIP().toString());
  } else {
    return (WiFi.softAPIP().toString());
  }
}

// If STA credentials are available try to connect to WiFi network else start AP mode
// If connection to WiFi network not possible start WiFi AP mode
// Repeat if connection to WiFi network is lost
// Repeat after WIFI_RETRY_MINUTES minutes
void oliWiFiHandleWiFi() {
  MDNS.update();

  if (mvAP_active==false && mvSTA_active==false) {
    // initial state
    Serial.println("Initial state");
    if (strlen(mvUserSettings.userSSID) != 0 && strlen(mvUserSettings.userPassword) != 0) {
      // STA credentials available
      Serial.println("STA credentials available");

      WiFi.begin(mvUserSettings.userSSID, mvUserSettings.userPassword);
      if (WiFi.waitForConnectResult(WIFI_CONNECT_TO) == WL_CONNECTED) {
        mvSTA_active = true;
        Serial.println("STA-active");
      } else {
        WiFi.softAP(oli_ssid, mvUserSettings.oliPassword);
        mvAP_active=true;
        Serial.println("AP-active");
      }
    } else {
      // STA credentials not available
      Serial.println("STA credentials not available");

      WiFi.softAP(oli_ssid, mvUserSettings.oliPassword);
      mvAP_active=true;      
      Serial.println("AP-active");
    }
  }

  if (mvAP_active==true && mvSTA_active==false) {

    if (strlen(mvUserSettings.userSSID) != 0 && strlen(mvUserSettings.userPassword) != 0) {

      if (SettingsUserChanged() == true) {
        Serial.println("STA credentials changed");
        Serial.println("STA credentials available");

        WiFi.begin(mvUserSettings.userSSID, mvUserSettings.userPassword);
        if (WiFi.waitForConnectResult(WIFI_CONNECT_TO) == WL_CONNECTED) {
          mvSTA_active = true;
          Serial.println("STA-active");
        } else {
          Serial.println("STA connect failed");
          if (mvAP_active == false) {
            WiFi.softAP(oli_ssid, mvUserSettings.oliPassword);
            mvAP_active=true;
            Serial.println("AP-active");
          }
        }
      }
    }

    if (millis() > mvConnectTime + WIFI_RETRY_TIME) {
      // TO
      Serial.println("TO-tje");

      mvConnectTime = millis();

      if (SettingsOliChanged() == true) {
        // stop and start AP
        Serial.println("Oli credentials changed");

        WiFi.softAPdisconnect(true);
        WiFi.softAP(oli_ssid, mvUserSettings.oliPassword);
      }

      if (strlen(mvUserSettings.userSSID) != 0 && strlen(mvUserSettings.userPassword) != 0) {
        // STA credentials available
        Serial.println("STA cedentials available");

        WiFi.begin(mvUserSettings.userSSID, mvUserSettings.userPassword);
        if (WiFi.waitForConnectResult(WIFI_CONNECT_TO) == WL_CONNECTED) {
          mvSTA_active = true;
          Serial.println("STA-active");
        } else {
          Serial.println("STA connect failed");
          if (mvAP_active == false) {
            WiFi.softAP(oli_ssid, mvUserSettings.oliPassword);
            mvAP_active=true;
            Serial.println("AP-active");
          }
        }
      }
    }
  }

  if (mvAP_active==true && mvSTA_active==true) {

    if (millis() - mvConnectTime >= WIFI_RETRY_TIME) {
      // TO
      Serial.println("TO");
      mvConnectTime = millis();

      WiFi.softAPdisconnect(true);
      mvAP_active = false;
      Serial.println("AP-deactive");
    }
  }

  if (mvSTA_active==true) {

    if (WiFi.status() != WL_CONNECTED || SettingsUserChanged() == true) {  
      Serial.println("STA connection lost or STA settings changed");

      WiFi.disconnect();
      mvSTA_active = false;
      Serial.println("STA-deactive");

      WiFi.begin(mvUserSettings.userSSID, mvUserSettings.userPassword);
      if (WiFi.waitForConnectResult(WIFI_CONNECT_TO) == WL_CONNECTED) {
        mvSTA_active = true;
        Serial.println("STA-active");
      } else {
        if (mvAP_active == false) {
          WiFi.softAP(oli_ssid, mvUserSettings.oliPassword);
          mvAP_active=true;
          Serial.println("AP-active");
        }
      }
    }
  }
}
