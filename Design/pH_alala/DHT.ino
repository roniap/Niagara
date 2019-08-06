void DHTread () {
t = dht.readTemperature();
h = dht.readHumidity();

if (isnan(h) || isnan(t)) {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
}
// Compute heat index in Celsius (isFahreheit = false)
hic = dht.computeHeatIndex(t, h, false);


Serial.print(F("Humidity: "));
Serial.print(h);
Serial.print(F("%  Temperature: "));
Serial.print(hic);
Serial.println(F("°C "));

}
