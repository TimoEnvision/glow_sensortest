#include "Arduino.h"
#include "Sensors.h"

Sensors::Sensors() {
    // configure atenna inputs
    pinMode(DIG11, INPUT);           // set pin to input
    pinMode(DIG12, INPUT);           // set pin to input
    pinMode(DIG13, INPUT);           // set pin to input
    pinMode(DIG14, INPUT);           // set pin to input
    
    digitalWrite(DIG11, HIGH);       // turn on pullup resistors
    digitalWrite(DIG12, HIGH);       // turn on pullup resistors
    digitalWrite(DIG13, HIGH);       // turn on pullup resistors
    digitalWrite(DIG14, HIGH);       // turn on pullup resistors
}

Sensors::readTouchInput() {
  antennaState1 = 1 - digitalRead(DIG11);   // PCB side antenna
  antennaState2 = 1 - digitalRead(DIG12);   // Far side antenna (start coax)
  antennaState3 = 1 - digitalRead(DIG13);   // PCB side antenna 2
  antennaState4 = 1 - digitalRead(DIG14);   // Far side antenna 2 (start coax)
  
  Serial.println(antennaState4);
    
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

Sensors::update() {
  readTouchInput();
}


