//------------ Oasis 2.0 Calibration ---------------

#include <MCP342x.h>
#include <Adafruit_ADS1015.h>

//ADC
uint8_t address = 0x68;
MCP342x adc_pH = MCP342x(address);
Adafruit_ADS1115 adc_TDS(0x48);

// Variables
//--- TDS
float TDS, TDSvolt;
//--- pH
float pH, pHvolt;


void setup() {

  Serial.begin (9600);

  // MCP
  MCP342x::generalCallReset();  // Initial reset
  delay(1); // MC342x needs 300us to settle, wait 1ms
  Wire.requestFrom(address, (uint8_t)1); // Check device present

  // ADS
  adc_TDS.begin();       // ADS Setup
  delay (500);

}

void loop() {

//    TDS_read ();


    pH_read ();

}
