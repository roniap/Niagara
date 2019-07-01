
//---------------- MQTT Protocol Function ------------
void reconnect()
{

  if (!client.connected()) {                                         // Loop until reconnected
    Serial.print("MQTT connectin9 ... ");
    if (client.connect(ARDUINO_CLIENT, BROKER_ID, BROKER_ID)) {      // Attempt to connect
      Serial.println("connected");
      //(re)subscribe
      //client.subscribe(SUB_LED);
    } else {
      Serial.print("Connection failed, retry ");
      //Serial.print(client.state());
      //Serial.println(", retrying in 0.5 seconds");
      delay(500); // Wait 5 seconds before retrying
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
