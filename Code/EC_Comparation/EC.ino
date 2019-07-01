
//------- EC Calculation
void ECvalue () {
  float Total1 = 0, Average1 = 0, Total2 = 0, Average2 = 0;
  int arrayPos;
  int arrayNum = 50;
  uint16_t adc0; 

  for ( arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++ ){
   adc0 = ads.readADC_SingleEnded(0);
   float VoltageValue1 = adc0 * 0.1875 / 1000 ;
    Total1 += VoltageValue1;   
    delay( 20 );
  }

  if ( arrayPos == arrayNum ) {
    Average1 = Total1 / arrayNum;
    EC1 = 2* Average1;
    Voltage1 = Average1;
  }
}

String stringConv(float dataFloat){
  char tmpBuffer[20];
  dtostrf(dataFloat, 6, 2, tmpBuffer);
  return tmpBuffer;
}
