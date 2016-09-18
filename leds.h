#ifndef Leds_h
#define Leds_H

#include <Arduino.h>
class Leds {
  public:
    Leds();
    void update();
  private:
    void lightFromPCB();
    void lightFromMid();
    void lightFromFarSide();
};
#endif

