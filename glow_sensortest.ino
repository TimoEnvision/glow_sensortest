#include "Sensors.h"
#include "Leds.h"
#include "MQTT_Ethernet.h"
#include "Artnet.h"

#include <Ethernet.h>
#include <EthernetClient.h>
#include <Dns.h>
#include <Dhcp.h>

Sensors *sensors;

Leds *leds;

MQTT_Ethernet *mqtt_ethernet;

Artnet *artnet;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress iotIP (192, 168, 0, 150);

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
const int number_of_channels = 504; //up to 512 channels; using 168 right now for 1 tube (56 controllable leds, 56 * 3)
const int start_address = 0; // 0 if you want to read from channel 1
byte rgb[number_of_channels]; // buffer to hold values for all leds

void loop() {
  byte touchState = sensors->update();

  mqtt_ethernet->send_touchState(touchState);

  //artnet->receive_artnet(rgb, start_address, number_of_channels);

  //leds->update(rgb);
}
