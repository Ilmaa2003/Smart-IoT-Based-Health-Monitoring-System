


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>


const char* ssid = "Amjad’s iPhone";        // Your WiFi network
const char* password = "amju3237";    // Your WiFi password
const char* apiKey = "AIzaSyCfHRoDxfzQMJGYN2beoJXRPJZiqtAt92g";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  getLocation();
}

void loop() {
  // You can call getLocation() repeatedly if you want periodic updates
}

void getLocation() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String url = "https://www.googleapis.com/geolocation/v1/geolocate?key=" + String(apiKey);
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST("{}");

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Response:");
      Serial.println(payload);

      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (error) {
        Serial.print("JSON parse failed: ");
        Serial.println(error.c_str());
        return;
      }

      float lat = doc["location"]["lat"];
      float lng = doc["location"]["lng"];
      float accuracy = doc["accuracy"];

      Serial.printf("Latitude: %f\n", lat);
      Serial.printf("Longitude: %f\n", lng);
      Serial.printf("Accuracy: %.2f meters\n", accuracy);

    } else {
      Serial.printf("HTTP request failed: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("WiFi not connected.");
  }
}
