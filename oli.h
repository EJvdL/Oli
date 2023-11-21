#ifndef OLI_H
#define OLI_H

// Pin usage
  // RTC pins 
  // SCL  D1
  // SDA  D2
  
  // LED pins
  #define POWER_LED         (LED_BUILTIN) // = D4
  #define ALED_DATA_PIN     (D3)

  // Input switch pin
  #define INPUT_SWITCH_PIN  (D5)

void oliSetTime(const char* fpString);
void oliSetPassword(const char* fpString);
void oliSetUserSSID(const char* fpString);
void oliSetUserPassword(const char* fpString);
void oliClearSettings();
void oliStoreScenarios();
void oliOnColorPicker(bool);

#endif