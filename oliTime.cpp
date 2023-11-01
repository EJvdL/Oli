#include "oliTime.h"

#include <TZ.h> 

#include <DS1307RTC.h>
#include <Timezone.h>

TimeChangeRule myDST = {"CED", Last, Sun, Mar, 2, +120};      // Daylight time = UTC + 2 hours
TimeChangeRule mySTD = {"CES", Last, Sun, Oct, 2, +60};       // Standard time = UTC + 1 hour
Timezone myLocalTimezone(myDST, mySTD);


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

void oliTimeInit() {
  initNTP();
  if (initRTC() == false) {
    while (true) {
      Serial.println("RTC init failed");
      delay(10000);
    }
  }
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

void oliTimeSync() {
  if (validNTPTime() == true) {
    time_t lvRTCNow    = RTC.get();
    time_t lvSystemNow = ntpTime();
    if(lvSystemNow != lvRTCNow) {
      RTC.set(ntpTime());

      Serial.println("Sync RTC time to NTP");
      
      Serial.print("NTP unix time:\t");
      Serial.println(lvSystemNow);

      Serial.print("RTC unix time:\t");
      Serial.println(lvRTCNow);
    } else {
//      Serial.println("RTC in sync with NTP");
    }
  } else { 
    Serial.println("no NTP");
  }  
}

char* oliTimeGetTime() {
  TimeChangeRule *tcr;                      // pointer to the time change rule, use to get TZ abbrev

  time_t lvNow = RTC.get();
  lvNow = myLocalTimezone.toLocal(lvNow, &tcr);

  return ctime(&lvNow);
}

void oliTimeDumpTime() {
  Serial.println(oliTimeGetTime());
}
