/*
  ATime.cpp - Library for managing NTP and an external RTC for a specific Timezone.
  Created by E-J van der Linden, November, 2023.
  Released into the public domain.
*/

// Timezone info: http://www.hs-help.net/hshelp/gira/v4_7/en/proj_tz.html
//
#include <DS1307RTC.h> // is now also included in the main file, else system crashes
#include "ATime.h"
#include <TZ.h> 
#include <Timezone.h>

#define MAX_TIME_STR  (32)
TimeChangeRule myDST = {"CED", Last, Sun, Mar, 2, +120};      // Daylight time = UTC + 2 hours
TimeChangeRule mySTD = {"CES", Last, Sun, Oct, 3, +60};       // Standard time = UTC + 1 hour
Timezone myLocalTimezone(myDST, mySTD);
char mvTimeStr[MAX_TIME_STR];                      // format: 19 Jan 2023 08:59\0

void initNTP();
bool initRTC();
time_t ntpTime();
bool validNTPTime();

bool ATimeInit() {
  initNTP();
  return (initRTC());
}

// To be called now and then....
// Syncs the RTC to the NTP if NTP is present
bool ATimeSync() {
  bool lvResult = false;

  if (validNTPTime() == true) {
    time_t lvRTCNow    = RTC.get();
    time_t lvSystemNow = ntpTime();
    if(lvSystemNow != lvRTCNow) {
      lvResult = RTC.set(ntpTime());
      if (lvResult == true) {
        Serial.println("Sync RTC time to NTP");
        
        Serial.print("NTP unix time:\t");
        Serial.println(lvSystemNow);

        Serial.print("RTC unix time:\t");
        Serial.println(lvRTCNow);
      } else {
        Serial.println("Failed to set RTC time");
      }
    } else {
      lvResult = true;
      Serial.println("RTC in sync with NTP");
    }
  } else {
    //    Serial.println("no NTP");
  }
  return (lvResult);
}

// format of fpString: 2023-11-08T16:09
void ATimeSetTime(const char* fpString) {
  struct tm lvTimeStruct;
  char lvTemp[10];
//  Serial.println(fpString);
  lvTimeStruct.tm_year  = atoi(strncpy(lvTemp, fpString +  0, 4)) - 1900;
  memset(lvTemp, 0, 10);
  lvTimeStruct.tm_mon   = atoi(strncpy(lvTemp, fpString +  5, 2)) - 1;
  lvTimeStruct.tm_mday  = atoi(strncpy(lvTemp, fpString +  8, 2));
  lvTimeStruct.tm_hour  = atoi(strncpy(lvTemp, fpString + 11, 2));
  lvTimeStruct.tm_min   = atoi(strncpy(lvTemp, fpString + 14, 2));
  lvTimeStruct.tm_sec = 0;
  time_t lvUnixTime = mktime(&lvTimeStruct);
  lvUnixTime = myLocalTimezone.toUTC(lvUnixTime);
  RTC.set(lvUnixTime);
}

char* ATimeGetTime() {
  TimeChangeRule *tcr;                      // pointer to the time change rule used, use it to get the TZ abbrev

  time_t lvNow = RTC.get();
  lvNow = myLocalTimezone.toLocal(lvNow, &tcr);
  
  struct tm* lvTmStruct = localtime(&lvNow);
  strftime(mvTimeStr, MAX_TIME_STR, "%A %d %b %Y %H:%M", lvTmStruct);
  return(mvTimeStr);
//  return ctime(&lvNow);
}

void ATimeDumpTime() {
  Serial.println(ATimeGetTime());
}

trigger_time_t ATimeGetBrokenTime() {
  TimeChangeRule  *tcr;                      // pointer to the time change rule used, use it to get the TZ abbrev
  trigger_time_t  lvTriggerTime;

  time_t lvNow = RTC.get();
  lvNow = myLocalTimezone.toLocal(lvNow, &tcr);
  struct tm* lvTmStruct = localtime(&lvNow);
  lvTriggerTime.theDay = lvTmStruct->tm_wday;
  lvTriggerTime.theHour = lvTmStruct->tm_hour;
  lvTriggerTime.theMinute = lvTmStruct->tm_min;
  
  return (lvTriggerTime);
}

void initNTP() {
  Serial.println("Start NTP ");

  const char* ntpServer  = "pool.ntp.org";
  #define UTC_TIMEZONE  TZ_Etc_Universal
  #ifdef ARDUINO_ARCH_ESP32
     configTzTime(UTC_TIMEZONE, ntpServer);
  #else
     configTime(UTC_TIMEZONE, ntpServer);
  #endif
}

bool initRTC() {
  bool lvResult = false;
  tmElements_t  tm;

  if (RTC.read(tm) == true) {
    lvResult = true;
  } else {
    if (RTC.chipPresent() == true) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();      
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();      
    }
  }
  return (lvResult);
}

// return the systemtime set by NTP, NTP sets the systemtime automatically
time_t ntpTime() {
  return(time(nullptr));
}

bool validNTPTime() {
  #define NTP_MIN_VALID_EPOCH 1533081600  // August 1st, 2018

  bool lvResult = false;

  if (ntpTime() > NTP_MIN_VALID_EPOCH) {
    lvResult = true;
  }
  return lvResult;
}