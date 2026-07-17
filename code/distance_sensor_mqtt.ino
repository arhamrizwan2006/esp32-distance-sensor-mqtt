#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "secrets.h"

const int trig = 5;
const int echo = 18;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish distanceFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/distance");

unsigned long lastPublish = 0;
const long publishInterval = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  connectWiFi();
}

void loop() {
  MQTT_connect();

  unsigned long currentMillis = millis();
  if (currentMillis - lastPublish >= publishInterval) {
    lastPublish = currentMillis;

    float distance = readDistance();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    char payload[10];
    dtostrf(distance, 4, 2, payload);

    if (!distanceFeed.publish(payload)) {
      Serial.println("Publish failed!");
    } else {
      Serial.println("Publish success!");
    }
  }
}

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

float readDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);
  float distance = (duration / 2.0) * 0.0343;
  return distance;
}

void MQTT_connect() {
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    mqtt.disconnect();
    delay(3000);
  }
  Serial.println("MQTT Connected!");
}