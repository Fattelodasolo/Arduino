void setup() {
  pinMode (2, INPUT);
  pinMode (13, OUTPUT);
  Serial.begin(9600);

}

void loop() {
int pir = digitalRead(2);

if (pir == 1){
    digitalWrite(13, HIGH);
    Serial.println("Intruso!");  
    }
else {
      digitalWrite(13, LOW);
     }

delay (10);

}
