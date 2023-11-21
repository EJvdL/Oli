#include "ALed.h"

#define NUM_LEDS (NUM_ALL_LEDS - 1)

#define SHORT_PRESS (250)
#define MAX_SHORT_PRESS (1000)
#define LONG_PRESS (5000)
#define MAX_LONG_PRESS (10000)

CRGB mvAllLEDs[NUM_LEDS];
CRGB* mvStatusLED = &mvAllLEDs[0];
CRGB* mvLEDs = &mvAllLEDs[1];

bool mvLightsOff = false;
CRGB mvStatusValue = CRGB::Black;

// forward function declaration
int buttonPress();

void ALedInit() {
  pinMode(INPUT_SWITCH_PIN, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // switch off the builtin LED, switch on the LED in the switch

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
  if (mvLightsOff == false) {
    FastLED.show();
    FastLED.show();
  }
}

void ALedSetStatus(CRGB fpRGB) {
  mvStatusValue = fpRGB;
  *mvStatusLED = mvStatusValue;
  if (mvLightsOff == false) {
    FastLED.show();
    FastLED.show();
  }
}

void ALedSetError(oli_error_t fpError) {
  CRGB lvPrevColor = *mvStatusLED;
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
  if (mvLightsOff == false) {
    FastLED.show();
    FastLED.show();
  }
}

void ALedToggleLightsOff() {
  mvLightsOff = !mvLightsOff;
  if (mvLightsOff == true) {
    digitalWrite(LED_BUILTIN, LOW);
    ALedOff();
    ALedSetStatus(CRGB::Black);
    FastLED.show();
    FastLED.show();
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    ALedSetStatus(mvStatusValue);
    FastLED.show();
    FastLED.show();
  }
}

/*
  Button presses are POLLED
  Functions must be called regularly for the corerect detection of button presses
*/

oli_button_press_t ALedPress() {
  oli_button_press_t lvReturn = no_press;

  int lvTimePressed = buttonPress();

  if (lvTimePressed > SHORT_PRESS && lvTimePressed < MAX_SHORT_PRESS) {
    lvReturn = short_press;
  }

  if (lvTimePressed > LONG_PRESS && lvTimePressed < MAX_LONG_PRESS) {
    lvReturn = long_press;
  }

  return lvReturn;
}

int buttonPress() {
  static unsigned long lvLastPress = millis();
  static bool lvWaitForRelease = false;
  int lvTime = 0;

  bool lvState = digitalRead(INPUT_SWITCH_PIN);

  lvTime = 0;
  if (lvState == true) {  // switched released
    if (lvWaitForRelease == true) {
      lvTime = millis() - lvLastPress;
      lvLastPress = millis();
      lvWaitForRelease = false;
    }
  } else {
    if (lvWaitForRelease == false) {
      lvWaitForRelease = true;
      lvLastPress = millis();
    }
  }
  return (lvTime);
}