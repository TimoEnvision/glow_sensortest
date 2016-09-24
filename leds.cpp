#include "Arduino.h"
#include "Leds.h"

#include "FastLED.h"

#define numLeds 10// Data pin that led data will be written out over

#define DATA_PIN 7// This is an array of leds.  One item for each led in your strip.

#define ledsPerStrip 56
#define numStrips 6

CRGB ledArray[numLeds];

Leds::Leds() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(ledArray, numLeds);

  FastLED.setMaxPowerInVoltsAndMilliamps(5,5000);
}

void Leds::update(byte* artnetValues) {
    for (int w = 0; w < ledsPerStrip; w += 2) {
      ledArray[w]   = CRGB(artnetValues[w*3],    artnetValues[w*3+1],    artnetValues[w*3+2]);
      ledArray[w++] = CRGB(artnetValues[(w++)*3],artnetValues[(w++)*3+1],artnetValues[(w++)*3+2]);
    }
    FastLED.show();
}
