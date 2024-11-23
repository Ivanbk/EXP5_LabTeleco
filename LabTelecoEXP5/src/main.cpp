
//Libraries

#include <Arduino.h>
#include "DHT.h"
#include "wifi.hpp"
#include "mqtt.hpp"
#include "ota.hpp"
#include "timer.hpp"
#include <ArduinoJson.h>
#include <time.h>
#include "FS.h"
#include "SPIFFS.h"


//Definitions

#define DHTPIN 14
#define DHTTYPE DHT11   // DHT 11

//Init sensor
DHT dht(DHTPIN, DHTTYPE); //Objeto sensor

const char* ntpServer = "pool.ntp.org"; // Use a public NTP server
const long gmtOffset_sec = 0;           // GMT offset in seconds (e.g., -18000 for EST)
const int daylightOffset_sec = 3600;    // Daylight saving offset in seconds (if applicable)

struct tm timeinfo;

void initTime() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("Time synchronized");
}

int pinLedUmbral = 33;

void setup() {

  Serial.begin(115200);
  Serial.println("Starting... VERSION 1.0");

  
      if (!SPIFFS.begin(true)) {
        Serial.println("An error occurred while mounting SPIFFS");
        return;
    }

    Serial.printf("SPIFFS Total Bytes: %d\n", SPIFFS.totalBytes());

  

  setup_wifi();
  setupTimer();
  initTime();
  delay(100);
  setup_mqtt();
  dht.begin();

  pinMode(pinLedUmbral, OUTPUT);
  pinMode(32, OUTPUT);
}

void loop() {


  loop_mqtt();
  // Read temperature as Celsius (the default)
  float h = dht.readHumidity();
  //float h = 55.5;
  // Read humidity
  float t = dht.readTemperature();
  //float t = 23.5;  

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  // Driving PIN Set
  if (t >= 23) {
      digitalWrite(pinLedUmbral, HIGH);
  } else {
      digitalWrite(pinLedUmbral, LOW);
  }

  // JSON publishing
  if(timer_fired){
    timer_fired = false;
    Serial.println("Timer fired");

      // Obtiene la fecha y hora actuales
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Error al obtener la hora");
      return;
    }
    else{
      char dateTime[20];
      strftime(dateTime, sizeof(dateTime), "%d/%m/%y - %H:%M", &timeinfo);
      Serial.println(dateTime);
      publish_dht11(t, h, dateTime);
    }
  }



}