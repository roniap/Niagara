//---------------- Sensors Function ------------


// ULtrasonic
void UltSensorMT_read () {
  distance = UltSensorMT.measureDistanceCm();
  volumeMT = -2.7333 * distance;
  volumeMT = volumeMT + 231.08;
}

void UltSensorST_read () {
  distance = UltSensorST.measureDistanceCm();
  volumeST = -2.6189 * distance;
  volumeST = volumeST + 115.78;
}


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
  int arrayNum = 1000;


  for ( arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++ ) {
  int16_t adcValue = adc_TDS.readADC_SingleEnded(1);

    float voltageValue = adcValue * 0.1875 / 1000 ;
    total += voltageValue;
  }

  if ( arrayPos == arrayNum ) {
    arrayPos = 0;
    average = total / arrayNum;

    TDSvolt = average;
    TDS = 716.69 * TDSvolt - 680.65;    // Change with TDS Equation
  }

  if (TDSvolt < 0.9) {
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
  int arrayNum = 1000;
  long adcValue = 0;

  MCP342x::Config status;

  for ( arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++ ) {
    uint8_t err = adc_pH.convertAndRead (MCP342x::channel1, MCP342x::oneShot,
                                     MCP342x::resolution18, MCP342x::gain1,
                                     1000000, adcValue, status);

    float voltageValue = adcValue * 0.1875 / 1000 ; // Ganti
    total += voltageValue;
  }

  if ( arrayPos == arrayNum ) {
    arrayPos = 0;
    average = total / arrayNum;

    pHvolt = average;
    pH = 716.69 * pHvolt - 680.65;    // Change with TDS Equation
  }
}
