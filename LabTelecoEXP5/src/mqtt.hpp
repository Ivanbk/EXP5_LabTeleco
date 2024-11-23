#ifndef Mqtt_h
#define Mqtt_h

#include <PubSubClient.h>
#include <string>
#include <cstring>
#include "wifi.hpp"
#include "ota.hpp"


#define MSG_BUFFER_SIZE  (50)

extern WiFiClientSecure LABCONTROL;
extern PubSubClient client;

extern float setTemp;

void reconnect();

void setup_mqtt();

void callback(char* topic, byte* payload, unsigned int length);

void loop_mqtt();

void publish_dht11(float temp, float hum, const char* date);

#endif