//------------ Oasis 2.0 ---------------

#include <Ethernet.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <HCSR04.h>
#include <MCP342x.h>
#include <Adafruit_ADS1015.h>
#include <EEPROM.h>

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


// Networking details
byte mac[] = {  0x00, 0xAA, 0xBB, 0xCC, 0xEE, 0x05 };
IPAddress ip( 10, 100, 1, 100 );                           // Ethernet shield (W5500) IP address
IPAddress server( 10, 100, 1, 128 );                       // MTTQ server IP address (Broker)

int ipd1, ipd2, ipd3, ipd4; //ip device
int ser1, ser2, ser3, ser4; //server
//IPAddress ip(ipd1, ipd2, ipd3, ipd4);
//IPAddress server(ser1, ser2, ser3, ser4);

//void callback(char* topic, byte* payload, unsigned int length);


// Define Naming
EthernetClient ethClient;
PubSubClient client(ethClient);
LiquidCrystal_I2C lcd(0x27, 16, 2);
UltraSonicDistanceSensor UltSensorMT(UltraTrig1, UltraEch1);
UltraSonicDistanceSensor UltSensorST(UltraTrig2, UltraEch2);
DHT dht(DHTpin, DHT11);

//ADC
uint8_t address = 0x68;
MCP342x adc_pH = MCP342x(address);
Adafruit_ADS1115 adc_TDS(0x48);

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
long last_Serial;
long timer_Serial = 10000;
//--- MQTT
char c_subs[40];
char c_pubs[40];
char c_device_ip[20];
String Feedback;
String device_ip, server_ip;


void setup() {

  Serial.begin (9600);

  lcd.init();
  lcd.backlight();
  dht.begin();

  // MCP
  MCP342x::generalCallReset();  // Initial reset
  delay(1); // MC342x needs 300us to settle, wait 1ms
  Wire.requestFrom(address, (uint8_t)1); // Check device present

  // ADS
  adc_TDS.begin();       // ADS Setup

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

  Serialprint ();
  //  LCDprint ();


}
