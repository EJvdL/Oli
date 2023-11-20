#include "ALed.h"

#define NUM_LEDS        (NUM_ALL_LEDS - 1)
#define DEBOUNCE_TIME   (5000)

CRGB mvAllLEDs[NUM_LEDS];

CRGB* mvStatusLED = &mvAllLEDs[0];
CRGB* mvLEDs = &mvAllLEDs[1];

void ALedInit() {
  pinMode(INPUT_SWITCH, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   // switch off the builtin LED

  FastLED.addLeds<WS2812, ALED_DATA_PIN, GRB>(mvAllLEDs, NUM_ALL_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(3);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 250);  // FastLED power management set at 5V, 250mA

  ALedSetStatus(CRGB::Black);
  ALedRainbow();
}

void ALedOff() {
  fill_solid(mvLEDs, NUM_LEDS, CRGB::Black);
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
void ALedRainbow() {
  fill_rainbow(mvLEDs, NUM_LEDS, 0, 20);  // Show initial rainbow
  FastLED.show();
  FastLED.show();
}

bool ALedLongPress() {
  static unsigned long lvLastPress = 0;
  static bool lvWaitForTrigger = true;
  bool lvReturn = false;

  bool lvState = digitalRead(INPUT_SWITCH);
  if (lvState == true) {    // switched released
    lvWaitForTrigger = true;
    lvLastPress = millis();
  } else {
    if (lvWaitForTrigger == true && 
        ((millis() - lvLastPress) > DEBOUNCE_TIME)) {
      lvWaitForTrigger = false;
      lvReturn = true;
    }
  }
  return lvReturn;
}