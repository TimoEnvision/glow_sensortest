/* IMPORTANT SIDENOTE
 *  Schematics show that antenna 1 should be connected to pin 25, pin 2 to 26 etc.
 *  In "real life" they are routed to the opposite pins AND the pins are mirrored!
 *  They are mirrored because the antenna 'S4' runs to MTI0 on the chip, S3 to MTI1, S2 to MTI3, S1 to MTI4
 *  So antenna 1 now routes to pin 14, antenna 2 to pin 15, 3 = 16 and 4 = 17. 
 */

#include "FastLED.h"
#include "sensors.cpp";
// LED stuff

// How many leds are in the strip?
#define numLeds 112

// Data pin that led data will be written out over
#define DATA_PIN 7

// This is an array of leds.  One item for each led in your strip.
CRGB leds[numLeds];

Sensors sensors;

Leds leds;

void setup() {
  delay(2000);
  
  Serial.begin(921600);

  Serial.println(F("Adafruit MQTT demo"));

  sensors = new Sensors();

  // Initialise the Client
  Serial.print(F("\nInit the Client..."));
  Ethernet.begin(mac, iotIP, dnsIP);
  delay(1000); //give the ethernet a second to initialize
  

  mqtt.subscribe(&onoffbutton);
}

void loop() {
  sensors.update();
  
  leds.update();
}
