//---------------- Data Protocol ----------

void convert() {
  device_ip.toCharArray(c_device_ip,20);
  String subs;
  subs = "Hydroponik";
  subs += "/";
  subs += "Command";
  subs += "/";
  subs += device_ip;
  subs.toCharArray(c_subs,40);
  String pubs;
  pubs = "Hydroponik";
  pubs += "/";
  pubs += "Reply";
  pubs += "/";
  pubs += device_ip;
  pubs.toCharArray(c_pubs,40);
}
