//---------------- LCD Display----------

void LCDprint () {
  if (millis() - last_LCD > timer_LCD) {
    TDS_read ();
    pH_read ();
    DHT_read ();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TDS:  ");
    lcd.print (TDS);

    lcd.setCursor(0, 1);
    lcd.print ("pH:  ");
    lcd.print (pH);
    last_LCD = millis();
  }
}
