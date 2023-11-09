/*
  ATime.h - Library for managing NTP and an external RTC for a specific Timezone.
  Created by E-J van der Linden, November, 2023.
  Released into the public domain.
*/
#ifndef ATime_H
#define ATime_H


void ATimeInit();
bool ATimeSync();
void ATimeSetTime(const char*);

char* ATimeGetTime();
void  ATimeDumpTime();

#endif
