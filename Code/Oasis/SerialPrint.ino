
void SerialPrint () {

  Serial.print("[sensor data] EC: ");
  Serial.print(ECReal);
  Serial.print("| Voltage: ");
  Serial.print(VoltageReal);
  Serial.print("| Temp: ");
  Serial.print(hic);
  Serial.print("| Hum: ");
  Serial.print(h);    
//  Serial.print(", pH: ");
//  Serial.println(pHValue);

}
