void setup() {
  Serial.begin(115200);        // Start serial communication
  pinMode(A0, INPUT);          // A0 is the only analog pin on ESP8266
}

void loop() {
  int soundLevel = analogRead(A0);  // Read analog value (0 - 1023)

  Serial.print("Sound Level: ");
  Serial.print(soundLevel);
  Serial.print(" -> ");

  // Classify the sound level
  if (soundLevel < 300) {
    Serial.println("Quiet");
  } else if (soundLevel < 700) {
    Serial.println("Normal");
  } else {
    Serial.println("Loud");
  }

  delay(200);  // Small delay for readability
}
