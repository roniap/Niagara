//---------------- Serial Print ----------

void Serialprint () {
  if (millis() - last_Serial > timer_Serial) {

    TDS_read ();
    Serial.print ("TDS Value :" );
    Serial.print (TDS);
    Serial.print (" ppm" );  
    Serial.print ("   | Voltage :" );
    Serial.print (TDSvolt);
    Serial.println (" Volt" );  
    
    pH_read ();
    Serial.print ("pH Value :" );
    Serial.print (pH);
    Serial.print (" pH" );      
    Serial.print ("   | Voltage :" );
    Serial.print (pHvolt);
    Serial.println (" Volt" );  
    
    DHT_read ();
    Serial.print ("Temperature :" );
    Serial.print (temperature);
    Serial.print (" C" );      
    Serial.print ("   | Humidity :" );
    Serial.print (humidity);
    Serial.println ("%" );  

    UltSensorMT_read ();
    Serial.print ("MT Volume :" );
    Serial.print (volumeMT);
    Serial.println (" L" );  

    Flow1_check ();
    Serial.print ("Water Flow 1 :" );
    Serial.print (l_hour1);
    Serial.println (" L/hour" );    

    Flow2_check ();
    Serial.print ("Water Flow 2 :" );
    Serial.print (l_hour1);
    Serial.println (" L/hour" );  

  }
}
