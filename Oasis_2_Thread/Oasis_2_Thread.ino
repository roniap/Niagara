//------------ Oasis 2.0 Sindur ---------------

#include <Ethernet.h>
#include <PubSubClient.h>
#include <SimpleDHT.h>
#include <NewPing.h>
#include <MCP342x.h>
#include <Adafruit_ADS1015.h>
#include <EEPROM.h>
#include <Thread.h>
#include <ThreadController.h>

ThreadController control = ThreadController();
Thread Threadultrasonic = Thread();
Thread Threadflowmeter = Thread();

// MQTT Data
#define ARDUINO_CLIENT "SensorBoard"      // Client ID for Arduino pub/sub
#define BROKER_ID "agrotech"            // Broker Username
#define BROKER_PASS "Kd9dj]XX.{/4~%Lq" // Broker Password


// Sensor Pin
#define UltraTrig1 6
#define UltraEch1 5
#define DHTpin A0
#define Rainpin 7
#define Flow1 2
#define Flow2 3

// Networking details
byte mac[] = {  0x00, 0xAA, 0xBB, 0xCC, 0xEE, 0x05 };

int ipd1, ipd2, ipd3, ipd4; //ip device
int ser1, ser2, ser3, ser4; //server

// Define Naming
EthernetClient ethClient;
PubSubClient client(ethClient);
NewPing sonar(UltraTrig1, UltraEch1, 200);
SimpleDHT11 dht11(DHTpin);

//ADC
uint8_t address = 0x68;
MCP342x adc_pH = MCP342x(address);
MCP342x::Config config(MCP342x::channel1, MCP342x::continous, MCP342x::resolution18, MCP342x::gain1);
MCP342x::Config status;
Adafruit_ADS1115 adc_TDS(0x48);

// Variables
//--- Ultrasonic
float distance, volumeMT;
//--- DHT
byte temperature, humidity;
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
unsigned long  timer_Serial = 10000;
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

unsigned int data[10];
int i = 0;
#define ITERATIONS     11

void flow1 () // Interrupt function
{
  flow_frequency1++;
}

void flow2 () // Interrupt function
{
  flow_frequency2++;
}

void setup() {

  //Serial.begin (115200);

  pinMode(Flow1, INPUT_PULLUP);
  pinMode(Flow2, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(2), flow1, RISING); // Setup Interrupt
  attachInterrupt(digitalPinToInterrupt(3), flow2, RISING); // Setup Interrupt
  sei(); // Enable interrupts


  // MCP
  MCP342x::generalCallReset();  // Initial reset
  delay(1); // MC342x needs 300us to settle, wait 1ms
  Wire.requestFrom(address, (uint8_t)1); // Check device present

  // ADS
  adc_TDS.begin();       // ADS Setup
  adc_TDS.setGain(GAIN_ONE);

  //IP
  IP_Convert();
  IPAddress ip(ipd1, ipd2, ipd3, ipd4);
  IPAddress server(ser1, ser2, ser3, ser4);

  uint8_t err = adc_pH.convert(config);
  if (err) {
    Serial.print("Convert error: ");
    Serial.println(err);
  }
  
  // MQTT
  client.setServer(server, 1883);   // MTTQ parameters
  client.setCallback(callback);
  delay(500);
  Ethernet.begin(mac, ip); // Ethernet shield configuration
  delay(1000); // Allow hardware to stabilize
  PubSub_Convert();

  Threadflowmeter.onRun(flowmeter);
  Threadflowmeter.setInterval(1000);
  Threadultrasonic.onRun(ultrasonic);
  Threadultrasonic.setInterval(100);

  control.add(&Threadultrasonic);
  control.add(&Threadflowmeter);
}

void loop() {

  // MQTT Loop
  if (!client.connected()) {
    //reconnect();
  }
  client.loop();
  control.run();

  //Serialprint ();
}
