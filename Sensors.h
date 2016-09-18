/* IMPORTANT SIDENOTE
 *  Schematics show that antenna 1 should be connected to pin 25, pin 2 to 26 etc.
 *  In "real life" they are routed to the opposite pins AND the pins are mirrored!
 *  They are mirrored because the antenna 'S4' runs to MTI0 on the chip, S3 to MTI1, S2 to MTI3, S1 to MTI4
 *  So antenna 1 now routes to pin 14, antenna 2 to pin 15, 3 = 16 and 4 = 17.
 */
 
#ifndef Sensors_h
#define Sensors_h

#include <Arduino.h>

// antenna pins Slave 1
int DIG11 =  3;   // PCB side antenna
int DIG12 =  5;   // Far side antenna (start coax)
int DIG13 = 23;   // PCB side antenna 2
int DIG14 = 22;   // Far side antenna 2 (start coax)

// antenna pins Slave 2
int DIG21 = 21;   // PCB side antenna
int DIG22 = 19;   // Far side antenna (start coax)
int DIG23 = 18;   // PCB side antenna 2
int DIG24 = 24;   // Far side antenna 2 (start coax)

// antenna pins master PCB
int DIG31 = 32;   // PCB side antenna
int DIG32 = 31;   // Far side antenna (start coax)
int DIG33 = 30;   // PCB side antenna 2
int DIG34 = 29;   // Far side antenna 2 (start coax)

// antenna state
boolean antennaState1;  // PCB side antenna
boolean antennaState2;  // Far side antenna (start coax)
boolean antennaState3;  // PCB side antenna 2
boolean antennaState4;  // Far side antenna 2 (start coax)

/* touchState indicates where the tube is touched
 * 0 is no touch 
 * 1 is PCB side
 * 2 is mid
 * 3 is far-side */
byte touchState;

class Sensors {
  public:
    Sensors();
    void update();
  private:
    void readTouchInput();
};
#endif
