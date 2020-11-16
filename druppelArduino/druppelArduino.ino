#include <ESP8266WiFi.h>

WiFiClient espClient;


// Update these with values suitable for your network.

const char* ssid = "ssid";
const char* password = "pass";
const char* mqtt_server = "ip";

// Predefine setup


void setupWifi();
void setupTopicsMQTT();




// MQTT topics
String statusTopic;
String moistureTopic;
String pumpTopic;

void setupTopicsMQTT() {
  String chipId = String(ESP.getChipId());
  String baseTopic = "garden/esp-" + chipId;
  moistureTopic = baseTopic + "/moisture";
  pumpTopic = baseTopic + "/pump";
  statusTopic = baseTopic + "/status";
}

void setup() {
 
  Serial.begin(9600);
  setupWifi();
  setupMqtt();
  setupTopicsMQTT();
  
} 

void loop() {

  checkConnection();

  publishToTopicLoop(moistureTopic,getMoistureValue());

}
