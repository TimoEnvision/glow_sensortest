#include "Sensors.h";

Sensors sensors;

Leds leds;

void setup() {
  delay(2000);
  
  Serial.begin(921600);

  Serial.println(F("Adafruit MQTT demo"));

  sensors = new Sensors();

  leds = new Leds();

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
