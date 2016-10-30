#include "Arduino.h"
#include "Leds.h"

/*OctoWS2811 Notes:
 All 8 are the same length (112 WS2812B leds)
 
 Required Connections
 --------------------
 pin 2:  LED Strip #1    Master tube strip 1
 pin 14: LED strip #2    Master tube strip 2
 pin 7:  LED strip #3    Slave1 tube strip 1
 pin 8:  LED strip #4    Slave1 tube strip 2
 pin 6:  LED strip #5    Slave2 tube strip 1
 pin 20: LED strip #6    Slave2 tube strip 2
 pin 21: LED strip #7    NOT USED
 pin 5:  LED strip #8    NOT USED
 pin 15 & 16 - Connect together, but do not use
 pin 4 - Do not use
 pin 3 - Do not use as PWM.  Normal use is ok.*/

//#define USE_OCTOWS2811
//#include<OctoWS2811.h>
#include<FastLED.h>

#define numLedsPerStrip 112
#define numStrips 3
#define numLeds numLedsPerStrip * numStrips

CRGB ledArray[numLeds];

Leds::Leds() {
  FastLED.addLeds<WS2812B, 2, GRB>(ledArray, 0, numLedsPerStrip - 1);
  FastLED.addLeds<WS2812B, 7, GRB>(ledArray, numLedsPerStrip, numLedsPerStrip * 2 - 1);
  FastLED.addLeds<WS2812B, 6, GRB>(ledArray, numLedsPerStrip * 2, numLedsPerStrip * 3 - 1);

  FastLED.setMaxPowerInVoltsAndMilliamps(5,5700);

  for (int w = 0; w < numLeds; w += 1) {
    ledArray[w] = ledArray[w]  = CRGB::White;
    FastLED.show();
    ledArray[w] = ledArray[w]  = CRGB::Black;
  }
}

void Leds::update(byte* artnetValues) {
  for (int w = 0; w < 171; w ++) {
    ledArray[w] = CRGB(artnetValues[w*3],    artnetValues[w*3+1],    artnetValues[w*3+2]);
  }
  for (int w = 170; w < numLedsPerStrip * 2; w ++) {
    ledArray[w] = CRGB(artnetValues[w*3+2],    artnetValues[w*3+3],    artnetValues[w*3+4]);
  }
  for (int w = numLedsPerStrip * 2; w < numLedsPerStrip * 3; w ++) {                      //loop 224
    ledArray[w] = CRGB(artnetValues[w*3+1],    artnetValues[w*3+2],    artnetValues[w*3+3]);
  }

//    for (int w = 0; w < numLedsPerStrip; w ++) {                                                                             // loop 0 - 111
//      ledArray[w] = ledArray[w + numLedsPerStrip] = CRGB(artnetValues[w*3],    artnetValues[w*3+1],    artnetValues[w*3+2]); // read artnetValues 0 - 335
//    }
//    int counter = 112;
//    for (int w = numLedsPerStrip * 2; w < numLedsPerStrip * 2 + 58; w ++) {                                                                              // loop 224 - 281 (58 leds)
//      ledArray[w] = ledArray[w + numLedsPerStrip] = CRGB(artnetValues[w + counter],    artnetValues[w + counter + 1],    artnetValues[w + counter + 2]); // read artnetValues 337 - 509
//      counter += 2;
//    }
//    counter = 230;
//    for (int w = numLedsPerStrip * 2 + 58; w < numLedsPerStrip * 3; w ++) {                                                                              // loop 282 - 335 (54 leds)
//      ledArray[w] = ledArray[w + numLedsPerStrip] = CRGB(artnetValues[w + counter],    artnetValues[w + counter + 1],    artnetValues[w + counter + 2]); // read artnetValues 511 - 673
//      counter += 2;
//    }
//    counter = 228;
//    for (int w = numLedsPerStrip * 4; w < numLedsPerStrip * 5; w ++) {                                                         // loop 446 - 559
//      ledArray[w] = ledArray[w + numLedsPerStrip] = CRGB(artnetValues[w + counter],    artnetValues[w + counter + 1],    artnetValues[w + counter + 2]); // read artnetValues 674 - 1009\
//      Serial.print(w);
//      counter += 2;
//    }
    FastLED.show();
}

