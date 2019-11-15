//------------ Oasis 2.0 Sindur ---------------

#include <Ethernet.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <MCP342x.h>
#include <Adafruit_ADS1015.h>
#include <EEPROM.h>
#include <NewPing.h>

// MQTT Data
#define ARDUINO_CLIENT "SensorBoard"      // Client ID for Arduino pub/sub
#define BROKER_ID "agrotech"            // Broker Username
#define BROKER_PASS "Kd9dj]XX.{/4~%Lq" // Broker Password


// Sensor Pin
#define UltraTrig1 8
#define UltraEch1 7
#define DHTpin 9
#define Rainpin A0
#define Flow1 2
#define Flow2 3

// Networking details
byte mac[] = {  0x00, 0xAA, 0xBB, 0xCC, 0xEE, 0x05 };
IPAddress ip( 192, 168, 88, 100 );                           // Ethernet shield (W5500) IP address
IPAddress server( 192, 168, 88, 254 );                       // MTTQ server IP address (Broker)

//192.168.88.100
//192.168.88.254
// 10, 100, 1, 100
// 10, 100, 1, 128
int ipd1, ipd2, ipd3, ipd4; //ip device
int ser1, ser2, ser3, ser4; //server
//IPAddress ip(ipd1, ipd2, ipd3, ipd4);
//IPAddress server(ser1, ser2, ser3, ser4);

//void callback(char* topic, byte* payload, unsigned int length);


// Define Naming
EthernetClient ethClient;
PubSubClient client(ethClient);
NewPing sonar(UltraTrig1, UltraEch1, 200);
DHT dht(DHTpin, DHT11);

//ADC
uint8_t address = 0x68;
MCP342x adc_pH = MCP342x(address);
Adafruit_ADS1115 adc_TDS(0x48);

// Variables
//--- Ultrasonic
float distanceMT;
//--- DHT
float temperature, humidity;
//--- TDS
int TDS;
float TDSvolt;
//--- pH
float pH, pHvolt;
//--- Rain
int RainLast = 0;
//--- FlowRate
volatile int flow_frequency1;
unsigned int l_hour1;
volatile int flow_frequency2;
unsigned int l_hour2;

//--- Millis
unsigned long last_Serial;
unsigned long timer_Serial = 10000;
unsigned long last_Rain;
unsigned long timer_Rain = 300000;
unsigned long last_Flow1;
unsigned long current_Flow1;
unsigned long last_Flow2;
unsigned long current_Flow2;

//--- MQTT
char c_subs[40];
char c_pubs[40];
char c_device_ip[20];
String Feedback;
String device_ip, server_ip;


void setup() {

  Serial.begin (9600);

  dht.begin();
  pinMode(Flow1, INPUT);
  digitalWrite(Flow1, HIGH);
  pinMode(Flow2, INPUT);
  digitalWrite(Flow2, HIGH);
  

  // MCP
  MCP342x::generalCallReset();  // Initial reset
  delay(1); // MC342x needs 300us to settle, wait 1ms
  Wire.requestFrom(address, (uint8_t)1); // Check device present

  // ADS
  adc_TDS.begin();       // ADS Setup
  adc_TDS.setGain(GAIN_ONE);

  //IP
  IP_Convert();

  // MQTT
  client.setServer(server, 1883);   // MTTQ parameters
  client.setCallback(callback);
  delay(500);
  Ethernet.begin(mac, ip); // Ethernet shield configuration
  delay(1000); // Allow hardware to stabilize
  PubSub_Convert();

}

void loop() {

  // MQTT Loop
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  //  Serialprint ();

}
