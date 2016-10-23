#include "Arduino.h"
#include "Sensors.h"

#define numAntennas 12
#define pcbSide 0
#define farSide 1

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

void Sensors::read(boolean* touchData) {
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

  for (int tube = 0; tube < numTubes; tube++) {
    if (touchedAt[tube * 4] || touchedAt[1 + tube * 4]) {           // if touched at PCB side
      touchData[tube][pcbSide] = true;
    }
    else {
      touchData[tube][pcbSide] = false;
    }
    if (touchedAt[2 + tube * 4] || touchedAt[3 + tube * 4]) {       // if touched at far side
      touchData[tube][farSide] = true;
    }
    else {                                                          // nobody touches
      touchData[tube][farSide] = false;
    }
  }
}


