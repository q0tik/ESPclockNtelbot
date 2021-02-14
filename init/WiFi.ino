void StartAPMode();

IPAddress apIP(192, 168, 4, 1);
char* ssidAP      = "q0tW";
char* passwordAP  = "1234567890";

bool wiFiInit() {
  // attempt to connect to ssid
  connectWiFi();
  
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Start AP mode");
    StartAPMode();

    return false;
  } else {
    Serial.print("WiFi connected\nIp address: ");
    Serial.println(WiFi.localIP());
    
    return true;
  }
}

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  int tries = 10;
  WiFi.begin(_ssid.c_str(), _password.c_str());

  while(--tries > 0 && WiFi.status() != WL_CONNECTED) {
    Serial.print("-");
    delay(1000);
  }
}

void StartAPMode() {
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  Serial.println(WiFi.softAP(ssidAP, passwordAP) ? "Ready" : "Failed!");

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
}
