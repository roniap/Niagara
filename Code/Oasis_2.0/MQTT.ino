//---------------- MQTT Protocol Function ------------
void reconnect()
{
  if (!client.connected()) {                                         // Loop until reconnected
    Serial.print("MQTT connecting ... ");
    if (client.connect(ARDUINO_CLIENT, BROKER_ID, BROKER_PASS)) {      // Attempt to connect
//  if (client.connect(ARDUINO_CLIENT)){
      Serial.println("connected");
      
      //(re)subscribe
      //client.subscribe(SUB_LED);

      
    } else {
      Serial.print("Connection failed");
      //Serial.print(client.state());
      delay(500);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("[sub: ");
  Serial.print(topic);
  Serial.print("] ");
  char message[length + 1] = "";
  for (int i = 0; i < length; i++)
    message[i] = (char)payload[i];
  message[length] = '\0';
  Serial.println(message);
}
