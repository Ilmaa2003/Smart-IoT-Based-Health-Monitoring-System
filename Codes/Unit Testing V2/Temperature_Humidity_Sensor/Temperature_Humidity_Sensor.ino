#include <Wire.h>
#include "Adafruit_AHTX0.h"

Adafruit_AHTX0 aht10;
#define I2C_SDA 21
#define I2C_SCL 22

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_SDA, I2C_SCL);

  if (!aht10.begin()) {
    Serial.println("AHT10 sensor not found.");
    while (1);
  }
}

void loop() {
  sensors_event_t humidity, temp;
  aht10.getEvent(&humidity, &temp);

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" % RH");

  delay(2000);
}
