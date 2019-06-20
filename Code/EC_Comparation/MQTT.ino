
//---------------- MQTT Protocol Function ------------
void reconnect()
{
  // Loop until reconnected
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection ... ");
    // Attempt to connect
    if (client.connect(ARDUINO_CLIENT, BROKER_ID, BROKER_ID)) {
      Serial.println("connected");
      // (re)subscribe
//      client.subscribe(SUB_LED);
    } else {
      Serial.print("Connection failed, state: ");
      Serial.print(client.state());
      Serial.println(", retrying in 5 seconds");
      delay(5000); // Wait 5 seconds before retrying
    }
  }
}
 
// sub callback function
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
