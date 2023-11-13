#ifndef ALED_H
#define ALED_H

#include "FastLED.h"

#define NUM_ALL_LEDS  (8)
#define DATA_PIN  (D3)
#define LED_TYPE  WS2812

// typedef enum {
//   purple,
//   yellow,
//   green,
//   off
// } myColor_t;

typedef enum {
  noError,          // off
  rtcError,         // red
  defaultConfig,    // Orange
  STAConnected      // Green
} oli_error_t;


void ALedInit();
void ALedError(oli_error_t);
void ALedOff();
void ALedSet(CRGB lvRGB);

#endif