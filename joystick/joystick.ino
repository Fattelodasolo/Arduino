void setup() {
  pinMode (3, INPUT);
  digitalWrite(3, HIGH);
  Serial.begin(9600);
  
}

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  int z = digitalRead(3);

  Serial.print("Asse X = ");
  Serial.print(x);
  Serial.print("\t");
  Serial.print("Asse Y = ");
  Serial.print(y);
  Serial.print("\t");
  Serial.print("Asse Z = ");
  Serial.println(z); 
  
  delay (10);

}
