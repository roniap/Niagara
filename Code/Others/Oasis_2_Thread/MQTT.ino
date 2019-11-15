//---------------- MQTT Protocol Function ------------

void MQTTprocess(String dataSub) {
  int total = dataSub.indexOf('#');
  String keyword = "";
  keyword = dataSub.substring(0, total);


  if (keyword == "Ph_Read") {
    pH_read ();
    
    Feedback = device_ip;
    Feedback += ';';
    Feedback += keyword;
    Feedback += ';';
    Feedback += "VALUE";
    Feedback += ';';
    Feedback += pH;
    Feedback += '#';
    reply(Feedback);
  }

  else if (keyword == "TDS_Read") {
    TDS_read ();
    Feedback = device_ip;
    Feedback += ';';
    Feedback += keyword;
    Feedback += ';';
    Feedback += "VALUE";
    Feedback += ';';
    Feedback += TDS;
    Feedback += '#';
    reply(Feedback);
  }

  else  if (keyword == "Volume_Read_MT") {
    UltSensorMT_read ();

    Feedback = device_ip;
    Feedback += ';';
    Feedback += keyword;
    Feedback += ';';
    Feedback += "VALUE";
    Feedback += ';';
    Feedback += volumeMT;
    Feedback += '#';
    reply(Feedback);
  }

  else  if (keyword == "DHT_Read") {
    DHT_read();

    Feedback = device_ip;
    Feedback += ';';
    Feedback += keyword;
    Feedback += ';';
    Feedback += "VALUE";
    Feedback += ';';
    Feedback += temperature;
    Feedback += ';';
    Feedback += humidity;
    Feedback += '#';
    reply(Feedback);

  }
}


//=============================================
void reply(String data) {
  char c_data[70];
  data.toCharArray(c_data, 70);
  Serial.println(c_data);
  client.publish(c_pubs, c_data);
}


//=============================================
void PubSub_Convert() {
  device_ip.toCharArray(c_device_ip, 20);

  String subs;
  subs = "Hydroponik";
  subs += "/";
  subs += "Command";
  subs += "/";
  subs += device_ip;
  subs.toCharArray(c_subs, 40);
  Serial.println (c_subs);

  String pubs;
  pubs = "Hydroponik";
  pubs += "/";
  pubs += "Reply";
  pubs += "/";
  pubs += device_ip;
  pubs.toCharArray(c_pubs, 40);
  Serial.println (c_pubs);

}


//=============================================
void reconnect()
{
  if (!client.connected()) {                                         // Loop until reconnected
    Serial.print("MQTT connecting ... ");
    if (client.connect(ARDUINO_CLIENT, BROKER_ID, BROKER_PASS)) {      // Attempt to connect
      //        if (client.connect(ARDUINO_CLIENT)){
      Serial.println("connected");
      client.subscribe(c_subs);

    } else {
      Serial.println("Connection failed");
      //Serial.print(client.state());
      delay(500);
    }
  }
}

//=============================================
void callback(char* topic, byte * payload, unsigned int length)
{
  String dataSub;

  Serial.print("[sub: ");
  Serial.print(topic);
  Serial.print("] ");
  char message[length + 1] = "";
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
    dataSub += (char)payload[i];
  }
  message[length] = '\0';
  Serial.println(message);

  MQTTprocess(dataSub);
}

/*
  //=============================================
  void pub(String topic, String Data)
  {
  if (client.connected()) {
    char charData[120];
    char charIP[50];
    memset(charData, '\n', sizeof(charData));
    memset(charIP, '\n', sizeof(charIP));
    topic.toCharArray(charIP, topic.length() + 1);
    Data.toCharArray(charData, Data.length() + 1);
    client.publish(charIP, charData);
  }
  }

  //=============================================
  String stringConv(float dataFloat) {
  char tmpBuffer[20];
  dtostrf(dataFloat, 6, 2, tmpBuffer);
  return tmpBuffer;
  }
*/
