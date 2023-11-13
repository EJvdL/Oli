// https://fastled.io/docs/index.html 

#include "ALed.h"

CHSV mvPurple = CHSV(184, 170, 200);
CHSV mvOrange = CHSV(40,  255, 200);
CHSV mvGreen  = CHSV(133, 170, 200);
CHSV mvRed    = CHSV(0,   255, 200);
CHSV mvBlack  = CHSV(0,   0,   0);


#define NUM_LEDS   (NUM_ALL_LEDS - 1)

CRGB mvAllLEDs[NUM_LEDS];

CRGB* mvStatusLED = &mvAllLEDs[0];
CRGB* mvLEDs = &mvAllLEDs[1];

void ALedInit() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(mvAllLEDs, NUM_ALL_LEDS);
  FastLED.setBrightness(5);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 250);             // FastLED power management set at 5V, 250mA

  *mvStatusLED = mvRed;

  fill_rainbow(mvLEDs, NUM_LEDS, 0, 20);                      // Show initial rainbow
  FastLED.show();
  FastLED.show();
}

void ALedOff() {
  fill_solid(mvLEDs, NUM_LEDS, mvBlack);
  FastLED.show();
  FastLED.show();
}

void ALedSet(CRGB lvRGB){
  fill_solid(mvLEDs, NUM_LEDS, lvRGB);
  FastLED.show();
  FastLED.show();
}

void ALedError(oli_error_t fpError) {
  Serial.println("Error handling NOG AF TE MAKEN!!!!");
  switch (fpError) {
    case (rtcError):
      {
        *mvStatusLED = CRGB::Red;
        break;
      }

    case (defaultConfig):
      {
        *mvStatusLED = CRGB::Orange;
        break;
      }

    case (noError):
    default:
      {
        *mvStatusLED = CRGB::Black;
        break;
      }
    }
}