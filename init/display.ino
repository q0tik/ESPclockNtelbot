int count = 0;

void draw() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  hum = String((int) h);
  hum += "%";
  
  temp = String((int) t);
  temp += "C";

  byte hours = (rtc.getHour(h12Flag, pmFlag));
  byte minutes = (rtc.getMinute());

  u8g2.setFont(u8g2_font_courR08_tr);
  u8g2.drawRFrame(36, 1, 34, 29, 1);
  u8g2.setCursor(38, 3);
  u8g2.print(hours / 10, DEC);
  u8g2.print(hours % 10, DEC);
  u8g2.print(":");
  u8g2.print(minutes / 10, DEC);
  u8g2.print(minutes % 10, DEC);
  u8g2.setCursor(38, 21);
  u8g2.print(rtc.getDate(), DEC);
  u8g2.print(".");
  u8g2.print(rtc.getMonth(century) / 10, DEC);
  u8g2.print(rtc.getMonth(century) % 10, DEC);
  u8g2.setCursor(43, 12);
  u8g2.print(getDay());

  u8g2.setFont(u8g2_font_5x8_tf);
  if (WiFi.status() == WL_CONNECTED) {
    u8g2.setCursor(0, 0);
    u8g2.print(WiFi.SSID());
  } else {
    if (count == 10) {
      count = 0;
      connectWiFi();
    } else {
      count++;
    }
  }
  
  if (alarm) {
    u8g2.setCursor(0, 7);
    u8g2.print("a");
//    u8g2.print(ah / 10);
//    u8g2.print(ah % 10);
//    u8g2.print(":");
//    u8g2.print(am / 10);
//    u8g2.print(am % 10);
  }
  
  u8g2.setCursor(0, 15);
  u8g2.print(hum);
  u8g2.setCursor(0, 24);
  u8g2.print(temp);

  u8g2.setFont(u8g2_font_unifont_t_symbols);
  //u8g2.setFont(u8g2_font_fur20_t_symbol);
  u8g2.drawUTF8(90, 10, "☃");
}

String getDay() {
  switch (rtc.getDoW()) {
    case 1:
      return "mon";
    case 2:
      return "tue";
    case 3:
      return "wed";
    case 4:
      return "thu";
    case 5:
      return "fri";
    case 6:
      return "sat";
    case 7:
      return "sun";
    default:
      return "meow";
  }
}
