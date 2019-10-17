//---------------- Sensors Function ------------

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
    TDS = 1617.9* TDSvolt - 285.26;    // Change with TDS Equation
  }

  /*  if (TDSvolt < 0.9) {
      TDSvolt = 0;
      TDS = 0;
    }*/
  if (TDS < 0)
    TDS = 0;

  Serial.print ("TDS Value :" );
  Serial.print (TDS);
  Serial.print ("   | Voltage :" );
  Serial.println (TDSvolt);
}


// pH
void pH_read () {
  float total = 0, average = 0;
  int arrayPos;
  int arrayNum = 10;
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
//    pH = 1617.9*pHvolt - 285.26;    // Change with TDS Equation
  }

  Serial.print ("pH Value :" );
  Serial.print (pH);
  Serial.print ("   | Voltage :" );
  Serial.println (pHvolt, 4);
}
