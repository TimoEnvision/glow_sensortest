#include "Arduino.h"
#include "Leds.h"

Leds::Leds() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, numLeds);

  FastLED.setMaxPowerInVoltsAndMilliamps(5,5000);
}

Leds::lightFromPCB() {
    for(int i = 0; i < numLeds; i ++){
      leds[i] = CRGB::Red;
      //delay(6);
      FastLED.show();
      fadeToBlackBy(leds,numLeds,25);
    }
}

Leds::lightFromMid() {
    for(int i = 0; i < numLeds; i ++){
      leds[numLeds/2 - i/2] = CRGB::Red;
      leds[numLeds/2 + i/2] = CRGB::Red;
      //delay(6);
      FastLED.show();
      fadeToBlackBy(leds,numLeds,25);
    }
}
  
Leds::lightFromFarSide() {
    for(int i = 0; i < numLeds; i ++){
      leds[numLeds - i] = CRGB::Red;
      //delay(6);
      FastLED.show();
      fadeToBlackBy(leds,numLeds,25);
    }
}

Leds::update() {
    switch(touchState){
    case 0:
      fadeToBlackBy(leds,numLeds,5);
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
