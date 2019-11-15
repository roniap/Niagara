//---------------- Sensors Function ------------


// ULtrasonic
void UltSensorMT_read () {
  float distance1 = distance / 57;
  volumeMT = -2.7333 * distance1;
  volumeMT = volumeMT + 231.08;
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
  int arrayNum = 100;

  for ( arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++ ) {
    int16_t adcValue = adc_TDS.readADC_SingleEnded(0);
    float voltageValue = adcValue * 0.125  / 1000 ;
    total += voltageValue;
  }

  arrayPos = 0;
  average = total / arrayNum;

  TDSvolt = average;
  TDS = (64.345 * TDSvolt * TDSvolt) + (441.74 * TDSvolt) - 1.8843;    // Change with TDS Equation
 

  if (TDSvolt < 0.03) {
    TDSvolt = 0;
    TDS = 0;
  }
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
    pH = (4.0293 * pHvolt * pHvolt) - (2.7111 * pHvolt) + 0.2829;   // Change with pH Equation
  }
}

// Rain Sensor
void Rain_check () {
  if (millis() - last_Rain > timer_Rain) {

    String Input = "";
    int Rainflag = 0;
    Rainflag = digitalRead (Rainpin);

    if (Rainflag == 1) {
      Input = "RainStatus:1:GET#";
      reply(Input);
      RainLast = 1;
    }

    else if (Rainflag == 0 && RainLast == 1) {
      Input = "RainStatus:0:GET#";
      reply(Input);
      RainLast = 0;
    }
    last_Rain = millis ();
  }
}


// Water Flow Sensor 1
void Flow1_check () {

  current_Flow1 = millis();
  last_Flow1 = current_Flow1;
  flow_frequency1 = 0;
  delay (1000);

  if (current_Flow1 >= (last_Flow1 + 1000)) {

    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
    l_hour1 = (flow_frequency1 * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
    flow_frequency1 = 0;

//    Serial.print(l_hour1, DEC); // Print litres/hour
//    Serial.println(" L/hour");
  }
}


// Water Flow Sensor 2
void Flow2_check () {

  current_Flow2 = millis();
  last_Flow2 = current_Flow2;
  flow_frequency2 = 0;
  delay (1000);

  if (current_Flow2 >= (last_Flow2 + 1000)) {

    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
    l_hour2 = (flow_frequency2 * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
    flow_frequency2 = 0;

//    Serial.print(l_hour2, DEC); // Print litres/hour
//    Serial.println(" L/hour");
  }
}
