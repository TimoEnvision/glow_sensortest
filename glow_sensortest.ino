#include "Sensors.h"
#include "Leds.h"
#include "MQTT_Ethernet.h"
#include "Artnet.h"

#include <Ethernet.h>
#include <EthernetClient.h>
#include <Dns.h>
#include <Dhcp.h>

#define numTubes 3
#define numTouchAreas 2

Sensors *sensors;

Leds *leds;

MQTT_Ethernet *mqtt_ethernet;

Artnet *artnet;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress iotIP (192, 168, 1, 150);

int counter = 0;       // how many times we have seen new touchState

// the following variable is a long because the time, measured in milliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long time = 0;         // the last time the output pin was sampled
int debounce_count = 4; // number of millis/samples to consider before declaring a debounced input

void setup() { 
  Serial.begin(115200);
  
  Ethernet.begin(mac, iotIP);
  delay(1000); //give the ethernet a second to initialize

  sensors = new Sensors();

  leds = new Leds();

  mqtt_ethernet = new MQTT_Ethernet();

  artnet = new Artnet();
} 

//customisation: edit this if you want for example read and copy only 4 or 6 channels from channel 12 or 48 or whatever.
const int total_number_of_channels = 1008; //1008 channels (112*3 controllable leds, 112 * 3 * 3)
const int start_address = 0; // 0 if you want to read from channel 1
byte rgb[total_number_of_channels]; // buffer to hold values for all leds
boolean touchReading[numTubes][numTouchAreas];
uint32_t currentTouchState[numTubes][numTouchAreas];

void loop() {

  if(millis() != time) {  // If we have gone on to the next millisecond
    sensors->read(touchReading);

    for (int side; side < 2; side ++) {
      for (int tube; tube < numTubes; tube ++) {
        if(touchReading[tube][side] == currentTouchState[tube][side] && counter > 0) {
          counter--;
        }
        if(touchReading[tube][side] != currentTouchState[tube][side]) {
          counter++;
        }
        // If the Input has shown the same value for long enough let's switch it
        if(counter >= debounce_count) {
          counter = 0;
          currentTouchState[tube][side] = (uint32_t)touchReading[tube][side];
          mqtt_ethernet->send_touchState(tube, side, currentTouchState[tube][side]);
        }
      }
    }
    time = millis();
  }

  artnet->receive_artnet(rgb, start_address, total_number_of_channels);

  leds->update(rgb);
}
