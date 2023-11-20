/*
  AWifi.h - Library for handling WiFi AP and STA modes.
  Created by E-J van der Linden, November, 2023.
  Released into the public domain.
*/
#ifndef AWIFI_H
#define AWIFI_H

#include "Arduino.h"

#define MAX_CREDENTIAL_LENGTH (32 + 1)    // +1 for the terminating null character
void  AWifiInit(const char*);
void  AWifiSetOliCredentials (const char*, const char*);
void  AWifiSetUserCredentials(const char*, const char*);
bool  AWifiHandleWiFi();
const char * AWifiGetSSID();
String AWifiGetIP();
bool AWifiGetAPState();

// only for unit testing purposes
extern long int  mvConnectTime;

#endif