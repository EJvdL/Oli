#ifndef A_LED_H
#define A_LED_H

#include "oli.h"
#include "FastLED.h"

#define NUM_ALL_LEDS  (8)
#define LED_TYPE      WS2812
#define COLOR_ORDER   GRB
#define BRIGHTNESS    (255)


typedef enum {
  oli_HW_error,
  oli_ota_error
} oli_error_t;

typedef enum {
  short_press,
  long_press,
  no_press
} oli_button_press_t;

void ALedInit();
void ALedOff();
void ALedSet(CRGB);
void ALedSetStatus(CRGB);
void ALedSetError(oli_error_t);
void ALedRainbow();
void ALedToggleLightsOff();
oli_button_press_t ALedPress();

#endif