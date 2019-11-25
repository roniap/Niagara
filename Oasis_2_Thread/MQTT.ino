//---------------- MQTT Protocol Function ------------

void MQTTprocess(String dataSub) {
  uint8_t total = dataSub.indexOf('#');
  String keyword = "";
  keyword = dataSub.substring(0, total);
  Feedback = "";

  if (keyword == "pH") {
    pH_read ();

    Feedback += keyword;
    Feedback += ':';
    Feedback += pH;
    Feedback += ':';
    Feedback += "GET";
    Feedback += '#';

    reply(Feedback);
  }

  else if (keyword == "TDS") {
    TDS_read ();

    Feedback += keyword;
    Feedback += ':';
    Feedback += TDS;
    Feedback += ':';
    Feedback += "GET";
    Feedback += '#';

    reply(Feedback);
  }

  else  if (keyword == "VolumeMT") {
    UltSensorMT_read ();

    Feedback += keyword;
    Feedback += ':';
    Feedback += volumeMT;
    Feedback += ':';
    Feedback += "GET";
    Feedback += '#';
    reply(Feedback);
  }

  else  if (keyword == "DHT") {
    DHT_read();

    Feedback += keyword;
    Feedback += ':';
    Feedback += temperature;
    Feedback += ':';
    Feedback += humidity;
    Feedback += ':';
    Feedback += "GET";
    Feedback += '#';

    reply(Feedback);
  }

  else  if (keyword == "RainStatus") {
    int Rainflag = 0;
    Rainflag = digitalRead (Rainpin);

    Feedback += keyword;
    Feedback += ':';
    Feedback += Rainflag;
    Feedback += ':';
    Feedback += "GET";
    Feedback += '#';

    reply(Feedback);
  }

  else  if (keyword == "FlowSensor") {
    Feedback += keyword;
    Feedback += ':';
    Feedback += l_hour1;
    Feedback += ':';
    Feedback += l_hour2;
    Feedback += ':';
    Feedback += "GET";
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
  strcpy(c_subs, "Agrotech/SensorBoard/Command");
  Serial.println (c_subs);
  strcpy(c_pubs, "Agrotech/SensorBoard/Feedback");
  Serial.println (c_pubs);

}


//=============================================
void reconnect()
{
  if (!client.connected()) {                                         // Loop until reconnected
    Serial.print("MQTT connecting ... ");
    //if (client.connect(ARDUINO_CLIENT, BROKER_ID, BROKER_PASS)) {      // Attempt to connect
    if (client.connect(ARDUINO_CLIENT)){
      Serial.println("connected");
      client.subscribe(c_subs);

    } else {
      //Serial.println("Connection failed");
      //Serial.print(client.state());
      delay(500);
    }
  }
}

//=============================================
void callback(char* topic, byte * payload, unsigned int length)
{
  String dataSub;

  //Serial.print("[sub: ");
  //Serial.print(topic);
  //Serial.print("] ");
  char message[length + 1] = "";
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
    dataSub += (char)payload[i];
  }
  message[length] = '\0';
  //Serial.println(message);

  MQTTprocess(dataSub);
}
