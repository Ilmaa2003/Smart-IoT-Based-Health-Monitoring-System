#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid     = "";
const char* password = "";
const char* googleApiKey = "";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  getGeoLocation();
}

void getGeoLocation() {
  int n = WiFi.scanNetworks();
  String json = "{\"wifiAccessPoints\":[";

  for (int i = 0; i < n; i++) {
    if (i > 0) json += ",";
    json += "{";
    json += "\"macAddress\":\"" + WiFi.BSSIDstr(i) + "\",";
    json += "\"signalStrength\":" + String(WiFi.RSSI(i));
    json += "}";
  }
  json += "]}";

  WiFiClientSecure client;
  client.setInsecure();  // Skip certificate validation

  const char* host = "www.googleapis.com";
  Serial.println("Connecting to Google...");

  if (!client.connect(host, 443)) {
    Serial.println("Connection failed");
    return;
  }

  String url = "/geolocation/v1/geolocate?key=" + String(googleApiKey);
  client.println("POST " + url + " HTTP/1.1");
  client.println("Host: www.googleapis.com");
  client.println("Content-Type: application/json");
  client.println("Content-Length: " + String(json.length()));
  client.println();
  client.println(json);

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  String response = client.readString();
  Serial.println("Location Response:");
  Serial.println(response);
}

void loop() {
}