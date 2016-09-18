#ifndef Leds_h
#define Leds_h

#include <Arduino.h>

class Leds {
  public:
    Leds();
    void update(uint32_t touchState);
  private:
    void lightFromPCB();
    void lightFromMid();
    void lightFromFarSide();
};
#endif

