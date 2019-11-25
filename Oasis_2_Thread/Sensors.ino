//---------------- Sensors Function ------------


// ULtrasonic
void ultrasonic(){
  if(i < ITERATIONS){ 
    data[i] = sonar.ping();
    i++;
  }
  else{
    oneSensorCycle();
    i = 0;
  }
}

void oneSensorCycle() { // All iterations complete, calculate the median.
  unsigned int uS[ITERATIONS];
  uint8_t j, it = ITERATIONS;
  uS[0] = NO_ECHO;
  for (uint8_t i = 0; i < it; i++) { // Loop through iteration results.
    if (data[i] != NO_ECHO) { // Ping in range, include as part of median.
      if (i > 0) {          // Don't start sort till second ping.
        for (j = i; j > 0 && uS[j - 1] < data[i]; j--) // Insertion sort loop.
          uS[j] = uS[j - 1];                         // Shift ping array to correct position for sort insertion.
      } else j = 0;         // First ping is sort starting point.
      uS[j] = data[i];        // Add last ping to array in sorted position.
    } else it--;            // Ping out of range, skip and don't include as part of median.
  }
  
  if(uS[it >> 1]!= 0)
  {
    distance = uS[it >> 1];
  }
}

void UltSensorMT_read () {
  volumeMT = distance / 57;
//  volumeMT = -2.7333 * distance1;
//  volumeMT = volumeMT + 231.08;
}


// DHT11
void DHT_read () {
  dht11.read(&temperature, &humidity, NULL);
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

  for ( arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++ ) {
    uint8_t err = adc_pH.read(adcValue, status);
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

// Water Flow Sensor 1
void flowmeter () {
    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
    l_hour1 = (flow_frequency1 * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
    flow_frequency1 = 0;
    l_hour2 = (flow_frequency2 * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
    flow_frequency2 = 0;
}
