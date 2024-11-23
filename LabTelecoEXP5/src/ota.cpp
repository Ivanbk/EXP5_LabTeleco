#include "OTA.hpp"


void update_ota(char url[]){
	Serial.println("OTA Updating SPIFFS...");
	LABCONTROL.setTimeout(12000); // Set a 12-second timeout for HTTPS connection
	t_httpUpdate_return ret = httpUpdate.updateSpiffs(LABCONTROL, url);
	if (ret == HTTP_UPDATE_OK) {
		Serial.println("OTA Updating sketch...");
		ret = httpUpdate.update(LABCONTROL, url);

		switch (ret) {
			case HTTP_UPDATE_FAILED:
				Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
			break;

			case HTTP_UPDATE_NO_UPDATES:
				Serial.println("HTTP_UPDATE_NO_UPDATES");
			break;

			case HTTP_UPDATE_OK:
				Serial.println("HTTP_UPDATE_OK");
			break;
		}
	}
}

