
//------- EC Calculation
void ECvalue () {
  float Total1 = 0, Average1 = 0, Total2 = 0, Average2 = 0;
  int arrayPos;
  int arrayNum = 50;
//int16_t adc0; 

  for (arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++) {
   int16_t adc0 = ads.readADC_SingleEnded(0);
   float VoltageValue1 = adc0 * 0.1875 / 1000 ;
   float VoltageValue2 = 5; //analogRead(pinEC2) * 5.0 / 1024;    
    Total1 += VoltageValue1;
    Total2 += VoltageValue2;    
    delay (20);
  }

  if (arrayPos == arrayNum) {
    Average1 = Total1 / arrayNum;
    Average2 = Total2 / arrayNum;
    
    EC1 = 159.88* exp(0.564*Average1);
    EC2 = 2* Average2;
    Voltage1 = Average1;
    Voltage2 = Average2;
    
    if (Voltage1 < 0.1)
    {
      EC1 = 0;
    }
    if (Voltage2 < 0.1)
    {
      EC2 = 0;
    }
  }
}
