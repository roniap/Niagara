
//---------------- MQTT Protocol Function ------------
void reconnect()
{

  if (!client.connected()) {                                         // Loop until reconnected
    Serial.print("MQTT connecting ... ");
    if (client.connect(ARDUINO_CLIENT, BROKER_ID, BROKER_PASS)) {      // Attempt to connect
//    if (client.connect(ARDUINO_CLIENT)){
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

//===========================================
void sub(String Data1)
{ 
  char charData1[50];
  memset(charData1,'\n',sizeof(charData1));
  Data1.toCharArray(charData1,Data1.length()+1);
  client.subscribe(charData1);
  //free(charData);
}


String stringConv(float dataFloat){
  char tmpBuffer[20];
  dtostrf(dataFloat, 6, 2, tmpBuffer);
  return tmpBuffer;
}
