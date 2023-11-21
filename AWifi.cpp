#include "wl_definitions.h"
/*
  AWifi.cpp - Library for handling WiFi AP and STA modes.
  Created by E-J van der Linden, November, 2023.
  Released into the public domain.
*/

#include "AWifi.h"
#include "IPAddress.h"
#include <ESP8266mDNS.h>

#define WIFI_RETRY_TIME       (1 * 60 * 1000)

char  mvOliSSID[MAX_CREDENTIAL_LENGTH];    
char  mvOliPwd[MAX_CREDENTIAL_LENGTH];    

char  mvWifiSSID[MAX_CREDENTIAL_LENGTH];
char  mvWifiPwd[MAX_CREDENTIAL_LENGTH];

bool      mvAP_active   = false;
bool      mvInit        = false;
long int  mvConnectTime = 0;

void AWifiInit(const char* fpMdns) {
  mvInit = true;

  WiFi.mode(WIFI_AP_STA);

  IPAddress lvLocal_IP(192,168,4,1);
  IPAddress lvSubnetMask(255,255,255,0);
  WiFi.softAPConfig (lvLocal_IP, lvLocal_IP, lvSubnetMask);

  if (MDNS.begin(fpMdns)) {
    Serial.print(F("MDNS on: ")); Serial.print(fpMdns); Serial.println(F(".local"));
  } else {
    Serial.println("MDNS not started");
  }
}

void  AWifiSetOliCredentials(const char* fpSSID, const char* fpPwd){
  if (strlen(fpPwd) != 0 && strlen(fpSSID) != 0) {
    strcpy(mvOliSSID, fpSSID);
    strcpy(mvOliPwd, fpPwd);
    WiFi.softAPdisconnect(true);
    WiFi.softAP(mvOliSSID, mvOliPwd);
    mvAP_active = true;
    Serial.println("AP-active");
  }
}

void  AWifiSetUserCredentials(const char* fpSSID, const char* fpPwd){
  strcpy(mvWifiSSID,fpSSID);
  strcpy(mvWifiPwd, fpPwd);

  // start with new credentials
  if (strlen(fpSSID) != 0 && strlen(fpPwd) != 0) {
    WiFi.disconnect();
    WiFi.begin(mvWifiSSID, mvWifiPwd);
    Serial.println("STA-active");
  } else {
    Serial.println("stop-STA");
    WiFi.disconnect();
  }
}

// If STA credentials are available try to connect to WiFi network else start AP mode
// If connection to WiFi network not possible start WiFi AP mode
// Repeat if connection to WiFi network is lost
// Repeat after WIFI_RETRY_MINUTES minutes
// Return true if STA connection is established
bool AWifiHandleWiFi() {
  bool lvResult = false;

  if (mvInit == true) {
    MDNS.update();

    if (mvAP_active == false && WiFi.status() != WL_CONNECTED) {
      WiFi.softAP(mvOliSSID, mvOliPwd);
      mvAP_active = true;
      Serial.println("Start-AP want STA not connected, cancel timer if running");
      mvConnectTime = 0;    // stop possibly running timer
    }

    if (mvAP_active == true && WiFi.status() == WL_CONNECTED) {
      mvConnectTime = millis() + WIFI_RETRY_TIME;   // start timer
      mvAP_active = false;
      Serial.println("STA active. Keep AP-active for a while, start timer to disable AP");
    }

    if (millis() > mvConnectTime && mvConnectTime != 0) {
      Serial.println("TO");
      WiFi.softAPdisconnect(true);
      Serial.println("Stop-AP");
      mvAP_active = false;
      mvConnectTime = 0;  // stop the timer
      lvResult = true;    // STA is stable and available
    }
  }
  return (lvResult);
}

bool AWifiGetAPState() {
  return (mvAP_active);
}

const char * AWifiGetSSID() {
  if (mvAP_active != true) {  
    return (mvWifiSSID);
  } else {
    return(mvOliSSID);
  }
}

String AWifiGetIP() {
  if (mvAP_active != true) {  
    return (WiFi.localIP().toString());
  } else {
    return (WiFi.softAPIP().toString());
  }
}
