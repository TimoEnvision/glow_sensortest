#include "Arduino.h"
#include "Sensors.h"

// antenna pins Slave 1
int DIG31 =  3;   // PCB side antenna
int DIG32 =  5;   // Far side antenna (start coax)
int DIG33 = 23;   // PCB side antenna 2
int DIG34 = 22;   // Far side antenna 2 (start coax)

// antenna pins Slave 2
int DIG21 = 21;   // PCB side antenna
int DIG22 = 19;   // Far side antenna (start coax)
int DIG23 = 18;   // PCB side antenna 2
int DIG24 = 24;   // Far side antenna 2 (start coax)

// antenna pins master PCB
int DIG11 = 32;   // PCB side antenna
int DIG12 = 31;   // Far side antenna (start coax)
int DIG13 = 30;   // PCB side antenna 2
int DIG14 = 29;   // Far side antenna 2 (start coax)

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
uint32_t touchState;

Sensors::Sensors() {
    // configure atenna inputs
    pinMode(DIG31, INPUT);           // set pin to input
    pinMode(DIG32, INPUT);           // set pin to input
    pinMode(DIG33, INPUT);           // set pin to input
    pinMode(DIG34, INPUT);           // set pin to input
    
    digitalWrite(DIG31, HIGH);       // turn on pullup resistors
    digitalWrite(DIG32, HIGH);       // turn on pullup resistors
    digitalWrite(DIG33, HIGH);       // turn on pullup resistors
    digitalWrite(DIG34, HIGH);       // turn on pullup resistors
}

void Sensors::readTouchInput() {
  antennaState1 = 1 - digitalRead(DIG31);   // PCB side antenna
  antennaState2 = 1 - digitalRead(DIG32);   // Far side antenna (start coax)
  antennaState3 = 1 - digitalRead(DIG33);   // PCB side antenna 2
  antennaState4 = 1 - digitalRead(DIG34);   // Far side antenna 2 (start coax)
    
  if (antennaState1 || antennaState3) {
    touchState = 1;
    //Serial.println("PCB side touched");
  }
  else if (antennaState2 || antennaState4) {
    if (touchState == 1) {
      touchState = 2;
      //Serial.println("mid touched");
    }
    else { 
      touchState = 3;
      //Serial.println("far side touched");
    }
  }
  else {
    touchState = 0;  // nobody touches
  }
  if (touchState > 0) {
    //Serial.println(touchState);
  }
}

uint32_t Sensors::update() {
  readTouchInput();
  return touchState;
}


