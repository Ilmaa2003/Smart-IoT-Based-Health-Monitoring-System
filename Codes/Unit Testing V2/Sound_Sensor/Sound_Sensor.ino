#define soundSensor 16
#define buzzer 13

void setup() {
  Serial.begin(9600);
  pinMode(soundSensor, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int soundValue = digitalRead(soundSensor);
  if (soundValue == LOW) {
    Serial.println("Sound detected!");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
  }
}
