#define airQualitySensor 34

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(airQualitySensor);
  int percent = map(value, 0, 4095, 0, 100);

  Serial.print("Air Quality: ");
  Serial.print(percent);
  Serial.println(" %");

  delay(1000);
}
