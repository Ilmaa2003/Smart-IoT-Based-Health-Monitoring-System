// Enhanced ESP32 Cough Detection and Health Monitor

#include <Wire.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "heartRate.h"
#include "Adafruit_AHTX0.h"

// WiFi and Firebase credentials
#define WIFI_SSID "Amjad Azward"
#define WIFI_PASSWORD "K2000I_A2003R"
#define FIREBASE_HOST "smartwatchapp-907d8-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "m7xzcRsh34B6xsy6XUdtDLIlfRi3fpWhx97KRiDo"

MAX30105 particleSensor;
Adafruit_AHTX0 aht10;

FirebaseData fbdo;
FirebaseAuth auth;  // leave empty for legacy token auth
FirebaseConfig config;

#define airQualitySensor 34
#define buzzer 13
#define soundSensor 16
#define tiltSensor 23
#define I2C_SDA 21
#define I2C_SCL 22

const int sampleCount = 60;
uint32_t irBuffer[sampleCount];
uint32_t redBuffer[sampleCount];

// Cough detection timing constants
const unsigned long detectionWindow = 250;
const unsigned long minDelayBetween = 40;
const unsigned long coughTrackingWindow = 3000;
const int coughThreshold = 2;

unsigned long lastSoundTime = 0;
bool soundDetected = false;

unsigned long coughTimes[10] = {0};
int coughIndex = 0;

unsigned long buzzerEndTime = 0;

// Variables to hold latest sensor values
float latestTemp = 0.0;
float latestHumidity = 0.0;
int latestSpO2 = 0;
int latestHeartRate = 0;
int latestAirQualityPercent = 0;

void setup() {
  Serial.begin(115200);

  pinMode(airQualitySensor, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  pinMode(soundSensor, INPUT);
  pinMode(tiltSensor, INPUT);

  Wire.begin(I2C_SDA, I2C_SCL);

  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30105 not found. Check wiring.");
    while (1);
  }
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeIR(0x0A);

  if (!aht10.begin()) {
    Serial.println("AHT10 sensor not found. Check wiring.");
    while (1);
  }

  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  // Firebase setup with legacy token
  config.database_url = FIREBASE_HOST;              // no https:// prefix
  config.signer.tokens.legacy_token = FIREBASE_AUTH; // legacy token string
  Firebase.begin(&config, &auth);                    // auth empty
  Firebase.reconnectWiFi(true);

  Serial.println("System ready.");
}

void loop() {
  unsigned long currentTime = millis();
  detectCough(currentTime);

  static unsigned long lastSensorRead = 0;
  if (currentTime - lastSensorRead > 1000) {
    lastSensorRead = currentTime;
    readPulseOximeter();
    readAHT10Sensor();
    readAirQualitySensor();
    sendAllSensorDataToFirebase(currentTime);
  }

  if (buzzerEndTime != 0 && currentTime > buzzerEndTime) {
    digitalWrite(buzzer, LOW);
    buzzerEndTime = 0;
  }
}

void detectCough(unsigned long currentTime) {
  if (digitalRead(soundSensor) == LOW) {
    lastSoundTime = currentTime;
    soundDetected = true;
  }

  if (digitalRead(tiltSensor) == HIGH && soundDetected) {
    unsigned long timeSinceSound = currentTime - lastSoundTime;
    if (timeSinceSound > minDelayBetween && timeSinceSound <= detectionWindow) {
      Serial.println("✅ Cough confirmed");
      logCough(currentTime);
      checkForDangerousCoughPattern(currentTime);
      readTemperature();
      soundDetected = false;
    } else {
      soundDetected = false;
    }
  }
}

void logCough(unsigned long currentTime) {
  coughTimes[coughIndex] = currentTime;
  coughIndex = (coughIndex + 1) % 10;
  String path = "/coughEvents/" + String(currentTime);
  FirebaseJson json;
  json.set("timestamp", currentTime);
  if (Firebase.RTDB.setJSON(&fbdo, path.c_str(), &json)) {
    Serial.println("Logged cough to Firebase");
  } else {
    Serial.print("Firebase log error: ");
    Serial.println(fbdo.errorReason());
  }
}

void checkForDangerousCoughPattern(unsigned long now) {
  int count = 0;
  for (int i = 0; i < 10; i++) {
    if (now - coughTimes[i] <= coughTrackingWindow) {
      count++;
    }
  }
  if (count >= coughThreshold) {
    Serial.println("🚨 DANGEROUS COUGH PATTERN DETECTED!");
    digitalWrite(buzzer, HIGH);
    buzzerEndTime = millis() + 500;
    for (int i = 0; i < 10; i++) {
      coughTimes[i] = 0;
    }
  }
}

void readTemperature() {
  sensors_event_t humidity, temp;
  aht10.getEvent(&humidity, &temp);
  latestTemp = temp.temperature;
  latestHumidity = humidity.relative_humidity;
  Serial.print("🌡 Temperature at cough: ");
  Serial.print(latestTemp);
  Serial.println(" °C");
}

void readPulseOximeter() {
  particleSensor.check();
  uint32_t irValue = particleSensor.getIR();

  if (irValue < 5000) {
    Serial.println("No finger detected, skipping measurement");
    latestSpO2 = 0;
    latestHeartRate = 0;
    return;
  }

  for (int i = 0; i < sampleCount; i++) {
    particleSensor.check();
    irBuffer[i] = particleSensor.getIR();
    redBuffer[i] = particleSensor.getRed();
    delay(10);
  }

  int32_t spo2 = 0;
  int8_t spo2Valid = 0;
  int32_t heartRate = 0;
  int8_t heartRateValid = 0;

  maxim_heart_rate_and_oxygen_saturation(
    irBuffer,
    sampleCount,
    redBuffer,
    &spo2,
    &spo2Valid,
    &heartRate,
    &heartRateValid
  );

  if (heartRateValid) {
    latestHeartRate = heartRate;
    Serial.print("Heart Rate: ");
    Serial.print(latestHeartRate);
    Serial.println(" BPM");
  } else {
    latestHeartRate = 0;
    Serial.println("Heart Rate: Invalid");
  }

  if (spo2Valid) {
    latestSpO2 = spo2;
    Serial.print("SpO2: ");
    Serial.print(latestSpO2);
    Serial.println(" %");
  } else {
    latestSpO2 = 0;
    Serial.println("SpO2: Invalid");
  }
}

void readAHT10Sensor() {
  sensors_event_t humidity, temp;
  aht10.getEvent(&humidity, &temp);
  latestTemp = temp.temperature;
  latestHumidity = humidity.relative_humidity;
  Serial.print("Temperature : ");
  Serial.print(latestTemp);
  Serial.println(" °C");
  Serial.print("Humidity : ");
  Serial.print(latestHumidity);
  Serial.println(" % RH");
}

void readAirQualitySensor() {
  int sensorValue = analogRead(airQualitySensor);
  latestAirQualityPercent = map(sensorValue, 0, 4095, 0, 100);
  Serial.print("Air Quality : ");
  Serial.print(latestAirQualityPercent);
  Serial.println(" % ");
}

void sendAllSensorDataToFirebase(unsigned long currentTime) {
  String path = "/sensorData/" + String(currentTime);
  FirebaseJson json;
  json.set("timestamp", currentTime);
  json.set("temperature", latestTemp);
  json.set("humidity", latestHumidity);
  json.set("heartRate", latestHeartRate);
  json.set("SpO2", latestSpO2);
  json.set("airQuality", latestAirQualityPercent);

  if (Firebase.RTDB.setJSON(&fbdo, path.c_str(), &json)) {
    Serial.println("Sensor data sent to Firebase");
  } else {
    Serial.print("Failed to send sensor data: ");
    Serial.println(fbdo.errorReason());
  }
}
