#ifndef WIFI_HPP
#define WIFI_HPP

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>

extern WiFiClientSecure LABCONTROL;

void setup_wifi();

#endif