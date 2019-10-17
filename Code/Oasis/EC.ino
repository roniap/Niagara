
//------- EC Calculation
void ECvalue () {
  float Total1 = 0, Average1 = 0;
  int arrayPos;
  int arrayNum = 200;
  int16_t adc0; 

  for ( arrayPos = 0 ; arrayPos < arrayNum ; arrayPos++ ){
   adc0 = ads.readADC_SingleEnded(0);
   float VoltageValue1 = adc0 * 0.1875 / 1000 ;
    Total1 += VoltageValue1;   
    delay( 10 );
  }

  if ( arrayPos == arrayNum ) {
    arrayPos = 0;
    Average1 = Total1 / arrayNum;

    //Voltage
    VoltageReal = Average1;

    //EC Calculation
//    ECReal = 716.69 * VoltageReal - 680.65;
      ECReal = 221.25 * exp (VoltageReal * 0.5907);

    if (VoltageReal < 0.9)
    { VoltageReal = 0;
      ECReal = 0;
      }
      
    if (ECReal < 0)
    { 
      ECReal = 0;
      }
  }
}
