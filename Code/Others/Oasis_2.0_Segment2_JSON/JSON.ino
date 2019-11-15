//---------------- LCD Display ----------

String Daily_Update () {
  UltSensorMT_read ();
  UltSensorST_read ();
  TDS_read ();
  pH_read ();
  DHT_read();

  Feedback = "";
  Feedback += "{";

  Feedback += "\"Device_IP\":";
  Feedback += device_ip;
  Feedback += ",";

  Feedback += "\"Volume_MT\":";
  Feedback += volumeMT;
  Feedback += ",";

  Feedback += "\"Volume_ST\":";
  Feedback += volumeST;
  Feedback += ",";

  Feedback += "\"TDS\":";
  Feedback += TDS;
  Feedback += ",";

  Feedback += "\"pH\":";
  Feedback += pH;
  Feedback += ",";

  Feedback += "\"Temperature\":";
  Feedback += temperature;
  Feedback += ",";

  Feedback += "\"Humidity\":";
  Feedback += humidity;

  Feedback += "}";
  return Feedback;
}


String Dosing_Update () {
  TDS_read ();
  pH_read ();

  Feedback = "";
  Feedback += "{";

  Feedback += "\"Device_IP\":";
  Feedback += device_ip;
  Feedback += ",";

  Feedback += "\"TDS\":";
  Feedback += TDS;
  Feedback += ",";

  Feedback += "\"pH\":";
  Feedback += pH;

  Feedback += "}";
  return Feedback;
}
