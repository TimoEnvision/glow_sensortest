#include "Arduino.h"
#include "Sensors.h"

#define numAntennas 12

// antenna pins Slave 1
int slaveOnePcbSideAntenna =  3;   // PCB side antenna
int slaveOneFarSideAntenna =  5;   // Far side antenna (start coax)
int slaveOnePcbSideAntenna2 = 23;   // PCB side antenna 2
int slaveOneFarSideAntenna2 = 22;   // Far side antenna 2 (start coax)

// antenna pins Slave 2
int slaveTwoPcbSideAntenna = 21;   // PCB side antenna
int slaveTwoFarSideAntenna = 19;   // Far side antenna (start coax)
int slaveTwoPcbSideAntenna2 = 18;   // PCB side antenna 2
int slaveTwoFarSideAntenna2 = 24;   // Far side antenna 2 (start coax)

// antenna pins master PCB
int MasterPcbSideAntenna = 32;   // PCB side antenna
int MasterFarSideAntenna = 31;   // Far side antenna (start coax)
int MasterPcbSideAntenna2 = 30;   // PCB side antenna 2
int MasterFarSideAntenna2 = 29;   // Far side antenna 2 (start coax)

boolean somethingHappened;
boolean touchedAt[numAntennas];

/* touchState indicates where the tube is touched
 * 0 is no touch 
 * 1 is PCB side
 * 2 is mid
 * 3 is far-side */
uint32_t touchState;
uint32_t previousTouchState;
boolean newActiveState;

Sensors::Sensors() {
    // configure all antenna pins as input
    pinMode(MasterPcbSideAntenna, INPUT);
    pinMode(MasterFarSideAntenna, INPUT);
    pinMode(MasterPcbSideAntenna2, INPUT);
    pinMode(MasterFarSideAntenna2, INPUT);

    pinMode(slaveOnePcbSideAntenna, INPUT);
    pinMode(slaveOneFarSideAntenna, INPUT);
    pinMode(slaveOnePcbSideAntenna2, INPUT);
    pinMode(slaveOneFarSideAntenna2, INPUT);

    pinMode(slaveTwoPcbSideAntenna, INPUT);
    pinMode(slaveTwoFarSideAntenna, INPUT);
    pinMode(slaveTwoPcbSideAntenna2, INPUT);
    pinMode(slaveTwoFarSideAntenna2, INPUT);

    // activate pullup resistors of the antenna inputs on Teensy
    digitalWrite(MasterPcbSideAntenna, HIGH);
    digitalWrite(MasterFarSideAntenna, HIGH);
    digitalWrite(MasterPcbSideAntenna2, HIGH);
    digitalWrite(MasterFarSideAntenna2, HIGH);

    digitalWrite(slaveOnePcbSideAntenna, HIGH);
    digitalWrite(slaveOneFarSideAntenna, HIGH);
    digitalWrite(slaveOnePcbSideAntenna2, HIGH);
    digitalWrite(slaveOneFarSideAntenna2, HIGH);

    digitalWrite(slaveTwoPcbSideAntenna, HIGH);
    digitalWrite(slaveTwoFarSideAntenna, HIGH);
    digitalWrite(slaveTwoPcbSideAntenna2, HIGH);
    digitalWrite(slaveTwoFarSideAntenna2, HIGH);
}

void Sensors::readTouchInput() {
touchedAt[0] = 1 - digitalRead(MasterPcbSideAntenna);    // PCB side antenna
touchedAt[1] = 1 - digitalRead(MasterPcbSideAntenna2); 
touchedAt[2] = 1 - digitalRead(MasterFarSideAntenna);    // Far side antenna (start coax)
touchedAt[3] = 1 - digitalRead(MasterFarSideAntenna2);

touchedAt[4] = 1 - digitalRead(slaveOnePcbSideAntenna);    // PCB side antenna
touchedAt[5] = 1 - digitalRead(slaveOnePcbSideAntenna2);
touchedAt[6] = 1 - digitalRead(slaveOneFarSideAntenna);    // Far side antenna (start coax)
touchedAt[7] = 1 - digitalRead(slaveOneFarSideAntenna2);

touchedAt[8] = 1 - digitalRead(slaveTwoPcbSideAntenna);    // PCB side antenna
touchedAt[9] = 1 - digitalRead(slaveTwoPcbSideAntenna2);
touchedAt[10] = 1 - digitalRead(slaveTwoPcbSideAntenna);   // Far side antenna (start coax)
touchedAt[11] = 1 - digitalRead(slaveTwoFarSideAntenna2);

  for (int i = 0; i < numAntennas / 4; i++) {
    if (touchedAt[0 + i * 4] || touchedAt[1 + i * 4]) {
      touchState = 2 + i * 4;  // touch state 2 for master tube, 6 for slave1, 10 for slave2 
      //Serial.print("tube" + i); Serial.println("PCB side touched");
    }
    else if (touchedAt[2 + i * 4] || touchedAt[3 + i * 4]) {
//      if (touchState == 1) {
//        touchState = 3 + i * 4; // touch state 3 for master tube, 7 for slave1, 11 for slave2 
//        //Serial.print("tube" + i); Serial.println("mid touched");
//      }
//      else { 
      touchState = 4 + i * 4;  // touch state 4 for master tube, 8 for slave1, 12 for slave2 
        //Serial.print("tube" + i); Serial.println("far side touched");
//      }
    }
    else {                     // nobody touches
      touchState = 1 + i * 4;  // touch state 1 for master tube, 5 for slave1, 9 for slave2 
    }

    /* TO DO:
     *  Write something that determines if anything has happened
     *  probably something like: 
     *  
     *  if (touchState == previousTouchState) {
     *    touchState = 0;  // change touch state to 0, nothing will happen @John is dit handig?
     *  }
     */
  }
  
  touchState = 0; //
}

uint32_t Sensors::update() {
  readTouchInput();
  return touchState;
}


