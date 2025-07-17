#define tiltSensor 23
#define buzzer 13

void setup() {
  Serial.begin(9600);
  pinMode(tiltSensor, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int tiltValue = digitalRead(tiltSensor);
  if (tiltValue == HIGH) {
    Serial.println("Tilt/Vibration detected!");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
  }
}
