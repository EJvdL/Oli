#ifndef RTC_H
#define RTC_H

#include "RTClib.h"

void rtcInit();
void rtcSetTime(const char *iso8601dateTime);
char* rtcGetTime();
void rtcDumpTime();

#endif
