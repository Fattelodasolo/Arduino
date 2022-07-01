void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(4, OUTPUT);

}

void loop() {
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(4, HIGH);

  delay(2000);

  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(4, LOW);

  delay(2000);

}
