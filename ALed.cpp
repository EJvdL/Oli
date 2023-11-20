#include "pixeltypes.h"
// https://fastled.io/docs/index.html

#include "ALed.h"

CHSV mvPurple = CHSV(184, 170, 200);
CHSV mvOrange = CHSV(40, 255, 200);
CHSV mvGreen = CHSV(133, 170, 200);
CHSV mvRed = CHSV(0, 255, 200);
CHSV mvBlack = CHSV(0, 0, 0);


#define NUM_LEDS (NUM_ALL_LEDS - 1)

CRGB mvAllLEDs[NUM_LEDS];

CRGB* mvStatusLED = &mvAllLEDs[0];
CRGB* mvLEDs = &mvAllLEDs[1];

void ALedInit() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   // switch off the builtin LED

  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(mvAllLEDs, NUM_ALL_LEDS);
  FastLED.setBrightness(3);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 250);  // FastLED power management set at 5V, 250mA

  ALedSetStatus(CRGB::Black);

  fill_rainbow(mvLEDs, NUM_LEDS, 0, 20);  // Show initial rainbow
  FastLED.show();
  FastLED.show();
}

void ALedOff() {
  fill_solid(mvLEDs, NUM_LEDS, mvBlack);
  FastLED.show();
  FastLED.show();
}

void ALedSet(CRGB fpRGB) {
  fill_solid(mvLEDs, NUM_LEDS, fpRGB);
  FastLED.show();
  FastLED.show();
}

void ALedSetStatus(CRGB fpRGB) {
  *mvStatusLED = fpRGB;
  FastLED.show();
  FastLED.show();
}

void ALedSetError(oli_error_t fpError) {
  CRGB  lvPrevColor = *mvStatusLED;
  switch (fpError) {
    case (oli_HW_error):
      {
        for (int i = 0; i < 15; i++) {
          ALedSetStatus(CRGB::Red);
          delay(500);
          ALedSetStatus(CRGB::Black);
          delay(500);
        }
        break;
      }
    case (oli_ota_error):
      {
        for (int i = 0; i < 15; i++) {
          ALedSetStatus(CRGB::Orange);
          delay(500);
          ALedSetStatus(CRGB::Black);
          delay(500);
        }
        break;
      }
  }
}