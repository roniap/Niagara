//------------ Oasis 2.0 Room ---------------

#include <Ethernet.h>
#include <PubSubClient.h>
#include <MCP342x.h>
#include <Adafruit_ADS1015.h>

// MQTT Data
#define ARDUINO_CLIENT "Oasis"      // Client ID for Arduino pub/sub

#define PUB_TDS "Oasis/TDS"         // MTTQ topic for ECreal
#define PUB_VTDS "Oasis/VTDS"         // MTTQ topic for Vreal
#define PUB_Temp "Oasis/Temp"         // MTTQ topic for Temperature Water
#define PUB_DHTtemp "Oasis/DHTtemp"         // MTTQ topic for DHTtemp
#define PUB_DHThum "Oasis/DHThum"         // MTTQ topic for DHThum
#define PUB_pH "Oasis/pH"         // MTTQ topic for pH
#define PUB_VpH "Oasis/VpH"         // MTTQ topic for pH
#define PUBLISH_TIMER 20000              // Publishing delay [ms]


// Networking details
byte mac[] = {  0x00, 0xAA, 0xBB, 0xCC, 0xEE, 0x05 };
IPAddress ip( 10, 1, 90, 92 );                           // Ethernet shield (W5100) IP address
IPAddress server( 10, 1, 90, 100 );                       // MTTQ server IP address (Broker)
//void callback(char* topic, byte* payload, unsigned int length);


// Define Naming
EthernetClient ethClient;
PubSubClient client(ethClient);

//ADC
uint8_t address = 0x68;
MCP342x adc_pH = MCP342x(address);
Adafruit_ADS1115 adc_TDS(0x48);

// Variables
//--- TDS
float TDS, TDSvolt;
//--- pH
float pH, pHvolt;
//--- Millis
long last_LCD;
long timer_LCD = 5000;
long last_MQTT;
long last_Serial;
long timer_Serial = 2000;

void setup() {

  Serial.begin (9600);

  // MCP
  MCP342x::generalCallReset();  // Initial reset
  delay(1); // MC342x needs 300us to settle, wait 1ms
  Wire.requestFrom(address, (uint8_t)1); // Check device present

  // ADS
  adc_TDS.begin();       // ADS Setup
  adc_TDS.setGain(GAIN_ONE);

  // MQTT
  client.setServer(server, 1883);   // MTTQ parameters
  client.setCallback(callback);
  delay(500);
  Ethernet.begin(mac, ip); // Ethernet shield configuration
  delay(1000); // Allow hardware to stabilize

}

void loop() {

  // MQTT Loop
  if (!client.connected()) {
    reconnect();
  }
  MQTTpub();

  Serialprint ();
  client.loop();
}
