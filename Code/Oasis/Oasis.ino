#include <Ethernet.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"


#define ARDUINO_CLIENT "ProjectOasis"      // Client ID for Arduino pub/sub
#define BROKER_ID "agrotech"            // Broker Username
#define BROKER_PASS "Kd9dj]XX.{/4~%Lq" // Broker Password

#define PUB_EC "Oasis/EC"         // MTTQ topic for ECreal
#define PUB_VEC "Oasis/VEC"         // MTTQ topic for Vreal
#define PUB_Temp "Oasis/Temp"         // MTTQ topic for Temperature Water
#define PUB_DHTtemp "Oasis/DHTtempEC"         // MTTQ topic for DHTtemp
#define PUB_DHThum "Oasis/DHThumEC"         // MTTQ topic for DHThum
#define PUB_pH "Oasis/pHvalue"         // MTTQ topic for pH
#define PUB_VpH "Oasis/VpH"         // MTTQ topic for pH
#define PUBLISH_DELAY 300000              // Publishing delay [ms]

//pH sensor
float pHValue, VoltagepH;

// Value
float ECReal, VoltageReal;
float TSvalue;

// DHT Sensor
#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float t, h, hic;

// Networking details
byte mac[] = {  0x00, 0xAA, 0xBB, 0xCC, 0xEE, 0x05 };
IPAddress ip( 10, 1, 90, 80 );                           // Ethernet shield (W5100) IP address
IPAddress server( 10, 1, 90, 100 );                       // MTTQ server IP address
//Router Mikrotik
//IPAddress ip( 10, 100, 1, 96 );
//IPAddress server( 10, 100, 1, 128 );
EthernetClient ethClient;
PubSubClient client( ethClient );

/*
  // Temp Sensor
  #define pinTS 7
  OneWire oneWire(pinTS);
  DallasTemperature sensorTS(&oneWire);
*/

// ADS
Adafruit_ADS1115 ads(0x48);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Other Variable
long lastLCD, lastMeasure, lastDHT;


void setup() {
  Serial.begin(9600);
  //  sensorTS.begin();     // TS Setup
  ads.begin();       // ADS Setup
  lcd.init();          // LCD Setup
  lcd.backlight();
  dht.begin();      // DHT Setup

  client.setServer(server, 1883);   // MTTQ parameters
  client.setCallback(callback);
  delay(500);
  Ethernet.begin(mac, ip); // Ethernet shield configuration
  delay(1000); // Allow hardware to stabilize
  lastMeasure = millis();
  lastLCD = millis();
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  ECvalue();
  //pHsensor ();
  //  TSread();
  DHTread ();
  LCDshow ();
  //SerialPrint ();

  if (millis() - lastMeasure > PUBLISH_DELAY) {
    pub(PUB_EC, stringConv(ECReal) + "#");
    pub(PUB_VEC, stringConv(VoltageReal) + "#");
//    pub(PUB_Temp, stringConv(TSvalue) + "#");
//    pub(PUB_DHTtemp, stringConv(hic) + "#");
//    pub(PUB_DHThum, stringConv(h) + "#");
//    pub(PUB_pH, stringConv(pHValue) + "#");
//    pub(PUB_VpH, stringConv(VoltagepH) + "#");
    lastMeasure = millis();

  }
  client.loop();
}

/*
void TSread() {
  sensorTS.requestTemperatures();
  TSvalue = sensorTS.getTempCByIndex(0);
}*/
