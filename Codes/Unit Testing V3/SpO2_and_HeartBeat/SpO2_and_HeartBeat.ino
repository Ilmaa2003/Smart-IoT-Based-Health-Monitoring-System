#include <Wire.h>
#include "Adafruit_AHTX0.h"

#define soundSensor 16
#define tiltSensor 23
#define buzzer 13
#define I2C_SDA 21
#define I2C_SCL 22

Adafruit_AHTX0 aht10;

const unsigned long detectionWindow = 250;       // Max time between sound and vibration
const unsigned long minDelayBetween = 40;        // Ignore simultaneous triggers
const unsigned long coughTrackingWindow = 3000;  // 3-second window to count coughs
const int coughThreshold = 2;                    // ⚠️ Danger if 2 coughs in 3 seconds

unsigned long lastSoundTime = 0;
bool soundDetected = false;

unsigned long coughTimes[10];
int coughIndex = 0;

void setup() {
  Serial.begin(9600);

  pinMode(soundSensor, INPUT);
  pinMode(tiltSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  Wire.begin(I2C_SDA, I2C_SCL);
  if (!aht10.begin()) {
    Serial.println("AHT10 sensor not found. Check wiring.");
    while (1);
  }

  Serial.println("Cough detection system ready.");
}

void loop() {
  unsigned long currentTime = millis();

  // Detect sound (active LOW)
  if (digitalRead(soundSensor) == LOW) {
    lastSoundTime = currentTime;
    soundDetected = true;
  }

  // Detect vibration after sound
  if (digitalRead(tiltSensor) == HIGH && soundDetected) {
    unsigned long timeSinceSound = currentTime - lastSoundTime;
    if (timeSinceSound > minDelayBetween && timeSinceSound <= detectionWindow) {
      Serial.println("✅ Cough confirmed");

      logCough(currentTime);
      checkForDangerousCoughPattern(currentTime);
      readTemperature();

      soundDetected = false;
      delay(500); // debounce
    } else {
      soundDetected = false;
    }
  }

  delay(10);
}

void logCough(unsigned long currentTime) {
  coughTimes[coughIndex] = currentTime;
  coughIndex = (coughIndex + 1) % 10;
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
    delay(500);
    digitalWrite(buzzer, LOW);

    // Clear cough log to avoid retriggering
    for (int i = 0; i < 10; i++) {
      coughTimes[i] = 0;
    }
  }
}

void readTemperature() {
  sensors_event_t humidity, temp;
  aht10.getEvent(&humidity, &temp);

  Serial.print("🌡 Temperature at cough: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");
}
