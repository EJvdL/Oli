#ifndef OLIWIFI_H
#define OLIWIFI_H

#include "secure.h"

void  oliWiFiInit();
void  oliWiFiHandleWiFi();
// void  oliWiFiStartAP();
// void  oliWiFiStopAP();
// void  oliWiFiStartSTA();
// void  oliWiFiStopSTA();
const char * oliWiFigetStatus();
const char * oliWiFigetSsid();
String oliWiFigetIP();

#endif