#ifndef OTA_h
#define OTA_h

#include <Arduino.h>
#include "wifi.hpp"
#include <HTTPClient.h>
#include <HTTPUpdate.h>

void update_ota(char url[]);


#endif