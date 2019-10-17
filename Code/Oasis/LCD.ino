
void LCDshow () {
  if (millis() - lastLCD > 4000) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("EC: ");
    lcd.setCursor(3, 0);
    lcd.print (ECReal);
          lcd.setCursor(8,0);
       lcd.print(" V: ");
      lcd.print(VoltageReal);
    lcd.setCursor(0, 1);
lcd.print ("H: ");
lcd.print (h);
//    lcd.print("pH: ");
//    lcd.print (pHValue);
    lcd.setCursor(6, 1);
    lcd.print(" TB: ");
    lcd.print(hic);

    lastLCD = millis();
  }
}
