#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

#define I2C_SDA 21
#define I2C_SCL 22

MAX30105 particleSensor;
long lastBeat = 0;
float beatsPerMinute;
bool bb;

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_SDA, I2C_SCL);

  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30102 not found.");
    while (1);
  }

  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeIR(0x0A);
}

void loop() {
  long irValue = particleSensor.getIR();
  Serial.print("IR Value: ");
  Serial.println(irValue);

  if (irValue >= 5000) {
    bb = true;
  }

  while (bb) {
    long irValue = particleSensor.getIR();

    if (checkForBeat(irValue)) {
      long now = millis();
      long delta = now - lastBeat;
      lastBeat = now;
      beatsPerMinute = 60.0 / (delta / 1000.0);

      if (beatsPerMinute < 220 && beatsPerMinute > 30) {
        Serial.print("Heart Rate: ");
        Serial.print(beatsPerMinute);
        Serial.println(" BPM");
      }
    }

    if (irValue < 5000) {
      Serial.println("No finger detected");
      bb = false;
    }
  }
}
