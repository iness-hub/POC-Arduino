#include <PubSubClient.h>
PubSubClient mqtt(espClient);

unsigned long lastMsg = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setupMqtt() {
  setupTopicsMQTT();
  mqtt.setServer(mqtt_server, 1883);
  mqtt.setCallback(callback);
  mqtt.subscribe("pump",0);
}

void connectMqtt() {
  
  // Loop until we're reconnected
  while (!mqtt.connected()) {
     
    Serial.print("Attempting MQTT connection...");
    // Create a  client ID
    String clientId = "esp-" + String(ESP.getChipId());

    // Attempt to connect
    if (mqtt.connect(clientId.c_str())) {
      Serial.println("connected");
      mqtt.subscribe("garden/esp-15730009/pump",0);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    
  }
}

void checkConnection() {
  if (!mqtt.connected()) {
    connectMqtt();
  }
  mqtt.loop();
}

void publishToTopicLoop(String topic, int value) {
  unsigned long now = millis();
  if (now - lastMsg > 100) {
    lastMsg = now;
    publishToTopic(topic, value);
  }
}

void publishToTopic(String topic, int value) {
  String message = (String) value;
  char buf[3];
  message.toCharArray(buf, 3);
  Serial.print("Publish message:" + (String)getMoistureValue());
  Serial.println(topic);
  char topicBuf[32];
  topic.toCharArray(topicBuf, 32);
  mqtt.publish(topicBuf, buf);
}
