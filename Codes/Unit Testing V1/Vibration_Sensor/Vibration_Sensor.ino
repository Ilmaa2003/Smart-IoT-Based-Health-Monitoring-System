#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// GPS module → NodeMCU V3 connections
// GPS TX → D7 (GPIO13)
// GPS RX → D8 (GPIO15) [optional for writing to GPS]

static const int RXPin = D7; // Receive from GPS
static const int TXPin = D8; // Transmit to GPS (optional)
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin); // RX, TX

void setup() {
  Serial.begin(115200);       // Serial monitor output
  gpsSerial.begin(GPSBaud);   // GPS module baud rate
  Serial.println("GPS Test Started. Waiting for fix...");
}

void loop() {
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    gps.encode(c);
  }

  if (gps.location.isUpdated()) {
    Serial.println("=== GPS Location Update ===");
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude (m): ");
    Serial.println(gps.altitude.meters());
    Serial.print("Satellites: ");
    Serial.println(gps.satellites.value());
    Serial.print("Speed (km/h): ");
    Serial.println(gps.speed.kmph());
    Serial.println("===========================\n");
  }

  delay(1000); // Adjust refresh rate
}
