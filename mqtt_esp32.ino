#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "belkin.af1";
const char* password = "Cash2014";
const char* mqtt_server = "164.52.192.5";
const int mqtt_port = 1883;
const char* mqtt_user = "sisai";
const char* mqtt_password = "sisai123";
const char* mqtt_topic = "Org_test/test51";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Collect your sensor data here
  
  float sensorValue = 23.45;

  // Publish data to MQTT topic

    client.publish(mqtt_topic, String(sensorValue).c_str());
    delay(500); // Publish data every 5 seconds  
}

void reconnect() 
{
  while (!client.connected()) 
  {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) 
    {
      Serial.println("Connected to MQTT broker");
    } 
    else 
    {
      Serial.println("Failed to connect to MQTT broker. Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
