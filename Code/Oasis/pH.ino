
void pHsensor () {
  float Total2 = 0, Average2 = 0;
  int arrayPos;
  int arrayNum = 200;
  int16_t adc1; 

  for ( arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++ ){
  // adc1 = ads.readADC_SingleEnded(1);
  // float VoltageValue2 = adc1 * 0.1875 / 1000 ;
  int Anavolt = analogRead (A0);
   float VoltageValue2 = Anavolt* 5.00 /1023;
    Total2 += VoltageValue2;   
    delay( 10 );
  }


  if ( arrayPos == arrayNum ) {
    arrayPos = 0;
    Average2 = Total2 / arrayNum;
    VoltagepH = Average2;
    pHValue = 9.6215 * VoltagepH - 10.845; 
  }
}
