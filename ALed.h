#ifndef ALED_H
#define ALED_H

#include "FastLED.h"

#define NUM_ALL_LEDS  (8)
#define DATA_PIN  (D3)
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

#endif