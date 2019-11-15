//---------------- Data Protocol ----------


void IP_Convert() {
//  device_ip = EEPROMreadString(0) ;
device_ip = "10.100.1.100";
  server_ip = EEPROMreadString(21) ;

  Serial.print ("IP: ");
  Serial.print (device_ip);
  Serial.print ("   | Broker: ");
  Serial.println (server_ip);

  EEPROM_Set_Address();
}

String EEPROMreadString (int addr) {
  String Output = "";
  char r;
  int i = 0;

  while (i < 20) {
    r = EEPROM.read (addr + i);
    Output += r;
    i++;
  }
  return Output;
}


void EEPROM_Set_Address() {
  String temp1, temp2, temp3, temp4;
  int ak1, ak2, ak3, len;

  len = device_ip.length();
  ak1 = device_ip.indexOf(".");
  ak2 = device_ip.indexOf(".", ak1 + 1);
  ak3 = device_ip.indexOf(".", ak2 + 1);

  temp1 = device_ip.substring(0, ak1);
  temp2 = device_ip.substring(ak1 + 1, ak2);
  temp3 = device_ip.substring(ak2 + 1, ak3);
  temp4 = device_ip.substring(ak3 + 1, len);

  ipd1 = temp1.toInt();
  ipd2 = temp2.toInt();
  ipd3 = temp3.toInt();
  ipd4 = temp4.toInt();
  //////////////////////////////////////////
  len = server_ip.length();
  ak1 = server_ip.indexOf(".");
  ak2 = server_ip.indexOf(".", ak1 + 1);
  ak3 = server_ip.indexOf(".", ak2 + 1);

  temp1 = server_ip.substring(0, ak1);
  temp2 = server_ip.substring(ak1 + 1, ak2);
  temp3 = server_ip.substring(ak2 + 1, ak3);
  temp4 = server_ip.substring(ak3 + 1, len);

  ser1 = temp1.toInt();
  ser2 = temp2.toInt();
  ser3 = temp3.toInt();
  ser4 = temp4.toInt();
}
