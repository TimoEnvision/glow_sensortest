#ifndef Leds_h
#define Leds_h

#include <Arduino.h>

class Leds {
  public:
    Leds();
    void update(byte* touchState);  // @John shouldn't this be rgb / ledData / artnetValues or something?
  private:
};
#endif

