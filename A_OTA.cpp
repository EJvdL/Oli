#include "A_OTA.h"
#include "secure.h"
#include <ArduinoOTA.h>


void A_OTAInit(){
  pinMode(LED_BUILTIN, OUTPUT);
  ArduinoOTA.setHostname(OliHostname);

  ArduinoOTA.onStart([]() {
    Serial.println("Start over the air update");
    digitalWrite(LED_BUILTIN, LOW);  // switch on led
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("end of over the air update");
    for (int i = 0; i < 1024; i++) {
      analogWrite(LED_BUILTIN, i);  //fade-off LED
      delay(2);
    }
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.print("Error occured during over the air update:\t");
    Serial.println(error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }    
    for(int i = 0; i < 5; i++) {
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);                      // wait for a second
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      delay(1000);                      // wait for a second
    }
    (void)error;
    ESP.restart();
  });

  ArduinoOTA.begin();
}

void A_OTAHandleOTA(){
  ArduinoOTA.handle();
}