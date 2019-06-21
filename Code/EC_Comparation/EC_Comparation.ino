#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
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
#define PUBLISH_DELAY 2000              // Publishing delay [ms]

// Hardware setup details
//const int pinEC1 = A1;
const int pinEC2 = A2;
const int pinTS = A0;

// Value
float EC1, EC2;
float Voltage1, Voltage2;
float TSvalue;

// Networking details
byte mac[]    = {  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

IPAddress ip(192, 168, 0, 10);                           // Ethernet shield (W5100) IP address
IPAddress server(192, 168, 0, 2);                       // MTTQ server IP address

EthernetClient ethClient;
PubSubClient client(ethClient);

// Temp Sensor
OneWire oneWire(pinTS);
DallasTemperature sensorTS(&oneWire);

// ADS
Adafruit_ADS1115 ads(0x48);
LiquidCrystal_I2C lcd(0x27, 16, 2);

long lastMeasure;


void setup() {
  Serial.begin(9600);

  // TS Setup
  sensorTS.begin();

  // ADS Setup
  ads.begin();

  // LCD Setup
  lcd.init();
  lcd.backlight();
  
  // MTTQ parameters
  client.setServer(server, 1883);
  client.setCallback(callback);

  // Ethernet shield configuration
  Ethernet.begin(mac, ip);

  delay(1500); // Allow hardware to stabilize
  lastMeasure = millis();  
}


void loop() {
// if (!client.connected())
//    reconnect();

     ECvalue();
     TSread();


  if (millis() - lastMeasure > PUBLISH_DELAY)
  {
      lastMeasure = millis();
      char tmpBuffer[20];
 
      Serial.print("[sensor data] EC1: ");
      Serial.print(EC1);
      Serial.print(", EC2: ");
      Serial.print(EC2);
      Serial.print(", Voltage1: ");
      Serial.print(Voltage1);      
      Serial.print(", Voltage2: ");
      Serial.print(Voltage2);
      Serial.print(", Temp: ");
      Serial.println(TSvalue);
             
      client.publish(PUB_EC1, dtostrf(EC1, 6, 2, tmpBuffer));
//      client.publish(PUB_EC2, dtostrf(EC2, 6, 2, tmpBuffer));
      client.publish(PUB_V1, dtostrf(Voltage1, 6, 2, tmpBuffer));
//      client.publish(PUB_V2, dtostrf(Voltage2, 6, 2, tmpBuffer));          
      client.publish(PUB_TS, dtostrf(TSvalue, 6, 2, tmpBuffer));

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("EC1 :");
      lcd.setCursor(7,0);
      lcd.print (EC1);
      
      lcd.setCursor(0,1);
      lcd.print("V:");
      lcd.setCursor(2,1);
      lcd.print (Voltage1,3);

      lcd.setCursor(9,1);
      lcd.print ("T:");
      lcd.setCursor(11,1);
      lcd.print (TSvalue);
      
  }
  client.loop();
}

void TSread(){
  sensorTS.requestTemperatures();
  TSvalue = sensorTS.getTempCByIndex(0);
  }
