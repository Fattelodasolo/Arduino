void setup() {
  Serial.begin(9600);

}

void loop() {
  int sensor = analogRead(A0);
  int luce = map (sensor, 0, 1023, 100, 0);

  Serial.print("Analog: ");
  Serial.print (sensor);
  Serial.print("\tLuce: ");
  Serial.print (luce);
  Serial.println("%");

  delay(3000);
  
}
