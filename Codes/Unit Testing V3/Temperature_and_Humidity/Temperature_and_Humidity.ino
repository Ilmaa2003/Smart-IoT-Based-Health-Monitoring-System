#include <Arduino.h>

#define SMOKE_SENSOR_PIN 34

void setup() {
  Serial.begin(115200);
  pinMode(SMOKE_SENSOR_PIN, INPUT);
}

void loop() {
  int value = analogRead(SMOKE_SENSOR_PIN);
  int percentage = map(value, 0, 4095, 0, 100);

  Serial.print("Smoke (Air Quality) Raw: ");
  Serial.print(value);
  Serial.print(" -> ");
  Serial.print(percentage);
  Serial.println("%");

  if (percentage > 70) {
    Serial.println("🚨 High smoke level detected");
  } else if (percentage < 10) {
    Serial.println("✅ Air is clean");
  }

  delay(2000);
}
