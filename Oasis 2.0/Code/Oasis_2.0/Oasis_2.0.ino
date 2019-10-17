//------------ Oasis 2.0 ---------------

#include <Ethernet.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <HCSR04.h>
#include <MCP342x.h>

// MQTT Data
#define ARDUINO_CLIENT "Oasis"      // Client ID for Arduino pub/sub
#define BROKER_ID "agrotech"            // Broker Username
#define BROKER_PASS "Kd9dj]XX.{/4~%Lq" // Broker Password


// Sensor Pin
#define UltraTrig1 8
#define UltraEch1 7
#define UltraTrig2 6
#define UltraEch2 5
#define DHTpin 9
#define Flow1 2


// Networking details
byte mac[] = {  0x00, 0xAA, 0xBB, 0xCC, 0xEE, 0x05 };
IPAddress ip( 10, 1, 90, 80 );                           // Ethernet shield (W5100) IP address
IPAddress server( 10, 1, 90, 100 );                       // MTTQ server IP address (Broker)
void callback(char* topic, byte* payload, unsigned int length);


// Define Naming
EthernetClient ethClient;
PubSubClient client(ethClient);
LiquidCrystal_I2C lcd(0x27, 16, 2);
UltraSonicDistanceSensor UltSensorMT(UltraTrig1, UltraEch1);
UltraSonicDistanceSensor UltSensorST(UltraTrig2, UltraEch2);
DHT dht(DHTpin, DHT11);

//ADC
uint8_t address = 0x68;
MCP342x adc_TDS = MCP342x(address);
uint8_t address1 = 0x69;
MCP342x adc_pH = MCP342x(address1);

// Variables
//--- Ultrasonic
float distance, volumeMT, volumeST;
//--- DHT
float temperature, humidity;
//--- TDS
float TDS, TDSvolt;
//--- pH
float pH, pHvolt;
//--- Millis
long last_LCD;
long timer_LCD = 5000;

void setup() {

  Serial.begin (9600);

  lcd.init();
  lcd.backlight();
  dht.begin();

  // ADC
  MCP342x::generalCallReset();  // Initial reset
  delay(1); // MC342x needs 300us to settle, wait 1ms
  Wire.requestFrom(address, (uint8_t)1); // Check device present


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
  client.loop();




}
