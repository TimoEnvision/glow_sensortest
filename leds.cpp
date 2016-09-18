#include "Arduino.h"
#include "Leds.h"

#include "FastLED.h"

#define numLeds 10// Data pin that led data will be written out over

#define DATA_PIN 7// This is an array of leds.  One item for each led in your strip.

CRGB ledArray[numLeds];

Leds::Leds() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(ledArray, numLeds);

  FastLED.setMaxPowerInVoltsAndMilliamps(5,5000);
}

void Leds::lightFromPCB() {
    for(int i = 0; i < numLeds; i ++){
      ledArray[i] = CRGB::Red;
      //delay(6);
      FastLED.show();
      fadeToBlackBy(ledArray,numLeds,25);
    }
}

void Leds::lightFromMid() {
    for(int i = 0; i < numLeds; i ++){
      ledArray[numLeds/2 - i/2] = CRGB::Red;
      ledArray[numLeds/2 + i/2] = CRGB::Red;
      //delay(6);
      FastLED.show();
      fadeToBlackBy(ledArray,numLeds,25);
    }
}
  
void Leds::lightFromFarSide() {
    for(int i = 0; i < numLeds; i ++){
      ledArray[numLeds - i] = CRGB::Red;
      //delay(6);
      FastLED.show();
      fadeToBlackBy(ledArray,numLeds,25);
    }
}

void Leds::update(uint32_t touchState) {
    switch(touchState){
    case 0:
      fadeToBlackBy(ledArray,numLeds,5);
      FastLED.show();
      break;
    case 1:
      lightFromPCB();
      break;
    case 2:
      lightFromMid();
      break;
    case 3:
      lightFromFarSide();
      break;
    default:
      Serial.println("Unknown Mode!");
      //delay(1000);
      break;
    }
}
