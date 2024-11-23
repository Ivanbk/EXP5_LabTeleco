
#include "wifi.hpp"


//Definitions
const char* ssid = "internoTucar";
const char* password = "PUeLeTyPeLoWNsHU2";


WiFiClientSecure LABCONTROL;

void setup_wifi() {
  int i = 0;
  WiFi.mode(WIFI_STA);
  delay(10);
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  //WiFi.config(ip, gateway, subnet, dns1, dns2);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(80);    
    Serial.print(".,");
    i++;
    if (i > 200) {
      i=0;
      ESP.restart();
    }
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}