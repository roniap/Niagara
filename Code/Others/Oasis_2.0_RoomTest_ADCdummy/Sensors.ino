//---------------- Sensors Function ------------

// DHT11
void DHT_read () {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float  hic = dht.computeHeatIndex(t, h, false);

  temperature = hic;
  humidity = h;
}


// TDS
void TDS_read () {
  float total = 0, average = 0;
  int arrayPos;
  int arrayNum = 200;


  for ( arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++ ) {
    int16_t adcValue = adc_TDS.readADC_SingleEnded(0);
    float voltageValue = adcValue * 0.125 / 1000 ;
 
    total += voltageValue;
  }

  if ( arrayPos == arrayNum ) {
    arrayPos = 0;
    average = total / arrayNum;

    TDSvolt = average;
    TDS = (64.345 * TDSvolt * TDSvolt) + (441.74 * TDSvolt) - 1.8843;    // Change with TDS Equation
  }

  if (TDSvolt < 0.03) {
    TDSvolt = 0;
    TDS = 0;
  }
  if (TDS < 0)
    TDS = 0;
}


// pH
void pH_read () {
  float total = 0, average = 0;
  int arrayPos;
  int arrayNum = 5;
  long adcValue = 0;

  MCP342x::Config status;

  for ( arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++ ) {
    uint8_t err = adc_pH.convertAndRead (MCP342x::channel1, MCP342x::oneShot,
                                         MCP342x::resolution18, MCP342x::gain1,
                                         1000000, adcValue, status);

    float voltageValue = adcValue * 2.048 / 131071 ; // Ganti
    total += voltageValue;
  }

  if ( arrayPos == arrayNum ) {
    arrayPos = 0;
    average = total / arrayNum;

    pHvolt = average;
    pH = (4.0293 * pHvolt * pHvolt) - (2.7111 * pHvolt) + 0.2829;    // Change with pH Equation
  }
}
