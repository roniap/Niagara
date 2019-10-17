#include <Ethernet.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "DHT.h"

#define ARDUINO_CLIENT "ProjectOasis"      // Client ID for Arduino pub/sub
#define BROKER_ID "agrotech"            // Broker Username
#define BROKER_PASS "Kd9dj]XX.{/4~%Lq" // Broker Password
#define PUB_pH "Oasis/pHvalue"         // MTTQ topic for pH
#define PUB_VpH "Oasis/VpH"         // MTTQ topic for pH
#define PUB_DHTtemp "Oasis/DHTtempPH"         // MTTQ topic for DHTtemp
#define PUB_DHThum "Oasis/DHThumPH"         // MTTQ topic for DHThum

//pH sensor
float pHValue, VoltagepH;

// Networking details
byte mac[] = {  0x00, 0x0A, 0x0E, 0x0A, 0x0E, 0x07 };
IPAddress ip( 10, 1, 90, 90 );                           // Ethernet shield (W5100) IP address
IPAddress server( 10, 1, 90, 100 );                       // MTTQ server IP address
EthernetClient ethClient;
PubSubClient client( ethClient );


#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float t, h, hic;


//Millis Variable
long mqttMeasure, relayMeasure, pHMeasure;
#define PUBLISH_DELAY 30000              // Publishing delay [ms]


void setup() {
  Serial.begin(9600);
  client.setServer(server, 1883);   // MTTQ parameters
  client.setCallback(callback);
  delay(500);
  Ethernet.begin(mac, ip); // Ethernet shield configuration
  delay(1000); // Allow hardware to stabilize

  dht.begin();      // DHT Setup

  mqttMeasure = millis();

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  pHsensor ();
  DHTread ();

  if (millis() - mqttMeasure > PUBLISH_DELAY) {
    pub(PUB_pH, stringConv(pHValue) + "#");
    pub(PUB_VpH, stringConv(VoltagepH) + "#");
    pub(PUB_DHTtemp, stringConv(hic) + "#");
    pub(PUB_DHThum, stringConv(h) + "#");
    Serial.println ("Sended!");
    mqttMeasure = millis();
  }
  client.loop();
}

String stringConv(float dataFloat) {
  char tmpBuffer[20];
  dtostrf(dataFloat, 6, 2, tmpBuffer);
  return tmpBuffer;
}
