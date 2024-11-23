
#include "mqtt.hpp"

//Mqtt Definitions:
const char* mqtt_server = "02130d568cb94e56b531441fdc23d648.s2.eu.hivemq.cloud";
const char* mqtt_user = "developers";
const char* mqtt_password = "mXaksE!M3hwxW#V";
const uint16_t mqtt_port = 8883;
const char* mqtt_topic_send = "lab/sensor";
const char* mqtt_topic_receive = "lab/control/#";
const char* mqtt_topic_receive_ota = "lab/control/ota";
const char* mqtt_topic_receive_led = "lab/control/led";


PubSubClient client(LABCONTROL);

void reconnect() {
    int i=0;
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "Esp32_LabControl";
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.publish("Status", "Connected");
      client.subscribe("lab/#"); //Receive Topic
      client.subscribe(mqtt_topic_receive_ota); //OTA Topic
      client.subscribe(mqtt_topic_receive_led); //LED Topic
      if (client.subscribe(mqtt_topic_receive_ota) && client.subscribe(mqtt_topic_receive_led)) {
      Serial.println("Subscribed Correctly");
      } 
      else {
        Serial.println("Subscription failed!");
      }
    } else {
      i++;
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 2 seconds");
      delay(2000);
    }
    if(i>15){
      i=0;
      ESP.restart();
      }
  }
}

void setup_mqtt() {
  LABCONTROL.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop_mqtt() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //Convert Payload to char from byte
  char message[length + 1]; // Allocate enough space for the payload and null terminator
  memcpy(message, payload, length);
  message[length] = '\0'; // Null-terminate the string
  Serial.println(message);

  if(strcmp(topic, mqtt_topic_receive_ota) == 0) {
    Serial.println("OTA Update");
    update_ota(message);
  } 
  else if(strcmp(topic, mqtt_topic_receive_led) == 0) {
    Serial.println("LED Control");
    Serial.println((char)payload[0]);
    if((char)payload[0] == '1') {
      digitalWrite(32, HIGH);
    } else {
      digitalWrite(32, LOW);
  }
  // Switch on the LED if an 1 was received as first character
}
}

void publish_dht11(float temp, float hum, const char* date) {
    // Create a JSON object to publish the data
    char message[150];
    sprintf(message, "{\"sender\":\"GRUPO_2\", \"temp\": %.2f, \"hum\": %.2f, \"date\": \"%s\"}", temp, hum, date);
    client.publish(mqtt_topic_send, message);
}
