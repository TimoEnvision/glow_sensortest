#include "Arduino.h"
#include "MQTT_Ethernet.h"

#include <SPI.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include <Ethernet.h>
#include <EthernetClient.h>
#include <Dns.h>
#include <Dhcp.h>

#define IO_SERVER      "192.168.1.3"
#define IO_SERVERPORT  1883
#define IO_USERNAME    "test"
#define IO_KEY         "test"

//Set up the ethernet client
EthernetClient client;

Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_SERVERPORT, IO_USERNAME, IO_KEY);

// You don't need to change anything below this line!
#define halt(s) { Serial.println(F( s )); while(1);  }

Adafruit_MQTT_Publish touchstate_sender = Adafruit_MQTT_Publish(&mqtt,  "tripods/1/touchstate");

MQTT_Ethernet::MQTT_Ethernet() {
  // Initialise the Client
  Serial.print(F("\nInit the Client..."));
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_Ethernet::MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}

void MQTT_Ethernet::send_touchState(byte touchState) {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // Now we can publish stuff!
  Serial.print(F("\nSending touchState "));
  Serial.print(touchState);
  Serial.print("...");
  if (! touchstate_sender.publish((uint32_t)touchState)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}
