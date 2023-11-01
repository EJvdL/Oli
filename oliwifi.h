#ifndef OLIWIFI_H
#define OLIWIFI_H

#include "secure.h"

void  oliWiFiInit();
void  oliWiFiHandleWiFi();
const char * oliWiFigetStatus();
const char * oliWiFigetSsid();
String oliWiFigetIP();

#endif