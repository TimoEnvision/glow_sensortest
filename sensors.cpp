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
  
  Sensors() {
    // configure atenna inputs
    pinMode(DIG11, INPUT);           // set pin to input
    digitalWrite(DIG11, HIGH);       // turn on pullup resistors
    pinMode(DIG12, INPUT);           // set pin to input
    digitalWrite(DIG12, HIGH);       // turn on pullup resistors
    pinMode(DIG13, INPUT);           // set pin to input
    digitalWrite(DIG13, HIGH);       // turn on pullup resistors
    pinMode(DIG14, INPUT);           // set pin to input
    digitalWrite(DIG14, HIGH);       // turn on pullup resistors
  }

  void readTouchInput() {
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

  void update() {
    readTouchInput();
  }


}


