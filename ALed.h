#ifndef A_LED_H
#define A_LED_H

#include "oli.h"
#include "FastLED.h"

#define NUM_ALL_LEDS  (8)
#define LED_TYPE  WS2812

typedef enum {
  oli_HW_error,
  oli_ota_error
} oli_error_t;

void ALedInit();
void ALedOff();
void ALedSet(CRGB);
void ALedSetStatus(CRGB);
void ALedSetError(oli_error_t);
void ALedRainbow();
bool ALedLongPress();

#endif