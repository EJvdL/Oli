#include "rtc.h"
#include "Arduino.h"
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char mvDateTime[11];

void rtcInit() {
  if (! rtc.begin()) {
      Serial.println(F("Couldn't find RTC"));
      Serial.println(F("LEDs aanzetten of blijven hangen?"));
      Serial.flush();
//      while (1) delay(10););
  }
}

void rtcSetTime(const char *iso8601dateTime){
  Serial.println(F("Enable rtc code"));
  Serial.println(iso8601dateTime);
//    rtc.adjust(DateTime(iso8601dateTime));
}

char* rtcGetTime() {
  DateTime lvNow;

  Serial.println("Enable rtc code");
  //lvNow = rtc.now();

  sprintf(mvDateTime, "%s %d-%d-%d %d:%d", daysOfTheWeek[lvNow.dayOfTheWeek()], lvNow.day(), lvNow.month(), lvNow.year(), lvNow.hour(), lvNow.minute());
  return mvDateTime;
}

void rtcDumpTime() {
  DateTime lvNow;
  Serial.println(F("Enable rtc code"));
//  lvNow = rtc.now();

  Serial.print(lvNow.year(), DEC);
  Serial.print(F("/"));
  Serial.print(lvNow.month(), DEC);
  Serial.print(F("/"));
  Serial.print(lvNow.day(), DEC);
  Serial.print(F(" ("));
  Serial.print(daysOfTheWeek[lvNow.dayOfTheWeek()]);
  Serial.print(F(" ("));
  Serial.print(lvNow.hour(), DEC);
  Serial.print(F(":"));
  Serial.print(lvNow.minute(), DEC);
  Serial.print(F(":"));
  Serial.print(lvNow.second(), DEC);
  Serial.println();  
}