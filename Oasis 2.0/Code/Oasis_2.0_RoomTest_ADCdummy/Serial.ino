//---------------- Serial Print ----------

void Serialprint () {
  if (millis() - last_Serial > timer_Serial) {

    TDS_read ();
    Serial.print ("TDS Value :" );
    Serial.print (TDS);
    Serial.print ("   | Voltage :" );    
    Serial.println (TDSvolt);
  
    pH_read ();
    Serial.print ("pH Value :" );
    Serial.print (pH);
    Serial.print ("   | Voltage :" );    
    Serial.println (pHvolt);

    DHT_read ();
    Serial.print ("Temperature :" );
    Serial.print (temperature);
    Serial.print ("   | Humidity :" );    
    Serial.println (humidity);

  }
}
