#include "Sensors.h"
#include "Leds.h"
#include "MQTT_Ethernet.h"
#include "Artnet.h"

Sensors *sensors;

Leds *leds;

MQTT_Ethernet *mqtt_ethernet;

Artnet *artnet

void setup() { 
  Serial.begin(921600);

  sensors = new Sensors();

  leds = new Leds();

  mqtt_ethernet = new MQTT_Ethernet();

  Artnet = new Artnet();
} 

void loop() {
  byte touchState = sensors->update();

  mqtt_ethernet->send_touchState(touchState);

  byte* artnetValues = artnet->receive_artnet();

  leds->update(artnetValues);
}
