#include <Ethernet.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <LiquidCrystal_I2C.h>


#define ARDUINO_CLIENT "ProjectOasis"      // Client ID for Arduino pub/sub
#define BROKER_ID "agrotech"            // Broker Username
#define BROKER_PASS "Kd9dj]XX.{/4~%Lq" // Broker Password

#define PUB_EC1 "ProjectOasis/EC1"         // MTTQ topic for EC1
#define PUB_EC2 "ProjectOasis/EC2"         // MTTQ topic for EC2
#define PUB_V1 "ProjectOasis/V1"         // MTTQ topic for V1
#define PUB_V2 "ProjectOasis/V2"         // MTTQ topic for V2
#define PUB_TS "ProjectOasis/TS"         // MTTQ topic for TS
#define PUBLISH_DELAY 5000              // Publishing delay [ms]

#define pinTS A0
// Value
float EC1, EC2;
float Voltage1, Voltage2;
float TSvalue;

// Networking details
byte mac[] = {  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
IPAddress ip( 192, 168, 0, 10 );                           // Ethernet shield (W5100) IP address
IPAddress server( 192, 168, 0, 2 );                       // MTTQ server IP address
EthernetClient ethClient;
PubSubClient client( ethClient );


// Temp Sensor
OneWire oneWire(pinTS);
DallasTemperature sensorTS(&oneWire);
// ADS
Adafruit_ADS1115 ads(0x48);
LiquidCrystal_I2C lcd(0x27, 16, 2);

long lastMeasure;


void setup() {
  Serial.begin(9600);
  sensorTS.begin();     // TS Setup
  ads.begin();       // ADS Setup
  lcd.init();          // LCD Setup
  lcd.backlight();
  
  client.setServer(server, 1883);   // MTTQ parameters
  client.setCallback(callback);
  delay(500);
  Ethernet.begin(mac, ip); // Ethernet shield configuration
  delay(1000); // Allow hardware to stabilize
  lastMeasure = millis();  
}


void loop() {
if (!client.connected()) {
    reconnect();
    }
ECvalue();
TSread();
if (millis() - lastMeasure > PUBLISH_DELAY) {
      lastMeasure = millis();
 
      Serial.print("[sensor data] EC1: ");
      Serial.print(EC1);
      Serial.print(", Voltage1: ");
      Serial.print(Voltage1);      
      Serial.print(", Temp: ");
      Serial.println(TSvalue);
    
      pub(PUB_EC1,stringConv(EC1)+"#");
      pub(PUB_V1,stringConv(Voltage1)+"#");
      pub(PUB_TS,stringConv(TSvalue)+"#");
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("EC1: ");
      lcd.setCursor(4,0);
      lcd.print (EC1);
      lcd.setCursor(8,0);
      lcd.print(" V:");
      lcd.print(Voltage1);
      lcd.setCursor(0,1);
      lcd.print("Temp :");
      lcd.print (TSvalue);
  }
client.loop();
}

void TSread(){
sensorTS.requestTemperatures();
TSvalue = sensorTS.getTempCByIndex(0);
}
