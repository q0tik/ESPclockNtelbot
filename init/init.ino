#include <ESP8266WiFi.h>
#include "DHT.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DS3231.h>
#include <U8g2lib.h>

DS3231 rtc;
bool alarm;
int ah;
int am;

bool century = false;
bool h12Flag;
bool pmFlag;

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);

#define DHTPIN D5

#define BOT_TOKEN "YOUR TOKEN"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

DHT dht(DHTPIN, DHT11);

String _ssid        = "hse";
String _password    = "hsepassword";

WiFiClientSecure net_ssl;
bool wifimode;

float h;
float t;
String hum;
String temp;

void setup() {
  ESP.eraseConfig();
  dht.begin();
  
  u8g2.begin();
  u8g2.setFontPosTop();
  
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Start");
  wifimode = wiFiInit();
  secured_client.setTrustAnchors(&cert);

//  time setup

//  rtc.setYear(2021);
//  rtc.setMonth(2);
//  rtc.setDate(13);
//  rtc.setDoW(6);
//  rtc.setHour(9);
//  rtc.setMinute(39);
//  rtc.setSecond(0);

}

void loop() {
  u8g2.clearBuffer();

//  receiving messages
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  while (numNewMessages) {
    Serial.println("got response");
    handleNewMessages(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }

  if (alarm) {
    if (ah == (rtc.getHour(h12Flag, pmFlag)) && am == (rtc.getMinute())) {
      playMario();

      am += 5;
      if (am / 60 == 1) {
        ah += 1;
      }
      am = am % 60;
      ah = ah % 24;
    }
  }
//------------------------

  draw();
  u8g2.sendBuffer();
  delay(1000);
}
