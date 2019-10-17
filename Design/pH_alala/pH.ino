
void pHsensor () {
  float Total2 = 0.00, Average2 = 0.00;
  int arrayPos;
  int arrayNum = 500;


  for ( arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++ ) {
    int Anavolt = analogRead (A0);
    float VoltageValue2 = Anavolt * 5.00 / 1023;
    Total2 += VoltageValue2;
    delay( 20 );
  }


  if ( arrayPos == arrayNum ) {
    arrayPos = 0;
    Average2 = Total2 / arrayNum;
    VoltagepH = Average2;
    //pHValue = -5.9708 * VoltagepH + 23.369;
    pHValue = 9.6215 * VoltagepH - 10.845;
    
    Serial.print ("V: ");
    Serial.println (VoltagepH,4);
    Serial.print ("pH: ");
    Serial.println (pHValue);        
  }
}
