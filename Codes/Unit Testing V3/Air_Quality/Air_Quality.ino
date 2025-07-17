#include <Firebase_ESP_Client.h>
#include <WiFi.h>

// Use your actual credentials
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
#define FIREBASE_HOST "your_project.firebaseio.com"
#define FIREBASE_AUTH "your_legacy_token"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected");

  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("Testing Firebase write...");

  FirebaseJson testData;
  testData.set("unit_test/temperature", 25.5);
  testData.set("unit_test/humidity", 60);
  testData.set("unit_test/status", "OK");

  if (Firebase.RTDB.setJSON(&fbdo, "/unitTest", &testData)) {
    Serial.println("✅ Firebase write successful");
  } else {
    Serial.print("❌ Firebase write failed: ");
    Serial.println(fbdo.errorReason());
  }
}

void loop() {}
