/*
  ATime.h - Library for managing NTP and an external RTC for a specific Timezone.
  Created by E-J van der Linden, November, 2023.
  Released into the public domain.
*/
#ifndef ATime_H
#define ATime_H

typedef struct Trigger_time {
  uint8_t  theDay;
  uint8_t  theHour;
  uint8_t  theMinute;
} trigger_time_t;

bool ATimeInit();
bool ATimeSync();
void ATimeSetTime(const char*);

char* ATimeGetTime();
void  ATimeDumpTime();

trigger_time_t ATimeGetBrokenTime();

#endif
