#include <ArduinoJson.h>
#include <Wifi.h>
#include <PubSubClient.h>

#include "mqttSetup.h"
#include "secrets.h"
#include "ledStrip.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* mqtt_server = "192.168.137.224";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) message += (char)payload[i];
  
  Serial.print("Received on topic: ");
  Serial.println(topic);
  Serial.print("Payload: ");
  Serial.println(message);

  //checks whether the sent data is in hex or json 
  if (String(topic) == "home/led/strip1/color") {
    if (message[0] == '#') {
      // Hex color format
      long color = strtol(message.substring(1).c_str(), NULL, 16);
      int r = (color >> 16) & 0xFF;
      int g = (color >> 8) & 0xFF;
      int b = color & 0xFF;
      setAllPixels(r, g, b);
    } else {
      // JSON RGB format
      StaticJsonDocument<128> doc;
      DeserializationError err = deserializeJson(doc, message);
      if (!err) {
        setAllPixels(doc["r"], doc["g"], doc["b"]);
      }
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("LEDStripClient")) {
      Serial.println("Connected to MQTT broker!");
      client.subscribe("home/led/strip1/color");
      Serial.println("Subscribed to topic: home/led/strip1/color");
    } else {
      Serial.print("Failed. State: ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void mqttSetup() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(500);
    Serial.println("Successfully connected to wifi.");
    Serial.print("ESP IP: ");
    Serial.println(WiFi.localIP());

    // MQTT setup
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void mqttLoop() {
    if (!client.connected()) reconnect();
    client.loop();
}