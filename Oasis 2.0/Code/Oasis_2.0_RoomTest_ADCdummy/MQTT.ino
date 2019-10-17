//---------------- MQTT Protocol Function ------------

void MQTTpub() {
  if (millis() - last_MQTT > PUBLISH_TIMER) {
    TDS_read ();
    pH_read ();
    DHT_read ();

    pub(PUB_TDS, stringConv(TDS) + "#");
    pub(PUB_VTDS, stringConv(TDSvolt) + "#");
    pub(PUB_DHTtemp, stringConv(temperature) + "#");
    pub(PUB_DHThum, stringConv(humidity) + "#");
    pub(PUB_pH, stringConv(pH) + "#");
    pub(PUB_VpH, stringConv(pHvolt) + "#");
    last_MQTT = millis();
  }
}

//=============================================
void reconnect()
{
  if (!client.connected()) {                                         // Loop until reconnected
    Serial.print("MQTT connecting ... ");
//    if (client.connect(ARDUINO_CLIENT, BROKER_ID, BROKER_PASS)) {      // Attempt to connect
  if (client.connect(ARDUINO_CLIENT)){
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


//=============================================
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


//=============================================
void pub(String topic,String Data)
{  
  if(client.connected()){
    char charData[120];
    char charIP[50];
    memset(charData,'\n',sizeof(charData));
    memset(charIP,'\n',sizeof(charIP));
    topic.toCharArray(charIP,topic.length()+1);
    Data.toCharArray(charData,Data.length()+1);
    client.publish(charIP,charData);
    }
}

//=============================================
String stringConv(float dataFloat){
  char tmpBuffer[20];
  dtostrf(dataFloat, 6, 2, tmpBuffer);
  return tmpBuffer;
}
