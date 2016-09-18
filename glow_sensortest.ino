#include "Sensors.h"
#include "Leds.h"
#include "MQTT_Ethernet.h"

Sensors *sensors;

Leds *leds;

MQTT_Ethernet *mqtt_ethernet;

void setup() { 
  Serial.begin(921600);

  sensors = new Sensors();

  leds = new Leds();

  mqtt_ethernet = new MQTT_Ethernet();
}

void loop() {
  byte touchState = sensors->update();
  
  leds->update(touchState);

  mqtt_ethernet->send_touchState(touchState);
}
